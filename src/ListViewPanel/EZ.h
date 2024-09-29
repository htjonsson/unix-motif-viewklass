#ifndef EZ_HEADER
#define EZ_HEADER

#include <Xm/Xm.h>
#include <string>

struct EZ
{
public:
     static void IsManaged(Widget widget, std::string name);

public:
     static void inflate(XRectangle *rectangle, int inflate);
     static void inflate(XRectangle *rectangle, int height, int width);
     static XRectangle makeRectangle(int x, int y, int width, int height);
     static XRectangle makeZerodRectangle();
     static XRectangle ofRectangle(XRectangle offset, int x, int y, int width, int height);
};

#endif // EZ_HEADER