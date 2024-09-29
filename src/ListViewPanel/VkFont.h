#ifndef VK_FONT
#define VK_FONT

#include <X11/Xft/Xft.h>
#include <Xm/Xm.h>
#include <string>
#include <iostream>
#include <map>

class VkGraphics;

class VkFont
{
private:
     VkGraphics*    _graphics;
     std::string    _fontName;
     XFontStruct*   _fontStruct;

public:
     void setGraphics(VkGraphics* graphics);
     void setFontName(std::string fontName);
     void setFontStruct(XFontStruct* fontStruct);

public:
     std::string fontName();     
     XFontStruct* fontStruct();
};

#endif // VK_FONT