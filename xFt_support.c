/*
    xFt_support.c

    The support of the XFT library introduced in OpenMotif 2.3 offers user’s the ability to use 
    client-side anti-aliased fonts from Motif applications. This feature is available via the new 
    Rendition Font Type, named XmFONT_IS_XFT. 
    The following sample shows how to specify the definition of the default RenderTable with the 
    new Font Type:
*/

#include <Xm/XmAll.h>

String fallback[] = {
    "*label.renderTable: three",
    "*three.fontType: FONT_IS_XFT",
    "*three.fontName: Times",
    "*label.labelType: XmPIXMAP_AND_STRING",
    "*label.labelPixmap: toucan.png",
    "*label.labelString: specified from resources",
    NULL
};

int
main(int argc, char *argv[]) {
Widget toplevel, rowcolumn;
Arg al[10];
Cardinal ac;
XtAppContext app;
XmString str;
Pixmap pixmap;


    XtSetLanguageProc(NULL, NULL, NULL);

    Widget toplevel = XtAppInitialize(&app, "test", NULL, 0, &argc, argv, fallback, NULL, 0);
 
    /*--------------------------------------------------------------------------------------*/

    XtSetArg(al[ac], XmNorientation, XmVERTICAL); ac++;
    Widget rowcolumn = XmCreateRowColumn(toplevel, "rowcolumn", al, ac);
    XtCreateManagedWidget("label", xmLabelWidgetClass, rowcolumn, NULL, 0);
 
    XtCreateManagedWidget("sep", xmSeparatorWidgetClass, rowcolumn, NULL, 0);
 
    /* Look for value of cyan color */
    XColor color, exact;
    XAllocNamedColor(XtDisplay(toplevel), DefaultColormap(XtDisplay(toplevel), DefaultScreen(XtDisplay(toplevel))), "cyan", &color, &exact);

    Pixmap pixmap = XmGetPixmap(XtScreen(toplevel), "toucan.png", XmUNSPECIFIED_PIXEL, XmUNSPECIFIED_PIXEL);
 
    XmString str = XmStringCreateLocalized("specified from code");
 
    XtSetArg(al[ac], XmNlabelType, XmPIXMAP_AND_STRING); ac++;
    XtSetArg(al[ac], XmNlabelPixmap, pixmap); ac++;
    XtSetArg(al[ac], XmNlabelString, str); ac++;
    XtCreateManagedWidget("label", xmLabelWidgetClass, rowcolumn, al, ac);
 
    XmStringFree(str);
   
    XtManageChild(rowcolumn);

    /*--------------------------------------------------------------------------------------*/

    XtRealizeWidget(toplevel);
 
    XtAppMainLoop(app);
}
