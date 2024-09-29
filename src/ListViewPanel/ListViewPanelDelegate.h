#ifndef LIST_VIEW_PANEL_DELEGATE
#define LIST_VIEW_PANEL_DELEGATE

#include "VkGraphics.h"
#include <Xm/Xm.h>


class ListViewPanelDelegate
{
public:
    ListViewPanelDelegate();
    ~ListViewPanelDelegate();

private:
    int _numberOfRows;

public:
    int numberOfRows();
    void setNumberOfRows(int numberOfRows);

private:
    int _heightOfRow;

public:
    int heightOfRow();
    void setHeightOfRow(int heightOfRow);

public:
    void draw(int rowId, VkGraphics* graphics, XRectangle rectangle);
};

#endif // LIST_VIEW_PANEL_DELEGATE