#include "IView.h"
#include "images/visualage.xpm"
#include "images/sgi.xpm"

using namespace std;

IView::IView(const char* name, Widget parent)
:   VkDoubleBuffer(name, parent),
    _visualState(-1)
{
}

IView::~IView()
{
}

void 
IView::draw()
{
    Display* display = XtDisplay(this->baseWidget());
    
    if (_visualState == -1)
    {
        _vaPixmap = VkCreateXPMPixmap(this->baseWidget(), visualage, NULL);
        _sgiPixmap = VkCreateXPMPixmap(this->baseWidget(), sgi, NULL);

        _visualState = 0;
    }
 
    XGCValues gcv;
    gcv.foreground = BlackPixelOfScreen(XtScreen(this->baseWidget()));

    Screen* screen = XtScreen(_baseWidget);
    GC gc = XCreateGC(display, RootWindowOfScreen(screen), 0, &gcv);

    if (_visualState == 1) 
    {
        XCopyArea(display, _vaPixmap, this->_canvas, gc, 0, 0, 218, 218, 50, 50);
        _visualState = 2;
    }
    else
    {
        XCopyArea(display, _sgiPixmap, this->_canvas, gc, 0, 0, 300, 243, 50, 50);
        _visualState = 1;
    }

    // Clean up
    XFreeGC(display, gc);

    VkDoubleBuffer::draw();
}