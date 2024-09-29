#ifndef LIST_VIEW_PANEL
#define LIST_VIEW_PANEL

#include <Vk/VkComponent.h>
#include <Xm/Xm.h>
#include "ListViewPanelDelegate.h"

class ListViewPanel : public VkComponent
{
private:
    Widget _drawingArea;
    Widget _verticalScrollbar;
    Widget _horizontalScrollbar;

private:
    VkGraphics graphics;

private:
    Dimension _rowHeight = 30;
    Dimension _rowWidth = 0;

    int _numberOfRowsVisible = 1;
    int _numberOfRows = 1;
    int _offsetRows = 0;

private:
    ListViewPanelDelegate* _delegate = NULL;

public:
    ListViewPanel(const char *name, Widget parent, ListViewPanelDelegate *delegate);
    ~ListViewPanel();

private:
  void createWidget(const char *name, Widget parent);  

public:
    void setDelegate(ListViewPanelDelegate* delegate);
    ListViewPanelDelegate* delegate();

public:
    void setNumberOfRows(int numberOfRows);
    int numnberOfRows();

    void setHeightOfRow(int heightOfRow);

private:
    // Pixmap _pixmap = NULL;
    Pixmap createPixmap(Dimension width, Dimension height);

private:    
    GC createGraphicsContextByPixmap(Pixmap pixmap);
    GC createGraphicsContextByWindow(Window window);

private:
    void setupUserInterface(Widget w);

private:
    void redraw(Window window);

public:
    void setRowsVisible(Dimension height);

private:
    void handleScrolled(int orientation, int value);
    void handleExpose(Window window); 
    void handleResize(Window window);   
    void handleEvent(XEvent* event);  
    void handleButtonPressed(XButtonPressedEvent* event);

private:
    static void inputCallback(Widget widget, XtPointer clientData, XtPointer callData);
    static void exposeCallback(Widget widget, XtPointer clientData, XtPointer callData); 
    static void resizeCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData);     
};

#endif // LIST_VIEW_PANEL