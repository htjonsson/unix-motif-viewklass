#include "VkTabPanel.h"

using namespace std;

/*
XtResource 
VkTabPanel::_resources [] = {
    // *tabs*tabHeight
};
*/

VkTabPanel::VkTabPanel(char* name, Widget parent, Boolean horizOrientation, int tabHeight)
:   VkComponent(name),
    _horizOrientation(horizOrientation)
{
    // https://motif.ics.com/support/docs/viewkit-programmers-guide/component-resource-support

    _tabHeight = tabHeight;

    _margin = 5;
    _margin1 = 5;
    _margin2 = 5;
    _sideOffset = 17;
    _fontName = "-*-helvetica-*-r-*-*-12-*-*-*-*-*-*-*";

    createWidget(parent);
}

VkTabPanel::~VkTabPanel()
{

}

int VkTabPanel::addTab(char *label, void *clientData, Boolean sorted) 
{
    // Ignore the sorted parameter
    VkTabPanelItem* item = new VkTabPanelItem(label, clientData);

    _items.push_back(item);

    return _items.size();// _labels.size();
}

void VkTabPanel::addTabs(char **labels, void **clientDatas, int numTabs, Boolean sorted)
{
    for(int i=0; i<numTabs; i++) 
    {
        addTab(labels[i], clientDatas[i]);
    }
}

Boolean VkTabPanel::removeTab(int index)
{
    if((size_t)index >= _labels.size())
        return false;

    _labels.erase(_labels.begin() + index);
    _clientDatas.erase(_clientDatas.begin() + index);   

    return true;  
}

Boolean VkTabPanel::removeTab(char *label)
{
    for(size_t i=0; i < _labels.size(); i++)
    {
        if(std::string(label) == _labels.at(i))
            return removeTab(i);
    }

    return false;
}

Boolean VkTabPanel::setTabPixmap(int index, Pixmap pixmap)
{
    return false;
}

Boolean VkTabPanel::setTabPixmap(char *label, Pixmap pixmap)
{
    return false;
}

Boolean VkTabPanel::tabPixmap(int index, Pixmap *pixmap_return)
{
    return false;
}

Boolean VkTabPanel::tabPixmap(char *label, Pixmap *pixmap_return)
{
    return false;
}

Boolean VkTabPanel::selectTab(int index, XEvent *event)
{
    static VkTabCallbackStruct calldata;
    if (hasCallbacks(VkTabPanel::callback))
    {
        calldata.tabIndex = index;
        calldata.label = (char*)_labels.at(index).c_str();
        calldata.clientData = _clientDatas.at(index);
        calldata.event = event;

        callCallbacks(VkTabPanel::callback, &calldata);

        return true;
    }
    return false;
}

Boolean VkTabPanel::selectTab(char *label, XEvent *event)
{
    if (_labels.size() == 0)
        return false;

    for(size_t i=0; i < _labels.size(); i++)
    {
        if(std::string(label) == _labels.at(i))
            return selectTab(i, event);
    }
    return false;
}

int VkTabPanel::selectedTab()
{
    return _selectedTab;
}

Boolean VkTabPanel::getTab(int index, char **label_return, void **clientData_return)
{
    size_t size = _labels.size();

    if(size == 0 || size >= (size_t)index)
    {
        label_return = NULL;
        clientData_return = NULL;
        return false;
    }

    label_return = (char**)_labels.at(index).c_str();
    clientData_return = (void**)_clientDatas.at(index);
    return true;
}

Boolean VkTabPanel::horiz()
{
    return _horizOrientation;
}

int VkTabPanel::size()
{
    return _size;
}

bool VkTabPanel::uniformTabs()
{
    return _uniformTabs;
}

int VkTabPanel::lineThickness()
{   
    return _lineThickness;
}

Pixel VkTabPanel::tabBg()
{
    return _tabBg;
}

Pixel VkTabPanel::labelFg()
{
    return _labelFg;
}

Pixel VkTabPanel::labelBg()
{
    return _labelBg;
}

GC VkTabPanel::gc()
{
    return _gc;
}

const char *const
VkTabPanel::callback = "VkTabPanel::callback";

/*-------------------------------------------------------------------------

    Private part of the Tab

-------------------------------------------------------------------------*/

void
VkTabPanel::preDraw(Display* display)
{
    /***************************************************************************
     * 
     *          LOAD FONTS
     * 
    ***************************************************************************/

    // Get font information
    XFontStruct *fontInfo = NULL;
    //string fontName("-*-helvetica-bold-r-*-*-12-*-*-*-*-*-*-*");
    string fontName(_fontName);

    if(!(fontInfo = XLoadQueryFont(display, fontName.c_str())))
    {
        string warning("Font " + fontName +  " not found");
        XtWarning(warning.c_str());
    }
    // Set the font
    XSetFont(display, _gc, fontInfo->fid);

    // Get the height of text
    _textHeight = fontInfo->ascent;

    std::cout << "Height " << _textHeight << endl; 

    /***************************************************************************
     * 
     *          GET COLORS
     * 
    ***************************************************************************/

    XColor color;

    Colormap colormap = DefaultColormap(display, DefaultScreen(display));

    XParseColor(display, colormap, "grey20", &color);
    XAllocColor(display, colormap, &color);

    _labelFg = color.pixel;

    XParseColor(display, colormap, "grey60", &color);
    XAllocColor(display, colormap, &color);

    _labelBg = color.pixel;

    XParseColor(display, colormap, "grey80", &color);
    XAllocColor(display, colormap, &color);

    _tabBg = color.pixel;

    /***************************************************************************/

    _gray80 = color.pixel;

    XParseColor(display, colormap, "grey40", &color);
    XAllocColor(display, colormap, &color);

    _gray40 = color.pixel;

    XParseColor(display, colormap, "grey27", &color);
    XAllocColor(display, colormap, &color);

    _gray27 = color.pixel;

    XParseColor(display, colormap, "black", &color);
    XAllocColor(display, colormap, &color);

    _black = color.pixel;

    XParseColor(display, colormap, "white", &color);
    XAllocColor(display, colormap, &color);

    _white = color.pixel;

    XParseColor(display, colormap, "green", &color);
    XAllocColor(display, colormap, &color);

    _green = color.pixel;

    /***************************************************************************/

    for(size_t i=0; i < _items.size(); i++)
    {
        VkTabPanelItem* item = _items.at(i);
        std::string str = item->label();
    
        _textHeight = fontInfo->ascent;
        item->textWidth(XTextWidth(fontInfo, str.c_str(), str.length()));
    
        std::cout << "Width " << item->textWidth() << endl;  
        std::cout << "Height " << _textHeight << endl;  
    }      
}

void 
VkTabPanel::drawLeftmostTab(Display* display, Window window, int x, int y, int w, int h, Pixel bgColor)
{
    XPoint pnts[3];

    pnts[0].x = x;
    pnts[0].y = y;
    pnts[1].x = x + w;
    pnts[1].y = y + h;
    pnts[2].x = x + w;
    pnts[2].y = y;

    XSetForeground(display, _gc, bgColor);
    XFillPolygon(display, window, _gc, pnts, 3, Convex, CoordModeOrigin);

    // First tab
    XSetForeground(display, _gc, _labelFg);
    XDrawLine(display, window, _gc, x, y, x + w, y + h);
}

void 
VkTabPanel::drawRightmostTab(Display* display, Window window, int x, int y, int w, int h, Pixel bgColor, int extra)
{
    XPoint pnts[3];

    pnts[0].x = x;
    pnts[0].y = y;
    pnts[1].x = x;
    pnts[1].y = y + h;
    pnts[2].x = x + w;
    pnts[2].y = y;

    XSetForeground(display, _gc, bgColor);
    XFillPolygon(display, window, _gc, pnts, 3, Convex, CoordModeOrigin);

    // Last tab
    XSetForeground(display, _gc, _labelFg);
    XDrawLine(display, window, _gc, x, y + h, x + w, y);

    for(int i = 0; i < extra; i++)
    {
        x = x + _sideOffset;
        XDrawLine(display, window, _gc, x - _sideOffset, y + h -1, x, y + h - 1);
        XDrawLine(display, window, _gc, x, y + h - 1, x + w, y);
    }
}

void 
VkTabPanel::drawActiveTab(Display* display, Window window, int x, int y, int w, int h)
{
    XPoint pnts[3];

    pnts[0].x = x;
    pnts[0].y = y;
    pnts[1].x = x + w;
    pnts[1].y = y + h;
    pnts[2].x = x + w;
    pnts[2].y = y;

    XSetForeground(display, _gc, _labelBg);
    XFillPolygon(display, window, _gc, pnts, 3, Convex, CoordModeOrigin);

    pnts[1].x = x + (w/2);
    pnts[1].y = y + (h/2);
    pnts[2].x = x;
    pnts[2].y = y + h;

    XSetForeground(display, _gc, _tabBg);
    XFillPolygon(display, window, _gc, pnts, 3, Convex, CoordModeOrigin);

    // -------------------------------------------------------------------

    XDrawLine(display, window, _gc, x, y + h, x + w, y);
    XDrawLine(display, window, _gc, x + (w/2), y + (h/2), x + w, y + h);
}

void 
VkTabPanel::drawCenterTab(Display* display, Window window, int x, int y, int w, int h)
{
    XPoint pnts[3];

    pnts[0].x = x;
    pnts[0].y = y;
    pnts[1].x = x + w;
    pnts[1].y = y + h;
    pnts[2].x = x + w;
    pnts[2].y = y;

    XSetForeground(display, _gc, _tabBg);
    XFillPolygon(display, window, _gc, pnts, 3, Convex, CoordModeOrigin);

    pnts[1].x = x + (w/2);
    pnts[1].y = y + (h/2);
    pnts[2].x = x;
    pnts[2].y = y + h;

    XFillPolygon(display, window, _gc, pnts, 3, Convex, CoordModeOrigin);

    // -------------------------------------------------------------------

    XSetForeground(display, _gc, _labelFg);
    XDrawLine(display, window, _gc, x, y, x + w, y + h);  
    XDrawLine(display, window, _gc, x, y + h, x + (w/2), y + (h/2));
}

void
VkTabPanel::draw(int width)
{
    int x = _sideOffset; // + 60;
    int y = 0;

    // Get attributes of screen
    Display* display = XtDisplay(_baseWidget);
    Window window = XtWindow(_baseWidget);

    std::cout << "Window " << window << endl;

    preDraw(display);

    XtVaGetValues(_baseWidget,
        // XmNwidth, &width,
        XmNbackground, &_tabBg,
        NULL);

    // cout << "draw() width = " << width << endl; 

    for(size_t i = 0; i < _items.size(); i++)
    {
        VkTabPanelItem* item = _items.at(i);
    
        int widthOfBox = item->textWidth() + 20;

        // Tab is selected
        if((int)i == _selectedTab) 
        {
            drawBoxAsSelected(display, window, x, y, widthOfBox, _textHeight + 12, item->label().c_str());

            // get the hit box    
            item->box(x, x + widthOfBox, y, y + _textHeight + 22);
        }
        else
        {
            drawBox(display, window, x, y, widthOfBox, _textHeight + 12, item->label().c_str());

            // get the hit box    
            item->box(x, x + widthOfBox, y, y + _textHeight + 12);
        }
        x += widthOfBox;
    }
    // draw extent
    if (x < width) {
        drawBox(display, window, x, y, width - x, _textHeight + 12, "");
    }
    // Ignore the right hand side offset
    if (_sideOffset > 0) {
        drawBox(display, window, 0, y, _sideOffset, _textHeight + 12, "");
    }

    return;

    XSetForeground(display, _gc, _labelFg);
    XDrawLine(display, window, _gc, 4, y-1, width - (8), y-1);

    for(size_t i = 0; i < _items.size(); i++)
    {
        VkTabPanelItem* item = _items.at(i);

        int height = heightWithMargins(_textHeight);

        Pixel bg;
        if((int)i == _selectedTab)
            bg = _labelBg;
        else
            bg = _tabBg;
        
        if(i == 0)
            drawLeftmostTab(display, window, x - _sideOffset, y, _sideOffset, height, bg);

        // get the hit box    
        item->box(x, x + widthWithMargins(item->textWidth()), y, y + heightWithMargins(_textHeight));

        drawText(display, window, _gc, x, y, bg, item);

        x += widthWithMargins(item->textWidth());

        if((int)i == _selectedTab)    
        {
            drawLeftmostTab(display, window, x - _sideOffset - widthWithMargins(item->textWidth()), y, _sideOffset, height, _labelBg);     
            if(i != _items.size() - 1)
                drawCenterTab(display, window, x, y, _sideOffset, height);
            drawRightmostTab(display, window, x, y, _sideOffset, height, _labelBg, 0);
        }
        else
        {
            if(i == _items.size() - 1)
                drawRightmostTab(display, window, x, y, _sideOffset, height, bg, 0);
            else
                drawCenterTab(display, window, x, y, _sideOffset, height);
        }
        
        x += _sideOffset;
    }
}

void 
VkTabPanel::drawBox(Display* display, Window window, int x, int y, int width, int height, const char* text)
{
    XSetForeground(display, _gc, _tabBg);
    XFillRectangle(display, window, _gc, x, y, width, height + 20);

	XSetForeground(display, _gc, _gray40);
	XFillRectangle(display, window, _gc, x, y, width, height);

	// Draw upper and right
	XSetForeground(display, _gc, _gray80);
	XDrawLine(display, window, _gc, x, y, x + width, y);
	XDrawLine(display, window, _gc, x, y, x, y + height - 1);

	// Draw lower and left
	XSetForeground(display, _gc, _gray27);
	XDrawLine(display, window, _gc, x + 1, y + height, x + width - 1, y + height);
	XDrawLine(display, window, _gc, x + width - 1, y + 1, x + width - 1, y + height);

	// Draw black line
	XSetForeground(display, _gc, _black);
	XDrawLine(display, window, _gc, x, y + height + 1, x + width - 1, y + height + 1);

	// Draw Text
	// top margin : 6 pixels
	// bottom margin : 6 pixels
	// right margin: 10 pixels
	// left margin: 10 pixels
    XSetForeground(display, _gc, _white);
    XDrawString(display, window, _gc, x + 10, y + 6 + _textHeight, text, strlen(text));  
}

void 
VkTabPanel::drawBoxAsSelected(Display* display, Window window, int x, int y, int width, int height, const char* text)
{
	XSetForeground(display, _gc, _gray40);
	XFillRectangle(display, window, _gc, x, y, width, height);

    int y1 = y + height;
    for(int i = 0; i < 11; i++)
	{
		XDrawLine(display, window, _gc, x + i, y1 + i, (x + width) - i, y1 + i);
	}

	// Draw upper and right
	XSetForeground(display, _gc, _gray80);
	XDrawLine(display, window, _gc, x, y, x + width, y);
	XDrawLine(display, window, _gc, x, y, x, y + height);
    XDrawLine(display, window, _gc, x, y + height, x + 10, y + height + 10);

	// Draw lower and left
	XSetForeground(display, _gc, _gray27);
	XDrawLine(display, window, _gc, x + width - 1, y + 1, x + width - 1, y + height);
    XDrawLine(display, window, _gc, x + 12, y + height + 10, x + width - 10, y + height + 10);
	XDrawLine(display, window, _gc, x + width - 10, y + height + 10, x + width, y + height);

	// Draw black line
	XSetForeground(display, _gc, _black);
    XDrawLine(display, window, _gc, x, y + height + 1, x + 10, y + height + 11);
    XDrawLine(display, window, _gc, x + 11, y + height + 11, x + width - 11, y + height + 11);
    XDrawLine(display, window, _gc, x + width - 10, y + height + 11, x + width + 1, y + height);

	// Draw Text
	// top margin : 6 pixels
	// bottom margin : 6 pixels
	// right margin: 10 pixels
	// left margin: 10 pixels
    XSetForeground(display, _gc, _green);
    XDrawString(display, window, _gc, x + 10, y + 14 + _textHeight, text, strlen(text));    
}
    
void 
VkTabPanel::drawText(Display* display, Window window, GC _gc, int x, int y, Pixel bgColor, VkTabPanelItem* item)
{
    int h = heightWithMargins(_textHeight);
    int w = widthWithMargins(item->textWidth());

    XSetForeground(display, _gc, bgColor);
    XFillRectangle(display, window, _gc, x, y, w, h);

    XSetForeground(display, _gc, _labelFg);
    XDrawLine(display, window, _gc, x, y + h, x + w, y + h);

    w = item->textWidth();
    h = _textHeight;
    x = x + _margin1;
    y = y + h + _margin1;

    cout << "drawText " << " x: " << x << " y: " << y << " width: " << w << " height: " << h << endl;

    XDrawString(display, window, _gc, x, y, item->label().c_str(), item->label().length());
}

/*-------------------------------------------------------------------------*/

int
VkTabPanel::heightWithMargins(int height)
{
    return _margin1 + height + _margin2;
}

int
VkTabPanel::widthWithMargins(int width)
{
    return _margin1 + width + _margin2;
}

void 
VkTabPanel::createWidget(Widget parent)
{
    _baseWidget = XtVaCreateManagedWidget("tabs",
        xmDrawingAreaWidgetClass, parent,
        XmNwidth,  600,
        XmNheight, _tabHeight,
        NULL);   

    // Get the attributes of the screen
    Display* display = XtDisplay(_baseWidget);
    Screen* screen = XtScreen(_baseWidget);  

    XGCValues gcv;
    gcv.foreground = BlackPixelOfScreen(screen);

    _gc = XCreateGC(display, RootWindowOfScreen(screen), GCForeground, &gcv);

    // Setup callbacks
    XtAddCallback(_baseWidget, XmNexposeCallback, (XtCallbackProc)exposeCallback, (XtPointer)this);
    XtAddCallback(_baseWidget, XmNresizeCallback, (XtCallbackProc)resizeCallback, (XtPointer)this);
    XtAddCallback(_baseWidget, XmNinputCallback, (XtCallbackProc)inputCallback, (XtPointer)this);
}

void VkTabPanel::handleExpose(XExposeEvent* event)
{
    std::cout << "handleExpose " << endl;

    int height, width;

    XtVaGetValues(_baseWidget,
        XmNheight,&height,
        XmNwidth,&width,
        NULL);

    cout << "Expose height = " << height << " width = " << width << endl;  

    if (width < event->width)
        width = event->width;

    draw(width);
}

void VkTabPanel::handleResize()
{
    std::cout << "handleResize " << endl; 

    int height, width;

    XtVaGetValues(_baseWidget,
        XmNheight,&height,
        XmNwidth,&width,
        NULL);

    cout << "Resize height = " << height << " width = " << width << endl;  
}

void VkTabPanel::handleKeyReleased(XKeyReleasedEvent* event)
{
    std::cout << "handleKeyReleased" << endl;
}

void VkTabPanel::handleButtonPressed(XButtonPressedEvent* event)
{
   std::cout << " x: " << event->x << " y: " << event->y << endl;

    for(size_t i=0; i<_items.size(); i++)
    {
        VkTabPanelItem* item = _items.at(i);

        if(item->hit(event->x, event->y))
        {
            cout << "An item has been hit" << i << endl;        
            cout << "Label " << item->label() << endl;

            if((int)i != _selectedTab)
            {
                _selectedTab = i;
                draw(-1);

                selectTab(i);
            }
        }
    }
}

void VkTabPanel::handleEvent(XEvent* event)
{
    if(event == NULL)
    {
        // cout << "No event" << endl;
        return;
    }

    // cout << "type : " << event->type << " ";

    // https://stackoverflow.com/questions/35745561/how-can-i-convert-an-xevent-to-a-string
    switch(event->type)
    {
        
        // case 2: cout << "XKeyPressedEvent" << endl; break;
        case 3: handleKeyReleased((XKeyReleasedEvent*)event); break;
        case 4: handleButtonPressed((XButtonPressedEvent*)event); break;
        // case 5: handleButtonReleased((XButtonReleasedEvent*)event); break;
        // case 6: cout << "XPointerMovedEvent" << endl; break;
        // case 7: cout << "XEnterWindowEvent" << endl; break;
        // case 8: cout << "XLeaveWindowEvent" << endl; break;
        // case 9: cout << "XFocusInEvent" << endl; break;
        // case 10: cout << "XFocusOutEvent" << endl; break;
        // case 11: cout << "XKeymapEvent" << endl; break;
        // case 12: cout << "XExposeEvent" << endl; break;
        // case 13: cout << "XGraphicsExposeEvent" << endl; break;
        default: break; // cout << "Undefined" << endl; break;
    }
}

// https://www.drdobbs.com/using-motif-callbacks-in-c/184403403?pgno=5

void VkTabPanel::exposeCallback(Widget widget, XtPointer userdata, XmDrawingAreaCallbackStruct* calldata)
{
    if (calldata->reason != XmCR_EXPOSE) 
    { /* Should NEVER HAPPEN for this program */
        std::cout << "X is screwed up" << endl;
        return;
    } 

    std::cout << "Window " << calldata->window << endl;

    if (calldata->event != NULL && calldata->event->type == 12) // Expose = 12
    {
        XExposeEvent* exposeEvent = (XExposeEvent*)calldata->event;
        std:cout << "XExposeEvent width = " << exposeEvent->width << endl;
    
        if (userdata != NULL)
            ((VkTabPanel*)userdata)->handleExpose(exposeEvent);

        return;
    }
}   

void VkTabPanel::resizeCallback(Widget widget, XtPointer userdata, XmDrawingAreaCallbackStruct* calldata)
{
    std::cout << "Window " << calldata->window << endl;

    if (calldata->reason != XmCR_RESIZE) 
    { /* Should NEVER HAPPEN for this program */
        std::cout << "X is screwed up" << endl;
        return;
    } 

    if (userdata != NULL)
        ((VkTabPanel*)userdata)->handleResize();
}   

void VkTabPanel::inputCallback(Widget widget, XtPointer userdata, XmDrawingAreaCallbackStruct* calldata)
{
    if (calldata->reason != XmCR_INPUT) 
    { /* Should NEVER HAPPEN for this program */
        std::cout << "X is screwed up" << endl;
        return;
    } 

    if (userdata != NULL)
        ((VkTabPanel*)userdata)->handleEvent(calldata->event);
}   
