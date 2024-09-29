#include "VkFont.h"

void 
VkFont::setGraphics(VkGraphics* graphics)
{
     _graphics = graphics;
}

void 
VkFont::setFontName(std::string fontName)
{
     _fontName = fontName;
}

void 
VkFont::setFontStruct(XFontStruct* fontStruct)
{
     _fontStruct = fontStruct;
}

std::string
VkFont::fontName()
{
     return _fontName;
}

XFontStruct* 
VkFont::fontStruct()
{
     return _fontStruct;
}

