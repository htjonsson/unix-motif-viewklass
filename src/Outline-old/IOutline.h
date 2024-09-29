#ifndef IOUTLINE_H
#define IOUTLINE_H

#include <Vk/VkComponent.h>
#include <Xm/Xm.h>
#include <Xm/Container.h>
#include <Xm/IconG.h>

using namespace std;

class IOutline : public VkComponent 
{
public:
    IOutline(const char *name, Widget parent);
    ~IOutline();

private:
    Widget createNode(Widget parent, const char* text, Widget parentNode);
    Widget createRootNode(Widget parent, const char* text, bool expaned = false);
    Widget createContainer(Widget parent);

private:
    Pixel _backgroundColor;

private:
    // Motif callbacks
    static void selectionCallback(Widget widget, XtPointer userdata, XmContainerSelectCallbackStruct* calldata);    
    static void outlineChangedCallback(Widget widget, XtPointer userdata, XmContainerOutlineCallbackStruct* calldata);
};

#endif // IOUTLINE_H