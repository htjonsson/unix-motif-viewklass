#include "VkGraphics.h"

#include <Vk/VkPixmap.h>

VkGraphics::VkGraphics()
{

}

VkGraphics::~VkGraphics()
{
    // Remove GC
    if (_gc != NULL && _display != NULL)
        XFreeGC(_display, _gc);

    // Clean up font map
    for(auto font : _fontMap)
    {
        if (font.second != NULL)
        {
            delete font.second;
            font.second = NULL;
        }
    } 
    _fontMap.clear();

    // Clear up color map
    for(auto color : _colorMap) 
        delete color.second;
    _colorMap.clear();    
} 

void 
VkGraphics::setWidget(Widget widget)
{
    _widget = widget;
    _display = XtDisplay(widget);
    _window = XtWindow(widget);

    if (!(_gc = XCreateGC(_display, _window, NULL, 0)))
    {
        XtError("Can't create gc.");
    }
}

Widget
VkGraphics::widget()
{
    return _widget;
}

GC
VkGraphics::gc()
{
    return _gc;
}

Window
VkGraphics::window()
{
    return _window;
}

Display*
VkGraphics::display()
{
    return _display;
}

void 
VkGraphics::clearWindow()
{
    XClearWindow(_display, _window);
}

VkFont* 
VkGraphics::getFontByName(std::string fontName)
{
    VkFont* font = new VkFont();

    if (_fontMap.count(fontName) == 0)
    {
        XFontStruct *fontInfo = NULL;

        if (!(fontInfo = XLoadQueryFont(_display, fontName.c_str())))
        {
            std::string warning("Font " + fontName + " not found");
            XtWarning(warning.c_str());
            delete font;
            return NULL;
        }

        font->setGraphics(this);
        font->setFontName(fontName);
        font->setFontStruct(fontInfo);

        _fontMap.insert(std::pair<std::string,VkFont*>(fontName, font));

        // td::cout << "[addFont] " << fontName << " added to _fontMap" << std::endl;
    }
    else
    {
        font = _fontMap.at(fontName);

        // std::cout << "[addFont] " << fontName << " font already in _fontMap" << std::endl;
    }

    return font;
}

bool
VkGraphics::setFont(std::string fontName)
{
    if (_fontMap.count(fontName) == 0)
    {
        std::string warning("Font " + fontName + " not found in map");
        XtWarning(warning.c_str());
        return false;
    }        

    if (_activeFontName != fontName)
    {
        VkFont* font = _fontMap.at(fontName);

        // Set the font
        XSetFont(_display, _gc, font->fontStruct()->fid);

        std::cout << "[setFont] " << fontName << " found in _fontMap" << std::endl;
    }
    return true;
}

Colormap
VkGraphics::getColormap()
{
    return DefaultColormap(_display, DefaultScreen(_display));
}

// ---------------------------------------------------------------------------------------
//
//      XFT STRING LOGIC - TRUE TYPE FONTS
//
// ---------------------------------------------------------------------------------------

XftColor* 
VkGraphics::getColorByNameXft(std::string colorName)
{
    XftColor* color = (XftColor*) XtMalloc((sizeof(XftColor)));

    if (_xftColorMap.count(colorName) == 0)
    {
        Colormap colormap = getColormap(); 
        Visual* visual = DefaultVisual(_display, DefaultScreen(_display));

        if (!XftColorAllocName(_display, visual, colormap, colorName.c_str(), color))
            return NULL;

        _xftColorMap.insert(std::pair<std::string, XftColor*>(colorName, color)); 

        return color;
    }
    
    return _xftColorMap.at(colorName);
}

XftFont* 
VkGraphics::getFontByNameXft(std::string fontName)
{
    if (_xftFontMap.count(fontName) == 0)
    {
        XftFont* font = XftFontOpenName(_display, DefaultScreen(_display), fontName.c_str());

        if (!font)
        {
            std::string warning("Font " + fontName + " not found");
            XtWarning(warning.c_str());
            delete font;
            return NULL;
        }
        _xftFontMap.insert(std::pair<std::string, XftFont*>(fontName, font));

        // std::cout << "[getXftFontByName] " << fontName << " added to _xftFontMap" << std::endl;

        return font;

    }

    XftFont* font = _xftFontMap.at(fontName);

    // std::cout << "[getXftFontByName] " << fontName << " font already in _xftFontMap" << std::endl;

    return font;
}

bool
VkGraphics::drawStringXft(std::string fontName, std::string colorName, Dimension x, Dimension y, std::string text)
{
    XftFont* font = getFontByNameXft(fontName);
    XftColor* color = getColorByNameXft(colorName);

    if (color != NULL && font != NULL)
    {
        Colormap colormap = getColormap();
        Visual* visual = DefaultVisual(_display, DefaultScreen(_display));

        XftDraw* draw = XftDrawCreate(_display, _window, visual, colormap);

        XftDrawStringUtf8(draw, color, font, x, y, (const FcChar8 *)text.c_str(), text.length());

        XftDrawDestroy(draw);
    }      
}

/*
// https://github.com/jsynacek/xft-example/tree/master
void
VkGraphics::drawStringXft(Dimension x, Dimension y, std::string text)
{
    Colormap colormap = getColormap();
    int screen = DefaultScreen(_display);
    Visual* visual = DefaultVisual(_display, screen);

    // XftFont* font = XftFontOpenName(_display, screen, "DejaVu Sans Mono:size=11:antialias=true");
    // XftFont* font = XftFontOpenName(_display, screen, "Helvetica:size=10:antialias=true");
    XftFont* font = XftFontOpenName(_display, screen, "Verdan:style=Bold:pixelsize=10:antialias=true");

    if (!font)
        XtError("cannot load font\n");

    XftColor color;
    // if (!XftColorAllocName(_display, visual, colormap, "#0000ee", &color))
    if (!XftColorAllocName(_display, visual, colormap, "black", &color))
        XtError("cannot allocate xft color\n");
    
    XftDraw* draw = XftDrawCreate(_display, _window, visual, colormap);

    XftDrawStringUtf8(draw, &color, font, x, y, (const FcChar8 *)text.c_str(), text.length());

    // Clean up
    XftColorFree(_display, visual, colormap, &color);
    XftDrawDestroy(draw);    
}
*/

// ---------------------------------------------------------------------------------------
//
//      STRING LOGIC
//
// ---------------------------------------------------------------------------------------

void
VkGraphics::drawString(Dimension x, Dimension y, std::string text)
{
    XDrawString(_display, _window, _gc, x, y, text.c_str(), text.length());    
}

bool
VkGraphics::drawString(std::string fontName, std::string colorName, Dimension x, Dimension y, std::string text)
{
    if (NULL == getFontByName(fontName))
        return false;

    setFont(fontName);
    setForegroundColor(colorName);
    drawString(x, y, text);
    
    return true;
}

// ---------------------------------------------------------------------------------------
//
//      LINE  LOGIC
//
// ---------------------------------------------------------------------------------------

void 
VkGraphics::drawLine(int x1, int y1, int x2, int y2, std::string colorName)
{
    setForegroundColor(colorName);
    XDrawLine(_display, _window, _gc, x1, y1, x2, y2);
}

void 
VkGraphics::drawHorizontalLine(int x1, int x2, int y, std::string colorName)
{
    drawLine(x1, y, x2, y, colorName);
}

// ---------------------------------------------------------------------------------------
//
//      RECTANGLE  LOGIC
//
// ---------------------------------------------------------------------------------------

void
VkGraphics::drawRectangle(XRectangle rectangle, std::string colorName)
{
    setForegroundColor(colorName);
    drawRectangle(rectangle);
}

void
VkGraphics::drawRectangle(Dimension x, Dimension y, Dimension width, Dimension height)
{
    XDrawRectangle(_display, _window, _gc, x, y, width, height);
}

void
VkGraphics::drawRectangle(XRectangle rectangle)
{
    XDrawRectangle(_display, _window, _gc, rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

void
VkGraphics::fillRectangle(XRectangle rectangle, std::string colorName)
{
    setForegroundColor(colorName);
    fillRectangle(rectangle);
}

void
VkGraphics::fillRectangle(XRectangle rectangle)
{
    XFillRectangle(_display, _window, _gc, rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

void
VkGraphics::fillRectangle(Position x, Position y, Dimension width, Dimension height)
{
    XFillRectangle(_display, _window, _gc, x, y, width, height);
}

// ---------------------------------------------------------------------------------------
//
//      COLOR HANDLING
//
// ---------------------------------------------------------------------------------------

XColor* 
VkGraphics::getColorByName(std::string colorName)
{
    XColor* color = (XColor*) XtMalloc((sizeof(XColor)));

    if (_colorMap.count(colorName) == 0)
    {
        Colormap colormap = getColormap();     

        XParseColor(_display, colormap, colorName.c_str(), color);
        XAllocColor(_display, colormap, color);

        _colorMap.insert(std::pair<std::string, XColor*>(colorName, color)); 
    }
    else
    {
        color = _colorMap.at(colorName);
    }

    return color;
}

void
VkGraphics::setForegroundColor(XColor* color)
{
    setForegroundColor(color->pixel);
} 

void 
VkGraphics::setForegroundColor(Pixel pixel)
{
    XSetForeground(_display, _gc, pixel);
}

void 
VkGraphics::setForegroundColor(std::string colorName)
{
    XColor* color = getColorByName(colorName);

    setForegroundColor(color);
}

void
VkGraphics::setBackgroundColor(XColor* color)
{
    setBackgroundColor(color->pixel);
} 

void 
VkGraphics::setBackgroundColor(Pixel pixel)
{
    XSetBackground(_display, _gc, pixel);
}

void 
VkGraphics::setBackgroundColor(std::string colorName)
{
    XColor* color = getColorByName(colorName);

    setBackgroundColor(color);
}

// ---------------------------------------------------------------------------------------
//
//      PIXMAP HANDLING
//
// ---------------------------------------------------------------------------------------

Pixmap 
VkGraphics::getPixmapByName(std::string pixmapName, std::string pixmapData)
{
    if (_pixmapMap.count(pixmapName) == 0)
    {
        Pixmap pixmap = VkCreateXPMPixmap(_widget, pixmapData.c_str(), NULL);

        _pixmapMap.insert(std::pair<std::string, Pixmap>(pixmapName, pixmap)); 

        return pixmap;
    }
    
    return _pixmapMap.at(pixmapName);
}

Pixmap 
VkGraphics::getPixmap(std::string pixmapName)
{
    if (_pixmapMap.count(pixmapName) == 0)
        return 0;

    return _pixmapMap.at(pixmapName);
}

void 
VkGraphics::setPixmap(std::string pixmapName, Pixmap pixmap)
{
    if (_pixmapMap.count(pixmapName) == 0)
        _pixmapMap.insert(std::pair<std::string, Pixmap>(pixmapName, pixmap)); 
}

void 
VkGraphics::draw(std::string pixmapName, unsigned int width, unsigned int height, int dest_x, int dest_y)
{
    Pixmap pixmap = getPixmap(pixmapName);

    if (pixmap != 0)
        draw(pixmap, width, height, dest_x, dest_y);
}

void 
VkGraphics::draw(Pixmap pixmap, unsigned int width, unsigned int height, int dest_x, int dest_y)
{
    XCopyArea(_display, pixmap, _window, _gc, 0, 0, width, height, dest_x, dest_y);
}

