/*****************************************************************
    ViewKlass - C++ framework library for Motif

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: resourceTest.cc,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>
#include <sstream>

#include <string.h>

#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/TextF.h>

#include <Vk/VkApp.h>
#include <Vk/VkOptionMenu.h>
#include <Vk/VkSubMenu.h>
#include <Vk/VkWindow.h>
#include <Vk/VkAlignmentGroup.h>
#include <Vk/VkWarningDialog.h>

#include <X11/Xmu/Editres.h>

using namespace std;

const char* const defaultResources[] = {
	"*Application.labelString: File",
	"*Application.mnemonic: F",
	"*XmLabel.alignment: ALIGNMENT_END",
	"*marginHeight: 1",
	NULL,
};

Widget resourceName;
Widget resourceClass;
Widget resourceDef;
VkOptionMenu* option1;
VkApp* app;

void
optionCallback(Widget w, XtPointer clientData, XtPointer callData)
{
	cout << "optionCallback(";
	cout << "clientData " << (const char*)clientData;
	cout << ", callData " << callData << ")" << endl;

	char* name;
	char* className;
	char* defaultVal;
	XtVaGetValues(resourceName, XmNvalue, &name, NULL);
	XtVaGetValues(resourceClass, XmNvalue, &className, NULL);
	XtVaGetValues(resourceDef, XmNvalue, &defaultVal, NULL);
	
	XtPointer res = VkGetResource(app->baseWidget(),
								  name, className,
								  (const char*)clientData, defaultVal);

	if (!strcmp((char*)clientData, XmRBoolean)) {
		Boolean x = (long)res; // cast to int to avoid compiler warning
		cout << "Boolean = " << (x ? "true" : "false") << endl;
	}
	
	if (!strcmp((char*)clientData, XmRCardinal)) {
		Cardinal x = ((Cardinal)((long)res));
		cout << "Cardinal = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRDimension)) {
		Dimension x =
			(unsigned long)res; // cast to int to avoid compiler warning
		cout << "Dimension = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRFloat)) {
		float x;
		memcpy(&x, &res, sizeof(x));
		cout << "float = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRFontList)) {
		XmFontList x = (XmFontList)res;
		cout << "FontList = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRInt)) {
		int x = (long)res;
		cout << "int = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRPixel)) {
		Pixel x = (Pixel)res;
		cout << "Pixel = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRPixmap)) {
		Pixmap x = (Pixmap)res;
		cout << "Pixmap = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRPosition)) {
		Position x = (long)res; // cast to int to avoid compiler warning
		cout << "Position = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRShort)) {
		short x = (long)res; // cast to int to avoid compiler warning
		cout << "short = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRString)) {
		String x = (String)res;
		cout << "String = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRUnsignedChar)) {
		unsigned char x =
			(unsigned long)res; // cast to int to avoid compiler warning
		cout << "unsigned char = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRWidget)) {
		Widget x = (Widget)res;
		cout << "Widget = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRWindow)) {
		Window x = (Window)res;
		cout << "Window = " << x << endl;
	}
	
	if (!strcmp((char*)clientData, XmRXmString)) {
		XmString x = (XmString)res;
		cout << "XmString = " << x << endl;
		char* str;
		Boolean b = XmStringGetLtoR(x, XmFONTLIST_DEFAULT_TAG, &str);
		cout << "GetLtoR  = " << (b ? "true" : "false") << endl;
		cout << "  String = " << str << endl;
		XtFree(str);
	}
}

void
quitCallback(Widget, XtPointer, XtPointer)
{
	theApplication->terminate(0);
}

VkMenuDesc appMenuPane[] = {
	{ CONFIRMFIRSTACTION, "Quit", quitCallback },
	{ END }
};

VkMenuDesc optionMenu[] = {
	{ ACTION, "XmRBoolean", optionCallback, NULL, (XtPointer)XmRBoolean },
	{ ACTION, "XmRCardinal", optionCallback, NULL, (XtPointer)XmRCardinal },
	{ ACTION, "XmRDimension", optionCallback, NULL, (XtPointer)XmRDimension },
	{ ACTION, "XmRFloat", optionCallback, NULL, (XtPointer)XmRFloat },
	{ ACTION, "XmRFontList", optionCallback, NULL, (XtPointer)XmRFontList },
	{ ACTION, "XmRInt", optionCallback, NULL, (XtPointer)XmRInt },
	{ ACTION, "XmRPixel", optionCallback, NULL, (XtPointer)XmRPixel },
	{ ACTION, "XmRPixmap", optionCallback, NULL, (XtPointer)XmRPixmap },
	{ ACTION, "XmRPosition", optionCallback, NULL, (XtPointer)XmRPosition },
	{ ACTION, "XmRShort", optionCallback, NULL, (XtPointer)XmRShort },
	{ ACTION, "XmRString", optionCallback, NULL, (XtPointer)XmRString },
	{ ACTION, "XmRUnsignedChar", optionCallback, NULL, (XtPointer)XmRUnsignedChar },
	{ ACTION, "XmRXmString", optionCallback, NULL, (XtPointer)XmRXmString },
	{ END },
};

VkMenuDesc mainMenuPane[] = {
	{ SUBMENU, "Application", NULL, appMenuPane },
	{ END }
};

bool
versionCheck()
{
	const int CURRENT_VERSION = 70;
	int version = (long)VkGetResource(theApplication->baseWidget(),
									 "versionCheck", "Version",
									 XmRInt, "0");
	if (version != CURRENT_VERSION) {
		stringstream msg;
		msg << "Resource File Version Check failed." << "\n"
			<< "Found version " << version << "\n"
			<< "Current version is "
			<< CURRENT_VERSION << ".\n"
			<< "Please copy the resource file (ResourceTest) to $HOME"
			<< ends;
		theWarningDialog->setButtonLabels("Continue", "Quit");
		theWarningDialog->centerOnScreen(true);
		return (theWarningDialog->postAndWait(msg.str().c_str())
				== VkDialogManager::OK);
	}
	return true;
}

int
main(int argc, char** argv)
{
	app = new VkApp("ResourceTest", &argc, argv);

	app->setDefaultResources(app->baseWidget(), defaultResources);
	app->setVersionString("ResourceTest 0.7.0");

	VkWindow* win = new VkWindow("ResourceTestHarness");
	
	Widget form = XtVaCreateManagedWidget(
		"form", xmFormWidgetClass, win->mainWindowWidget(), NULL);

	Widget optLabel = XtVaCreateManagedWidget(
		"Resource Type", xmLabelWidgetClass, form,
  		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_NONE,
		NULL);
	
	Widget nameLabel = XtVaCreateManagedWidget(
		"Resource Name", xmLabelWidgetClass, form,
  		XmNtopAttachment, XmATTACH_WIDGET,
  		XmNtopWidget, optLabel,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_NONE,
		NULL);
	
	Widget classLabel = XtVaCreateManagedWidget(
		"Resource Class", xmLabelWidgetClass, form,
  		XmNtopAttachment, XmATTACH_WIDGET,
  		XmNtopWidget, nameLabel,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_NONE,
		NULL);
	
	Widget defaultLabel = XtVaCreateManagedWidget(
		"Resource Default", xmLabelWidgetClass, form,
  		XmNtopAttachment, XmATTACH_WIDGET,
  		XmNtopWidget, classLabel,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_NONE,
		NULL);

	VkAlignmentGroup group;
	group.add(optLabel);
	group.add(nameLabel);
	group.add(classLabel);
	group.add(defaultLabel);
	group.alignWidth();	
	
	
	option1 = new VkOptionMenu(form, "optionmenu", optionMenu, NULL);
	XtVaSetValues(
		option1->baseWidget(),
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, optLabel,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);
	
	resourceName = XtVaCreateManagedWidget(
		"resource_text", xmTextFieldWidgetClass, form,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, option1->baseWidget(),
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, nameLabel,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);

	resourceClass = XtVaCreateManagedWidget(
		"resource_text", xmTextFieldWidgetClass, form,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, resourceName,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, classLabel,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);

	resourceDef = XtVaCreateManagedWidget(
		"resource_def", xmTextFieldWidgetClass, form,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, resourceClass,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, defaultLabel,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);

	VkAlignmentGroup g2;
	g2.add(optLabel);
	g2.add(option1->baseWidget());
	g2.alignHeight();

	VkAlignmentGroup g3;
	g3.add(nameLabel);
	g3.add(classLabel);
	g3.add(defaultLabel);
	g3.add(resourceName);
	g3.add(resourceClass);
	g3.add(resourceDef);
	g3.alignHeight();

	win->setMenuBar(new VkMenuBar(mainMenuPane, win, False));

	win->menu()->showHelpPane();

	win->addView(form);
	win->show();

	win->setTitle("titleResource");
	win->setIconName("iconNameResource");

	XtAddEventHandler(
		win->baseWidget(), (EventMask)0, True,
		(XtEventHandler)_XEditResCheckMessages, NULL);

	if (!versionCheck()) {
		exit(1);
	}

	app->run();

	return 0;
}

