// Motif 
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/List.h>
// ViewKlass
#include <Vk/VkApp.h>
#include <Vk/VkSimpleWindow.h>
// Standard C/C++
#include <stdio.h>
#include <iostream>
#include <vector>

#include "ListViewPanel.h"
#include "ListViewPanelDelegate.h"

using namespace std;

// Application-specific setup
int main ( int argc, char **argv )
{
	const char* const defaultResources[] = {
        "*foreground: #000000",
        "*highlightColor: red",
        "*background: #c1c1c1",
        "*renderTable : xft, xft-menu, xft-label, xft-text",
        // BASE FONT
        "*xft.fontType : FONT_IS_XFT",
        "*xft.fontName : helvetica",
        "*xft.fontSize : 10",
        // SGI MENU FONT
        "*xft-menu.fontType : FONT_IS_XFT",
        "*xft-menu.fontName: helvetica",
        "*xft-menu.fontSize : 10",
        "*xft-menu.fontStyle : bold italic",
        "*xft-menu.renditionForeground : red",
        // SGI LABEL FONT
        "*xft-label.fontType : FONT_IS_XFT",
        "*xft-label.fontName: helvetica",
        "*xft-label.fontSize : 10",
        "*xft-label.fontStyle : bold italic",
        // SGI TEXT FONT
        "*xft-text.fontType : FONT_IS_XFT",
        "*xft-text.fontName: helvetica",
        "*xft-text.fontSize : 12",
        // SGI SUB-TEXT FONT    
        "*xft-sub-text.fontType : FONT_IS_XFT",
        "*xft-sub-text.fontName: helvetica",
        "*xft-sub-text.fontSize : 10",   
        // PUSH BUTTON
        "*XmPushButton*background: #999999",
        "*XmPushButton*topShadowColor: #e6e6e6",
        "*XmPushButton*bottomShadowColor: #4c4c4c",
        "*XmPushButton*renderTable : xft-menu",
        // PUSH BUTTON GADGET
        "*XmPushButtonGadget*background: #999999",
        "*XmPushButtonGadget*topShadowColor: #e6e6e6",
        "*XmPushButtonGadget*bottomShadowColor: #4c4c4c",
        // TEXT FIELD
        "*XmTextField*background: #b98e8e",
        // TEXT
        "*XmText*background: #b98e8e",
        // MENUBAR
        "*menuBar*XmPushButton.marginHeight: 2",
        "*menuBar*XmPushButton.marginWidth: 9",
        "*menuBar*XmCascadeButton.marginHeight: 2",
        "*menuBar*XmCascadeButton.marginWidth: 9",
        "*menuBar*XmToggleButton.marginHeight: 2",
        "*menuBar*XmToggleButton.marginWidth: 9",
        "*menuBar.marginHeight: 0",
        // LIST
        "*XmList*highlightThickness: 0",
        "*XmList.listMarginWidth: 3",
        "*XmList.listSpacing: 2",
        // "*XmList*background: #999999",
        "*XmList*background: #719c9c",
        // SCROLLBAR
        "*XmScrollBar*sliderMark: XmTHUMB_MARK",
        "*XmScrollBar*width: 20",
        "*XmScrollBar*height: 20",
        // TOGGLE BUTTON
        "*XmToggleButton*indicatorOn: XmINDICATOR_CHECK_BOX",
        "*XmToggleButton*indicatorSize: 16",
        // TOGGLE BUTTON GADGET
        "*XmToggleButtonGadget*indicatorOn: XmINDICATOR_CHECK_BOX",
        "*XmToggleButtonGadget*indicatorSize: 16",
		NULL,
	};

    VkApp* app = new VkApp("TabPanelApp", &argc, argv);
    // Application-specific code
    app->setDefaultResources(app->baseWidget(), defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("List - Window");
    
    ListViewPanelDelegate delegate;
    delegate.setNumberOfRows(8);
    delegate.setHeightOfRow(72);

    ListViewPanel panel("list_view_panel", win->mainWindowWidget(), &delegate);
 
    win->addView(panel);

    XtVaSetValues(win->mainWindowWidget(), XmNwidth, 800, XmNheight, 600, NULL);

    win->show();

    // Run the application
    app->run();  

    return 0;
}

