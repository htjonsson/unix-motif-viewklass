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

#include "FileInfo.h"

using namespace std;

void Test();
void setList(Widget w, vector<string>* strings);
void setList(Widget w, vector<string>* strings, vector<string>* tags);

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

    /*
    *label1.renderTable: bold, oblique
    *label1.renderTable.bold.renditionForeground: Green
    *label1.renderTable.bold.fontName: *-*-*-bold-*-iso8859-1
    *label1.renderTable.bold.fontType: FONT_IS_FONT
    *label1.renderTable.oblique.renditionBackground: Red
    *label1.renderTable.oblique.fontName: *-*-*-italic-*-iso8859-1
    *label1.renderTable.oblique.fontType: FONT_IS_FONT
    *label1.renderTable.oblique.underlineType: AS_IS
    *label1.renderTable.fontName: fixed
    *label1.renderTable.fontType: FONT_IS_FONT
    *label1.renderTable.renditionForegound: black
    *label1.renderTable*tabList: 1in, +1.5in, +3in
    */

    Test();

    VkApp* app = new VkApp("TabPanelApp", &argc, argv);
    // Application-specific code
    app->setDefaultResources(app->baseWidget(), defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("List - Window");
    
    // -------------------------------------------------------------------------

    Arg args[8];
    int n = 0;

    // -------------------------------------------------------------------------

    XmString label = XmStringCreateLocalized((char*)"Push here to say hello");

    n = 0;
    XtSetArg(args[n], XmNlabelString, label); n++;
    XtSetArg(args[n], XmNwidth, 400); n++;
    XtSetArg(args[n], XmNvisibleItemCount, 8); n++;
    // XtSetArg(args[n], XmNrenderTable, renderTable); n++;
    Widget pushButton_w = XmCreateScrolledList(win->mainWindowWidget(), (char*)"pushButton_w", args, n);
    XtManageChild(pushButton_w);

    XmStringFree(label);

    // -------------------------------------------------------------------------

    vector<string> poem;

    poem.push_back("Mary had a little lamb");
    poem.push_back("Its fleece was white as snow");
    poem.push_back("And everywhere that Mary went");
    poem.push_back("The lamb was sure to follow");

    vector<string> tags;

    tags.push_back("xft-label");
    tags.push_back("xft-text");
    tags.push_back("xft-menu");

    setList(pushButton_w, &poem, &tags);

    // -------------------------------------------------------------------------

    win->addView(pushButton_w);

    win->show();

    // Run the application
    app->run();  

    return 0;
}

void setList(Widget w, vector<string>* strings, vector<string>* tags)
{
    XmStringTable table = (XmStringTable) XtMalloc ((unsigned) strings->size() * sizeof (XmString));
    
    for (int i=0; i < strings->size(); i++)
    {
        XmStringTag tag = (XmStringTag)"";
        if (tags->size() > i)
        {
            tag = (XmStringTag)tags->at(i).c_str();
        }

        // https://linux.die.net/man/3/xmstringgenerate
        table[i] = XmStringGenerate((XtPointer) strings->at(i).c_str(),
                                    NULL,
                                    XmCHARSET_TEXT,
                                    tag);
    }

    XtVaSetValues(w, 
                    XmNitems, table,
                    XmNitemCount, strings->size(),
                    NULL);

    // Clean up
    for (int i=0; (int)i < strings->size(); i++)
        XmStringFree(table[i]);
    XtFree((char*) table);
}

void setList(Widget w, vector<string>* strings)
{
    vector<string> tags;

    setList(w, strings, &tags);
}

void Test()
{
    std::string currentWorkingDirectory = FileInfo::getCurrentWorkingDirectory();

    std::cout << "Current Working Directory - " << currentWorkingDirectory << std::endl;

    std::string homeDirectory = FileInfo::getHomeDirectory();

    std::cout << "Home Directory - " << homeDirectory << std::endl;

    std::vector<FileInfo*> collection;

    FileInfo::getFilesInDirectory(currentWorkingDirectory.c_str(), &collection);

    for(size_t i=0; i < collection.size(); i++)
    {    
        std::cout << "-------------------------------" << std::endl;
        
        collection[i]->printOut();
    }

    // Clean up
    for(size_t i=0; i < collection.size(); i++)
        delete collection.at(i);
    collection.clear();
}

