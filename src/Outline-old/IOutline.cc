#include "IOutline.h"
#include <iostream>
#include <Vk/VkPixmap.h>
#include "images/expanded.xpm"
#include "images/collapsed.xpm"

using namespace std;

IOutline::IOutline(const char* name, Widget parent)
:   VkComponent(name)
{
    _baseWidget = createContainer(parent);

    // Setup callbacks
    XtAddCallback(_baseWidget, XmNselectionCallback, (XtCallbackProc)selectionCallback, (XtPointer)this);
    XtAddCallback(_baseWidget, XmNoutlineChangedCallback, (XtCallbackProc)outlineChangedCallback, (XtPointer)this);
}

IOutline::~IOutline()
{
}

Widget
IOutline::createContainer(Widget parent)
{
    Pixmap expandedPixmap = VkCreateXPMPixmap(parent, expanded, NULL);
    Pixmap collapsedPixmap = VkCreateXPMPixmap(parent, collapsed, NULL);

    Display* display = XtDisplay(parent);
    Colormap colormap = DefaultColormap(display, DefaultScreen(display));

    XColor color;
    color.red = 153 * 256;      // HEX 99
    color.green = 187 * 256;    // HEX BB
    color.blue = 188 * 256;     // HEX BC
    color.flags = DoRed | DoGreen | DoBlue;

    XAllocColor(display, colormap, &color);
    _backgroundColor = color.pixel;

    // https://linux.die.net/man/3/xmcontainer
    Widget container = XtVaCreateManagedWidget("Container",
                xmContainerWidgetClass, parent,
                XmNlayoutType, XmOUTLINE,
                XmNselectionPolicy, XmBROWSE_SELECT,
                XmNautomaticSelection, XmNO_AUTO_SELECT,
                XmNexpandedStatePixmap, expandedPixmap,
                XmNcollapsedStatePixmap, collapsedPixmap,
                XmNoutlineButtonPolicy, XmOUTLINE_BUTTON_PRESENT,
                XmNoutlineLineStyle, XmNO_LINE, 
                XmNoutlineIndentation, 20,
                XmNshadowThickness, 0,
                XmNborderWidth, 0,
                XmNbackground, _backgroundColor,
                // XmNforeground, _backgroundColor,
                XmNtopShadowColor, _backgroundColor,
                XmNbottomShadowColor, _backgroundColor,
                // XmNhighlightColor, _backgroundColor,
                NULL);


    Widget president       = createRootNode(container, "President", true);
    Widget vice_president  = createNode(container, "ice-President", president);
    Widget dir_of_sales    = createNode(container, "Director of Sales", vice_president);
    Widget dir_of_rnd      = createNode(container, "Director of R&D", dir_of_sales);
                             createNode(container, "Director of Manufacturing", dir_of_rnd);

    // Clean up pixmaps
    // XFreePixmap(display, expandedPixmap);
    // XFreePixmap(display, collapsedPixmap);

    return container;
}

Widget
IOutline::createNode(Widget parent, const char* text, Widget parentNode)
{
    Widget widget;

    widget = XtVaCreateManagedWidget(text,
                xmIconGadgetClass, parent,
                XmNentryParent, parentNode,
                XmNshadowThickness, 0,
                XmNmarginBottom, 0,
                XmNbackground, _backgroundColor,
                XmNspacing, 0,
                XmNuserData, text,
                NULL);

    return widget;
}


Widget
IOutline::createRootNode(Widget parent, const char* text, bool expaned)
{
    Widget widget;

    if (expaned == true) 
    {
        widget = XtVaCreateManagedWidget(text,
                    xmIconGadgetClass, parent,
                    XmNoutlineState, XmEXPANDED,
                    XmNshadowThickness, 0,
                    XmNbackground, _backgroundColor,
                    XmNuserData, text,
                    XmNspacing, 0,
                    NULL);       
    }
    else
    {
        widget = XtVaCreateManagedWidget(text,
                    xmIconGadgetClass, parent,
                    XmNoutlineState, XmEXPANDED,
                    XmNshadowThickness, 0,
                    XmNbackground, _backgroundColor,
                    XmNuserData, text,
                    XmNspacing, 0,
                    NULL);     
    }

    return widget;
}

// ---------------------------------------------------------------------------------------------------------------------
//
//        MOTIF CALLBACKS LOGIC
//
// ---------------------------------------------------------------------------------------------------------------------

void 
IOutline::selectionCallback(Widget widget, XtPointer userdata, XmContainerSelectCallbackStruct* calldata)
{
    std::cout << "selectionCallback" << endl;

    std::cout << "selected_item_count " << calldata->selected_item_count << endl;

    if (calldata->selected_item_count > 0)
    {
        std::cout << "selected_items " << calldata->selected_items[0] << endl;
        std::cout << "auto_selection_type " << calldata->auto_selection_type << endl;

        XtPointer userData;

        XtVaGetValues (calldata->selected_items[0],
            XmNuserData, &userData,
            NULL);

        std::cout << "User data " << (const char*) userData << endl;
    }
}

void 
IOutline::outlineChangedCallback(Widget widget, XtPointer userdata, XmContainerOutlineCallbackStruct* calldata)
{
    std::cout << "outlineChangedCallback" << endl;
}