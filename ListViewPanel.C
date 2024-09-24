// https://www.oreilly.com/openbook/motif/vol6a/Vol6a_html/appa.html#28

class ListViewDelegate
{
public:
    int _numberOfRows = 0;
    int numberOfRows();

public:
    void draw(int row, Display display, Pixmap pixmap, GC gc, Dimension x, Dimension y, Dimension height, Dimension width);
}

int 
ListViewDelegate::numberOfRows()
{
    return _numberOfRows;
}

void 
ListViewDelegate::draw(int row, Display display, Pixmap pixmap, GC gc, Dimension x, Dimension y, Dimension height, Dimension width)
{
    std::string label("Text to be shown in the list view");

    XDrawString(display, pixmap, gc, x+10, y+10, label.c_str(), label.length());
}

// --------------------------------------------------------------------------

class ListViewPanel
{
private:
    Widget _baseWidget;
    Widget _drawingArea;
    Widget _verticalScrollbar;
    Widget _horizontalScrollbar;

private:
    Dimension _rowHeight = 30;
    Dimension _rowWidth = 0;
    Dimension _numberOfRowsVisible = 1;
    Dimension _numberOfRows = 30;

private:
    ListViewDelegate* _delegate = NULL;

public:
    ListViewPanel(const char *name, Widget parent);
    ~ListViewPanel();

public:
    void setDelegate(ListViewDelegate* delegate);
    ListViewDelegate* delegate();

private:
    // Pixmap _pixmap = NULL;

private:
    void setupUserInterface(Widget w);
    void setupCallbacks();

private:
    void redraw(Window window);

private:
    void scrolled(int orientation, int value)
    void expose(Window window); 
    void resize(Window window);   

private:
    static void exposeCallback(Widget widget, XtPointer clientData, XtPointer callData); 
    static void resizeCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragHorizontalCallbackWidget(Widget widget, XtPointer clientData, XtPointer callData);     
};

// --------------------------------------------------------------------------

ListViewPanel::ListViewPanel(const char* name, Widget parent)
:   VkComponent(name)
{
    createWidget(name, parent);
}

VkDoubleBuffer::~ListViewPanel()
{
}

void 
VkDoubleBuffer::createWidget(const char *name, Widget parent)
{
    _baseWidget = XtVaCreateManagedWidget(name,
        xmDrawingAreaWidgetClass, parent,
        XmNresizePolicy, XmRESIZE_ANY,
        NULL);   
    
    _canvas = createPixmap(_baseWidget, 32, 32);  
}

void
ListViewPanel::setDelegate(ListViewDelegate* delegate)
{
    _delegate = delegate;
}

ListViewDelegate* 
ListViewPanel::delegate()
{
    return _delegate;
}

void 
ListViewPanel::createWidget(const char *name, Widget parent, ListViewDelegate* delegate)
{
    setDelegate(default);

    _baseWidget = XtVaCreateManagedWidget (name,
        xmScrolledWindowWidgetClass, parent,
        XmNscrollingPolicy, XmAPPLICATION_DEFINED,
        XmNvisualPolicy,    XmVARIABLE,
        XmNshadowThickness, 0,
        NULL);
    
    // --------------------------------------------------------------------------

    _drawingArea = XtVaCreateManagedWidget ("list_view_panel_drawing_a",
        xmDrawingAreaWidgetClass, _baseWidget,
        XmNwidth,       Resrcs.view_width,
        XmNheight,      Resrcs.view_height,
        NULL);

    // --------------------------------------------------------------------------

    _verticalScrollbar = XtVaCreateManagedWidget ("list_view_panel_vertical_scrollbar",
        xmScrollBarWidgetClass, _baseWidget,
        XmNorientation,   XmVERTICAL,
        XmNmaximum,       (int)(_numberOfRows/_numberOfRowsVisible),
        // XmNsliderSize,    (int)(_numberOfRows/_numberOfRowsVisible),
        NULL);

    // --------------------------------------------------------------------------

    _horizontalScrollbar = XtVaCreateManagedWidget ("list_view_panel_horizontal_scrollbar",
        xmScrollBarWidgetClass, _baseWidget,
        XmNorientation,   XmHORIZONTAL,
        XmNmaximum,       1,
        // XmNsliderSize,    min (Resrcs.view_width / cell_width, Resrcs.cols),
        NULL);

    // --------------------------------------------------------------------------

    XmScrolledWindowSetAreas (_baseWidget, _horizontalScrollbar, _verticalScrollbar, _drawingArea);
}

void 
ListViewPanel:setupCallbacks()
{
    XtAddCallback (_drawingArea, XmNexposeCallback, exposeCallback, this);
    XtAddCallback (_drawingArea, XmNresizeCallback, resizeCallback, this);
    
    // --------------------------------------------------------------------------
    
    XtAddCallback (_verticalScrollbar, XmNvalueChangedCallback, valueChangedVerticalCallback, this);
    XtAddCallback (_verticalScrollbar, XmNdragCallback, dragVerticalCallback, this);
    
    // --------------------------------------------------------------------------
    
    XtAddCallback (_horizontalScrollbar, XmNvalueChangedCallback, valueChangedHorizontalCallback, this);
    XtAddCallback (_horizontalScrollbar, XmNdragCallback, dragHorizontalCallback, this);
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      DRAWING
//
// ------------------------------------------------------------------------------------------------------------------------

void 
ListViewPanel::setRowsVisible(Dimension height)
{
    if (height > 0)
    {
        XtError("Can't calculate rows visible");
        return;
    }

    float rows = (float)height / (float)_rowHeight;
    _numberOfRowsVisible = (int)rows + 1;
}

void
ListViewPanel::redraw(Window window)
{
    // XCopyArea(_display, _pixmap, window, gc, pix_hoffset, pix_voffset, Resrcs.view_width, Resrcs.view_height, sw_hoffset, sw_voffset);    
}

Pixmap 
ListViewPanel::createPixmap(Dimension width, Dimension height)
{
    Pixmap pixmap;

    if (!(pixmap = XCreatePixmap(_display, DefaultRootWindow(_display), width, height, DefaultDepthOfScreen(XtScreen(_drawingArea)))))
    {
        XtError ("Can't Create pixmap.");
        return NULL;
    }
    
    return pixmap;
}

GC
ListViewPanel::createGraphicsContext(Pixmap pixmap)
{
    GC gc;

    if (!(gc = XCreateGC(_display, pixmap, NULL, 0)))
    {
        XtError ("Can't create gc.");
        return NULL;
    }

    return gc;  
}

void
ListViewPanel::preDraw()
{
    Display* display = XtDisplay(_baseWidget);

    _pixmap = createPixmap(_width, _height);
    _gc = createGraphicsContext(_pixmap);

    /***************************************************************************
     * 
     *          LOAD FONTS
     * 
    ***************************************************************************/

    // Get font information
    XFontStruct *fontInfo = NULL;
    string fontName("-*-helvetica-bold-r-*-*-12-*-*-*-*-*-*-*");

    if(!(fontInfo = XLoadQueryFont(display, fontName.c_str())))
    {
        string warning("Font " + fontName +  " not found");
        XtWarning(warning.c_str());
    }
    // Set the font
    XSetFont(display, _gc, fontInfo->fid);

    /***************************************************************************
     * 
     *          SETUP CONTEXT
     * 
    ***************************************************************************/

    XSetForeground(display, _gc, _foregroundColor);
    XSetForeground(display, _gc, _backgroundColor); 
    XFillRectangle(display, _pixmap, _gc, 0, 0, _width, _height)

    for(int i=0; i < _numberOfRowsVisible; i++)
    {
        int offset = _rowHeight * i;

        draw(display, _pixmap, _gc, 0, offset, _rowHeight, _rowWidth);
    }
}

void
// ListViewPanel::draw(Display display, Pixmap pixmap, GC gc, Dimension x, Dimension y, Dimension height, Dimension width)
ListViewPanel::draw(int row, Display display, Window window, GC gc, Dimension x, Dimension y, Dimension height, Dimension width)
{
    if (delegate != NULL)
        delegate->draw(row, display, window, gc, x, y, height, width)
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      ACTIONS
//
// ------------------------------------------------------------------------------------------------------------------------

void 
ListViewPanel::scrolled(int orientation, int value)
{
    if (orientation == XmVERTICAL)
        pix_voffset = value * cell_height;
    else
        pix_hoffset = value * cell_width;
       
    this->redraw (XtWindow (_drawingArea));    
}

void 
ListViewPanel::expose(Window window)
{
    redraw(window);
}

void 
ListViewPanel::resize(Window window)
{
    Dimension width, height;

    XtVaGetValues (_drawingArea, XmNwidth,  &width, XmNheight, &height, XmNgc, &_gc, NULL); 

    _rowWidth = viewWidth;

    std::cout << "XmNwidth " << width << std::endl;
    std::cout << "XmNheight " << height << std::endl;

    // if (_pixmap != NULL)
    //     XFreePixmap (_pixmap);

    // _pixmap = createPixmap(viewWidth, viewHeight);

    

    // if (clearArea)
    //    XClearArea(dpy, window, 0, 0, 0, True);   
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      MOTIF CALLBACKS LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void
ListViewPanel::exposeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "exposeCallback" << std::endl;

    ListViewPanel* listViewPanel = (ListViewPanel*)clientData;
    listViewPanel->expose(((XmScrollBarCallbackStruct*) callData)->window);
}

void
ListViewPanel::resizeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "exposeCallback" << std::endl;

    XmDrawingAreaCallbackStruct * cbs = (XmDrawingAreaCallbackStruct *) callData

    ListViewPanel* listViewPanel = (ListViewPanel*)clientData;
    listViewPanel->resize(cbs->window);
}

void
ListViewPanel::valueChangedVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "valueChangedVerticalCallback" << std::endl;

    ListViewPanel* listViewPanel = (ListViewPanel*)clientData;
    listViewPanel->scrolled(XmVERTICAL, ((XmScrollBarCallbackStruct*) callData)->value);
}

void
ListViewPanel::dragVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "dragVerticalCallback" << std::endl;

    ListViewPanel* listViewPanel = (ListViewPanel*)clientData;
    listViewPanel->scrolled(XmVERTICAL, ((XmScrollBarCallbackStruct*) callData)->value);
}

void
ListViewPanel::valueChangedHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "valueChangedHorizontalCallback" << std::endl;

    ListViewPanel* listViewPanel = (ListViewPanel*)clientData;
    listViewPanel->scrolled(XmHORIZONTAL, ((XmScrollBarCallbackStruct*) callData)->value);
}

void
ListViewPanel::dragHorizontalCallbackWidget (Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "dragHorizontalCallbackWidget" << std::endl;

    ListViewPanel* listViewPanel = (ListViewPanel*)clientData;
    listViewPanel->scrolled(XmHORIZONTAL, ((XmScrollBarCallbackStruct*) callData)->value);
}

