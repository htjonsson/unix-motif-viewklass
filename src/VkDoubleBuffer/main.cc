#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/DrawingA.h>
#include <Xm/Label.h>
#include <Vk/VkApp.h>
#include <iostream>
#include "IView.h"

using namespace std;

static void inputCallback(Widget widget, XtPointer userdata, XmDrawingAreaCallbackStruct* calldata)
{
    XEvent *event = calldata->event;
    if (event->xany.type == ButtonPress)
    {
        ((IView*)userdata)->update();
    }
}

// Application-specific setup
int main ( int argc, char **argv )
{
	const char* const defaultResources[] = {
		"+*background : gray80",
        "*renderTable : xft",
        "*xft.fontType : FONT_IS_XFT",
        "*xft.fontName : helvetica",
        "*xft.fontSize : 12",
        "*xft.fontStyle : regular",
		NULL,
	};

    VkApp* app = new VkApp("DoubleBufferApp", &argc, argv);

    app->setDefaultResources(app->baseWidget(), defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("VkDoubleBuffer - App");

    IView* iview = new IView((char*)std::string("interface_view").c_str(), win->mainWindowWidget());

    XtVaSetValues (iview->baseWidget(),
        XmNheight, 800,
        XmNwidth, 600,
        NULL);

    XtAddCallback(iview->baseWidget(), XmNinputCallback, (XtCallbackProc)inputCallback, (XtPointer)iview);

    win->addView(iview);
    iview->update();

    win->show();
    app->run();  // Run the application

    return 0;
}