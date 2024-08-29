/*****************************************************************
    TestWindow - Test the VkWindow class.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: TestWindow.cc,v 1.9 2009/03/21 11:44:34 jostle Exp $";

using namespace std;

#include <iostream>

using namespace std;

#include <iostream>

#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/ToggleB.h>

#include <Vk/VkCallbackObject.h>
#include <Vk/VkSubMenu.h>
#include <Vk/VkRadioGroup.h>

#include "TestWindow.h"

const char* const testWindowDefaultResources[] = {
	"*tb1.labelString: Toggle 1",
	"*tb2.labelString: Toggle 2",
	"*tb3.labelString: Toggle 3",
	"*tb4.labelString: Toggle 4",
	"*radioFormLabel.labelString: VkRadioGroup Test",
	"*radioFormLabel.fontList: -*-helvetica-bold-r-*-*-*-120-*-*-*-*-*-*",
	NULL,
};

TestWindow::TestWindow(const char* name)
	: VkWindow(name)
{
	theApplication->setDefaultResources(
		mainWindowWidget(), testWindowDefaultResources);

	VkSubMenu* appPane = addMenuPane("application");
	appPane->addAction("Close", closeCallback, this);

	Widget form = XtVaCreateManagedWidget(
		"form", xmFormWidgetClass, mainWindowWidget(),
		NULL);
	
	Widget label = XtVaCreateManagedWidget(
		"radioFormLabel", xmLabelWidgetClass, form,
		XmNtopAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);
	
	// Use a form to hold the toggles
	// (just to prove they don't nee to be in a RowColumn)
	Widget radioForm = XtVaCreateManagedWidget(
		"radioForm", xmFormWidgetClass, form,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, label,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);
	
	tb1 = XtVaCreateManagedWidget(
		"tb1", xmToggleButtonWidgetClass, radioForm,
		XmNset, true,
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_POSITION,
		XmNbottomPosition, 50,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_POSITION,
		XmNrightPosition, 50,
		NULL);

	tb2 = XtVaCreateManagedWidget(
		"tb2", xmToggleButtonWidgetClass, radioForm,
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_POSITION,
		XmNbottomPosition, 50,
		XmNleftAttachment, XmATTACH_POSITION,
		XmNleftPosition, 50,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);
	tb3 = XtVaCreateManagedWidget(
		"tb3", xmToggleButtonWidgetClass, radioForm,
		XmNtopAttachment, XmATTACH_POSITION,
		XmNtopPosition, 50,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_POSITION,
		XmNrightPosition, 50,
		NULL);
	tb4 = XtVaCreateManagedWidget(
		"tb4", xmToggleButtonWidgetClass, radioForm,
		XmNtopAttachment, XmATTACH_POSITION,
		XmNtopPosition, 50,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_POSITION,
		XmNleftPosition, 50,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);

	XtAddCallback(tb1, XmNvalueChangedCallback,
				  toggleCallback, this);
	XtAddCallback(tb2, XmNvalueChangedCallback,
				  toggleCallback, this);
	XtAddCallback(tb3, XmNvalueChangedCallback,
				  toggleCallback, this);
	XtAddCallback(tb4, XmNvalueChangedCallback,
				  toggleCallback, this);

	mRadioGroup = new VkRadioGroup();
	mRadioGroup->add(tb1);
	mRadioGroup->add(tb2);
	mRadioGroup->add(tb3);
	mRadioGroup->add(tb4);

	addView(form);
}

TestWindow::~TestWindow()
{
	delete mRadioGroup;
}

void
TestWindow::closeCallback(Widget, XtPointer clientData, XtPointer)
{
	TestWindow* me = (TestWindow*)clientData;
	me->hide();
}

void
TestWindow::toggleCallback(Widget w, XtPointer clientData, XtPointer call_data)
{
	TestWindow* me = (TestWindow*)clientData;
	XmToggleButtonCallbackStruct* cbs =
		(XmToggleButtonCallbackStruct*)call_data;

	Boolean isSetInCbs = cbs->set;
	Boolean isSetInWidget;
	XtVaGetValues(w, XmNset, &isSetInWidget, NULL);
	
	cerr << "TestWindow::toggleCallback " ;
	if (w == me->tb1) {
		cerr << "tb1 is ";
	} else if (w == me->tb2) {
		cerr << "tb2 is ";
	} else if (w == me->tb3) {
		cerr << "tb3 is ";
	} else if (w == me->tb4) {
		cerr << "tb4 is ";
	} else {
		cerr << " ERROR - Unknown Widget" << endl;
	}

	if (!isSetInCbs) {
		cerr << "not ";
	}
	cerr << "set in csb";
	
	cerr << " and is " ;
	if (!isSetInWidget) {
		cerr << "not ";
	}
	cerr << "set in widget." << endl;
}

