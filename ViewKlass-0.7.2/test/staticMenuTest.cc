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
	= "$Id: staticMenuTest.cc,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>
#include <sstream>

#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/DrawingA.h>

#include <Vk/VkApp.h>
#include <Vk/VkWindow.h>
#include <Vk/VkPopupMenu.h>
#include <Vk/VkOptionMenu.h>
#include <Vk/VkSubMenu.h>
#include <Vk/VkRepeatButton.h>
#include <Vk/VkWarningDialog.h>

using namespace std;

const char* const defaultResources[] = {
	"*Application.labelString: File",
	"*Application.mnemonic: F",
	"*Sample.labelString: Test",
	"*Sample.mnemonic: T",
	"+*foo.labelString: Foo",
	"+*foo.mnemonic: F",
	"+*foo.accelerator: Shift<Key>F10",
	"+*foo.acceleratorText: Shift<Key>F10",
	NULL,
};

VkOptionMenu* option1;
VkRepeatButton* rb;

void
sampleCallback(Widget, XtPointer, XtPointer)
{
	cout << "sampleCallback " << endl;
}

void
quitCallback(Widget w, XtPointer, XtPointer)
{
	cout << "SimpleWindow = " << VkSimpleWindow::getWindow(option1) << endl;
	cout << "Window  = " << VkWindow::getWindow(option1) << endl;
	cout << "MenuBar = " << VkWindow::getMenu(option1) << endl;
	cout << "SimpleWindow = " << VkSimpleWindow::getWindow(rb) << endl;
	cout << "Window  = " << VkWindow::getWindow(rb) << endl;
	cout << "MenuBar = " << VkWindow::getMenu(rb) << endl;
	theApplication->terminate(0);
}

VkMenuDesc appMenuPane[] = {
	{ ACTION, "Action One", sampleCallback },
	{ ACTION, "Action Two", sampleCallback },
	{ ACTION, "Action Three", sampleCallback },
	{ ACTIONWIDGET, "Action Widget", sampleCallback },
	{ SEPARATOR, "Separator1" },
	{ TOGGLE, "Toggle On/Off", sampleCallback },
	{ SEPARATOR, "Separator2" },
	{ CONFIRMFIRSTACTION, "Quit", quitCallback },
	{ END }
};

VkMenuDesc subMenu[] = {
	{ ACTION, "foo", sampleCallback },
	{ ACTION, "bar", sampleCallback },
	{ ACTION, "baz", sampleCallback },
	{ END },
};

VkMenuDesc radioMenu[] = {
	{ TOGGLE, "Rfoo", sampleCallback },
	{ TOGGLE, "Rbar", sampleCallback },
	{ TOGGLE, "Rbaz", sampleCallback },
	{ END },
};

VkMenuDesc optionMenu[] = {
	{ ACTION, "Option Foo", sampleCallback },
	{ ACTION, "Option Bar", sampleCallback },
	{ ACTION, "Option Baz", sampleCallback },
	{ END },
};

VkMenuDesc sampleMenuPane[] = {
	{ LABEL, "Sample Label" },
	{ SEPARATOR, "Separator3" },
	{ ACTION, "More Action", sampleCallback },
	{ SUBMENU, "Submenu", NULL, subMenu },
	{ RADIOSUBMENU, "Radio Submenu", NULL, radioMenu },
	{ END }
};

VkMenuDesc editMenuPane[] = {
	{ LABEL, "Sample Label" },
	{ SEPARATOR, "Separator3" },
	{ END }
};

VkMenuDesc popupMenuPane[] = {
	{ LABEL, "A Popup Menu" },
	{ SEPARATOR, "Popup Separator" },
	{ ACTION, "Option 1", sampleCallback },
	{ ACTION, "Option 2", sampleCallback },
	{ ACTION, "Option 3", sampleCallback },
	{ SUBMENU, "Submenu", NULL, subMenu },
	{ RADIOSUBMENU, "Radio Submenu", NULL, radioMenu },
	{ END },
};

VkMenuDesc mainMenuPane[] = {
	{ SUBMENU, "Application", NULL, appMenuPane },
	{ SUBMENU, "Edit", NULL, editMenuPane },
	{ SUBMENU, "Sample", NULL, sampleMenuPane },
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
			<< "Please copy the resource file (StaticMenuTest) to $HOME"
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
	VkApp* app = new VkApp("StaticMenuTest", &argc, argv);

	app->setDefaultResources(app->baseWidget(), defaultResources);
	app->setVersionString("StaticMenuTest 0.7.0");

	VkWindow* win = new VkWindow("MenuTestHarness");
	
	Widget form = XtVaCreateManagedWidget(
		"form", xmFormWidgetClass, win->mainWindowWidget(), NULL);

	Widget frame1 = XtVaCreateManagedWidget(
		"EmptySpaceFrame", xmFrameWidgetClass, form,
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_NONE,
		NULL);
	Widget label1 = XtVaCreateManagedWidget(
		"Empty Space", xmLabelWidgetClass, frame1,
		NULL);

	Widget frame2 = XtVaCreateManagedWidget(
		"DrawAreaFrame", xmFrameWidgetClass, form,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, frame1,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_OPPOSITE_WIDGET,
		XmNrightWidget, frame1,
		NULL);
	Widget drawArea1 = XtVaCreateManagedWidget(
		"drawArea1", xmDrawingAreaWidgetClass, frame2,
		XmNheight, 50,
		NULL);

	option1 = new VkOptionMenu(form, "optionmenu", optionMenu, NULL);
	XtVaSetValues(option1->baseWidget(),
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_NONE,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, label1,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);
	
	Widget label2 = XtVaCreateManagedWidget(
		"Right-click here\nfor a popup", xmLabelWidgetClass, form,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, option1->baseWidget(),
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, label1,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);

	VkPopupMenu* popup1 = new VkPopupMenu(label2, popupMenuPane, win);

	popup1->attach(drawArea1);
	
	VkMenuItem* mi = popup1->findNamedItem("bar");
	mi->hide();
	
	VkMenuItem* mi2 = popup1->findNamedItem("Option 2");
	mi2->hide();
	
	win->setMenuBar(new VkMenuBar(mainMenuPane, win, False));

	win->menu()->showHelpPane();

	win->addView(form);
	win->show();

	VkMenuItem* mi1 = popup1->findNamedItem("foo");
	mi1->deactivate();
	
	VkMenuItem* mi3 = popup1->findNamedItem("Rbaz");
	mi3->setLabel("BazRadio");
	
	mi->show();
	
	win->setTitle("titleResource");
	win->setIconName("iconNameResource");

	VkSimpleWindow* sw = new VkSimpleWindow("simple");
	rb = new VkRepeatButton("repeat", sw->mainWindowWidget(), RB_pushButton);
	sw->addView(rb);
	sw->show();
	
	if (!versionCheck()) {
		exit(1);
	}
	
	app->run();
	
	return 0;
}

/*********************
VkMenuDesc MenuPane[] = {
	{ ACTION, "", Callback, clientData, undoCallback },
	{ ACTIONWIDGET, "", Callback, clientData, undoCallback }, //Not implemented
	{ CONFIRMFIRSTACTION, "", Callback },
	{ TOGGLE, "", Callback },
	{ LABEL, "" },
	{ SEPARATOR, "" },
	{ SUBMENU, "", NULL, MenuPane },
	{ RADIOSUBMENU, "", NULL, MenuPane },
	{ BAR, "", NULL, MenuPane },
	{ OPTION, "", NULL, MenuPane },
	{ POPUP, "", NULL, MenuPane },
	{ OBJECT, "", NULL, MenuPane }, //Not implemented
	{ END },
};
*********************/
