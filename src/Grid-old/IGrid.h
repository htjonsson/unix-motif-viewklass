#ifndef IGRID_H
#define IGRID_H

#include <Vk/VkComponent.h>
#include <Xm/Xm.h>
#include <Xm/Container.h>
#include <Xm/IconG.h>

using namespace std;

class IGrid : public VkComponent 
{
public:
    IGrid(const char *name, Widget parent);
    ~IGrid();

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

#endif // IGRID_H