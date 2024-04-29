/*
advanced_image_support.c

Added support of PNG and JPEG images in Motif 2.3 allows users to specify images of these 
types to pixmap resources, as well as load these images using Pixmap loading functions such as 
XmGetPixmap()
*/

#include <Xm/XmAll.h>

String fallback[] = {
    "*label.labelType: XmPIXMAP",
    "*label.labelPixmap: toucan.png",
    NULL
};

int
main(int argc, char *argv[]) {
    XtAppContext app;

    XtSetLanguageProc(NULL, NULL, NULL);

    Widget toplevel = XtAppInitialize(&app, "test", NULL, 0, &argc, argv, fallback, NULL, 0);

    /*--------------------------------------------------------------------------------------*/

    Arg al[10];
    Cardinal ac;

    XtSetArg(al[ac], XmNorientation, XmVERTICAL); ac++;
    Widget rowcolumn = XmCreateRowColumn(toplevel, "rowcolumn", al, ac);

    XtCreateManagedWidget("label", xmLabelWidgetClass, rowcolumn, NULL, 0);

    XtCreateManagedWidget("sep", xmSeparatorWidgetClass, rowcolumn, NULL, 0);

    Pixmap pixmap = XmGetPixmap(XtScreen(toplevel), "toucan.jpg", XmUNSPECIFIED_PIXEL, XmUNSPECIFIED_PIXEL);
 
    XtSetArg(al[ac], XmNlabelType, XmPIXMAP); ac++;
    XtSetArg(al[ac], XmNlabelPixmap, pixmap); ac++;
    XtCreateManagedWidget("label", xmLabelWidgetClass, rowcolumn, al, ac);
 
    XtManageChild(rowcolumn);

    /*--------------------------------------------------------------------------------------*/

    XtRealizeWidget(toplevel);

    XtAppMainLoop(app);
} 
