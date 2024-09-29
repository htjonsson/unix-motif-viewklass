#include "ListViewPanelDelegate.h"

#include "EZ.h"
#include "images/workstation_sgi.xpm"
#include "images/workstation_sparc.xpm"

#include <Vk/VkPixmap.h>
#include <Xm/Xm.h>
#include <X11/Xlib.h>
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

ListViewPanelDelegate::ListViewPanelDelegate()
{
    _numberOfRows = 0;
    _heightOfRow = 72;
}

ListViewPanelDelegate::~ListViewPanelDelegate()
{

}

// --------------------------------------------------------------------------------------------------------------------------

int 
ListViewPanelDelegate::numberOfRows()
{
    return _numberOfRows;
}

void
ListViewPanelDelegate::setNumberOfRows(int numberOfRows)
{
    _numberOfRows =  numberOfRows;
}

int 
ListViewPanelDelegate::heightOfRow()
{
    std::cout << "ListViewPanelDelegate::heightOfRow() " << _heightOfRow << endl; 

    return _heightOfRow;;
}

 void 
 ListViewPanelDelegate::setHeightOfRow(int heightOfRow)
 {
    _heightOfRow = heightOfRow;
 }

// --------------------------------------------------------------------------------------------------------------------------

void 
ListViewPanelDelegate::draw(int rowId, VkGraphics* g, XRectangle rectangle)
{
    /*
        helvetica
        courier
        lucida
        times


        VkFontBuilder fb();
        fb.setFamily("helvetica");
        fb.setAsBold();
        fb.setFontSize(12);
        "-*-helvetica-bold-r-*-*-12-*-*-*-*-*-*-*" == tb.toString();

        fb.Init();
        fb.setFamily("helvetica");
        fb.setFontSize(12);
        "-*-helvetica-bold-r-*-*-12-*-*-*-*-*-*-*" == tb.toString();         
    */

    // title
    XRectangle rect = EZ::ofRectangle(rectangle, 60, 18, 300, 13);

    stringstream ss;
    ss << "[" << rowId << "] - Ant Design Title 2"; 
    
    std::string fontName("Verdan:style=Bold:pixelsize=10:antialias=true");
    std::string colorName("black");

    g->drawStringXft(fontName, colorName, rect.x, rect.y+rect.height-2, ss.str());

    // text
    rect = EZ::ofRectangle(rectangle, 60,44, 300, 13);

    std::string fontName2("Verdan:pixelsize=10:antialias=true");
    std::string colorName2("gray55");

    g->drawStringXft(fontName2, colorName2, rect.x, rect.y+rect.height-2, "Ant Design, a design language for background apllications, is refined by Ant UED Team");

    // image
    rect = EZ::ofRectangle(rectangle, 6, 15, 48, 48);
    g->drawRectangle(rect, "green");

    g->getPixmapByName("sun", _workstation_sparc);

    g->draw("sun", 48, 48, rect.x, rect.y);    
}