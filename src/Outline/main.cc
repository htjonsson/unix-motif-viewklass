#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/DrawingA.h>
#include <Xm/Label.h>
#include <Vk/VkApp.h>
#include <iostream>
#include "IOutline.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>

using namespace std;

// Application-specific setup
int main ( int argc, char **argv )
{
	const char* const defaultResources[] = {
		"+*background : gray80",
        "*renderTable : xft",
        "*xft.fontType : FONT_IS_XFT",
        "*xft.fontName : helvetica",
        "*xft.fontSize : 10",
        "*xft.fontStyle : regular",
		NULL,
	};

    VkApp* app = new VkApp("OutlineApp", &argc, argv);

    app->setDefaultResources(app->baseWidget(), defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("IOutline - App");

    IOutline* view = new IOutline((char*)std::string("outline").c_str(), win->mainWindowWidget());

    XtVaSetValues (view->baseWidget(),
        XmNheight, 800,
        XmNwidth, 600,
        NULL);

    win->addView(view);

    win->show();
    app->run();  // Run the application

    return 0;
}