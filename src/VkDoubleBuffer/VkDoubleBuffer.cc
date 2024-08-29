#include "VkDoubleBuffer.h"

using namespace std;

VkDoubleBuffer::VkDoubleBuffer(const char* name, Widget parent)
:   VkComponent(name)
{
    createWidget(name, parent);
}

VkDoubleBuffer::~VkDoubleBuffer()
{
    XFreePixmap(XtDisplay(_baseWidget), _canvas);
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

// ---------------------------------------------------------------------------------------------------------------------
//
//        DEFAULT DRAWING LOGIC
//
// ---------------------------------------------------------------------------------------------------------------------

void 
VkDoubleBuffer::resize()
{
    update();
}

void 
VkDoubleBuffer::update()
{
    XtVaGetValues(_baseWidget, XmNheight, &_height, XmNwidth, &_width, NULL);

    Display* display = XtDisplay(_baseWidget);
    XFreePixmap(display, _canvas);

    _canvas = createPixmap(_baseWidget, _width, _height);

    draw();
    swapBuffers();
}

void 
VkDoubleBuffer::draw()
{
}

void
VkDoubleBuffer::swapBuffers()
{
    XtVaSetValues(_baseWidget, XmNbackgroundPixmap, _canvas, NULL);
}

// ---------------------------------------------------------------------------------------------------------------------
//
//        UTILITY METHODS
//
// ---------------------------------------------------------------------------------------------------------------------

Pixmap
VkDoubleBuffer::createPixmap(Widget widget, int width, int height)
{
    int depth = DefaultDepthOfScreen(XtScreen(widget));
    Screen* screen = XtScreen(_baseWidget); 

    Pixmap pixmap = XCreatePixmap(XtDisplay(widget), RootWindowOfScreen(screen), width, height, depth);

    switch (pixmap)
    {
        case BadAlloc:      std::cout << "[createPixmap] BadAlloc" << endl; break;
        case BadDrawable:   std::cout << "[createPixmap] BadDrawable" << endl; break;
        case BadValue:      std::cout << "[createPixmap] BadValue" << endl; break;
        default:            break;
    }

    return pixmap;
}




