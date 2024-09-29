#include "EZ.h"

#include <iostream>

void 
EZ::IsManaged(Widget widget, std::string name)
{
    if (XtIsManaged(widget) == FALSE)
    {
        std::cout << "Widget [" + name + "] is not managed" << std::endl;
    }
}

// ---------------------------------------------------------------------------------------
//
//      RECTANGLE  LOGIC
//
// ---------------------------------------------------------------------------------------

void
EZ::inflate(XRectangle *rectangle, int inflate)
{
    EZ::inflate(rectangle, inflate, inflate);
}

void
EZ::inflate(XRectangle *rectangle, int width, int height)
{
    rectangle->x -= width;
    rectangle->width += width;
    rectangle->y -= height;
    rectangle->height += height;
}

XRectangle 
EZ::ofRectangle(XRectangle offset, int x, int y, int width, int height)
{
    XRectangle r;
    r.x = offset.x + x;
    r.y = offset.y + y;
    r.width = width;
    r.height = height;
    return r;
}

XRectangle 
EZ::makeRectangle(int x, int y, int width, int height)
{
    XRectangle r;
    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;
    return r;
}

XRectangle 
EZ::makeZerodRectangle()
{
    return makeRectangle(0, 0, 0, 0);
}