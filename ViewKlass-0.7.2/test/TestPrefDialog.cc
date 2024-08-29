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
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

//
// TestPrefDialog.cc
//
static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: TestPrefDialog.cc,v 1.8 2009/03/21 11:44:34 jostle Exp $";


#include <iostream>
#include "TestPrefDialog.h"

const char* const TestPrefDialog::_defaultResources[] = {
	"*PrefGroup1Label.labelString : The Group Label",
	"*firstOptionString : Option One",
	"*PrefText2Label.labelString : Second text",
	NULL
};

TestPrefDialog::TestPrefDialog(const char *name):
	VkPrefDialog(name),
  	pg1(0),
  	pg2(0),
  	pls1(0),
  	pr1(0),
	pt1(0),
	pt2(0),
	pt3(0),
	ptg1(0),
	ptg2(0),
	ptg3(0),
	ptg4(0),
	po1(0),
	po2(0),
	po3(0),
	pl1(0),
	pl2(0),
	pl3(0),
	ps1(0),
	ps2(0),
	ps3(0),
	pc1(0),
	pe1(0),
	sl1(0)
{
}

TestPrefDialog::~TestPrefDialog()
{
	cout << "TestPrefDialog::~TestPrefDialog" << endl;
	// Set the prefList's baseWidget to 0 so that it
	// doesn't get XtDestroy()ed. The VkComponent
	// destructor for this dialog will call XtDestroy
	// which will recursively destroy all the child widgets.
	pls1->widgetDestroyed();
	delete pls1;
}

Widget
TestPrefDialog::createDialog(Widget parent)
{
	// Load class-default resources for this object before creating base widget
	setDefaultResources(parent, _defaultResources );

	pls1 = new VkPrefList("PrefList1");
	
  	pg1 = new VkPrefGroup("PrefGroup1");
	pls1->addItem(pg1);
	
	pt1 = new VkPrefText("PrefText1");
	pg1->addItem(pt1);
	pt2 = new VkPrefText("PrefText2");
	pg1->addItem(pt2);
	pt3 = new VkPrefText("PrefText3");
	pg1->addItem(pt3);

	ps1 = new VkPrefSeparator("PrefSep1");
	pg1->addItem(ps1);

	po1 = new VkPrefOption("PrefOption1", 6);
	po1->setLabel(0, "firstOptionString");
	po1->setLabel(1, "Option 2");
	po1->setLabel(2, "Option 3");
	po1->setLabel(3, "Option 4");
	po1->setLabel(4, "Option 5");
	po1->setLabel(5, "Option 6");
	pg1->addItem(po1);

	ps2 = new VkPrefSeparator("PrefSep2");
	pg1->addItem(ps2);

	pl1 = new VkPrefLabel("PrefLabel1");
	pg1->addItem(pl1);

	pe1 = new VkPrefEmpty("PrefEmpty1");
	pg1->addItem(pe1);

	ps3 = new VkPrefSeparator("PrefSep3");
	pg1->addItem(ps3);

	ptg1 = new VkPrefToggle("PrefToggle1");
	pg1->addItem(ptg1);
	ptg2 = new VkPrefToggle("PrefToggle2", true);
	pg1->addItem(ptg2);
	
  	pg2 = new VkPrefGroup("PrefGroup2");
	pls1->addItem(pg2);
	
	pc1 = new VkPrefCustom("PrefCustom1");
	pg2->addItem(pc1);

	pr1 = new VkPrefRadio("PrefRadio1", true);
	ptg3 = new VkPrefToggle("PrefToggle3");
	ptg4 = new VkPrefToggle("PrefToggle4");
	pr1->addItem(ptg3);
	pr1->addItem(ptg4);
	pg2->addItem(pr1);
	
	setItem(pls1);

	// VkPrefDialog::createDialog will instantiate all the
	// PrefItem children.
	Widget base = VkPrefDialog::createDialog(parent);

	Widget customButton = XtVaCreateManagedWidget(
		"Test Button", xmPushButtonWidgetClass, pc1->baseWidget(),
		NULL);
	XtAddCallback(customButton, XmNactivateCallback, customCB, this);

	return(base);
}

void
TestPrefDialog::customCB(Widget w, XtPointer clientData, XtPointer)
{
	TestPrefDialog* me = (TestPrefDialog*)clientData;
	
	static Boolean sensitive = True;

	sensitive = !sensitive;
	XtSetSensitive(me->pg1->baseWidget(), sensitive);
}

void
TestPrefDialog::setOptionValue(int i)
{
		po1->setValue(i);
}

void
TestPrefDialog::ok(Widget w, XtPointer callData)
{
	cerr << "TestPrefDialog::ok" << endl;

	bool ch;
	
  	ch = pls1->changed();
  	cerr << "VkPrefList pls1->changed() = " << ch << endl;
	cerr << endl;

  	ch = pg1->changed();
  	cerr << "VkPrefGroup pg1->changed() = " << ch << endl;
  	ch = pg2->changed();
  	cerr << "VkPrefGroup pg2->changed() = " << ch << endl;
	cerr << endl;
	
  	ch = pt1->changed();
	cerr << "VkPrefText pt1->changed() = " << ch << endl;
  	ch = pt2->changed();
	cerr << "VkPrefText pt2->changed() = " << ch << endl;
  	ch = pt3->changed();
	cerr << "VkPrefText pt3->changed() = " << ch << endl;
	cerr << endl;
	
  	ch = po1->changed();
	cerr << "VkPrefOption po1->changed() = " << ch << endl;
	cerr << endl;

  	ch = ptg1->changed();
	cerr << "VkPrefToggle ptg1->changed() = " << ch << endl;
  	ch = ptg2->changed();
	cerr << "VkPrefToggle ptg2->changed() = " << ch << endl;
	cerr << endl;
	
  	ch = pr1->changed();
  	cerr << "VkPrefRadio   pr1->changed() = " << ch << endl;
  	ch = ptg3->changed();
	cerr << "VkPrefToggle ptg3->changed() = " << ch << endl;
  	ch = ptg4->changed();
	cerr << "VkPrefToggle ptg4->changed() = " << ch << endl;
	cerr << endl;
	
}

void
TestPrefDialog::apply(Widget w, XtPointer callData)
{
	cerr << "TestPrefDialog::apply" << endl;
}

void
TestPrefDialog::cancel(Widget w, XtPointer callData)
{
	cerr << "TestPrefDialog::cancel" << endl;
}
