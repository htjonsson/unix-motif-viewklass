/*****************************************************************
    TestAlignment - Test the VkAlignment class.

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
	= "$Id: TestAlignment.cc,v 1.7 2009/03/21 11:44:34 jostle Exp $";

using namespace std;

#include <iostream>

#include <Xm/Label.h>
#include <Xm/BulletinB.h>
#include <Xm/Form.h>

#include <Vk/VkTrace.h>

#include <Vk/VkOptionMenu.h>

#include "TestAlignment.h"

const char* const defaultResources[] = {
	"*optionmenu.mnemonic: A",
	"*makenorm.labelString : Make Normal",
	"*aligntop.labelString : Align Top",
	"*alignbot.labelString : Align Bottom",
	"*alignleft.labelString : Align Left",
	"*alignright.labelString : Align Right",
	"*alignwidths.labelString : Align Width",
	"*alignheights.labelString : Align Height",
	"*disthoriz.labelString : Distribute Horizontal",
	"*distvert.labelString : Distribute Vertical",
	"*printgeom.labelString : Print Geometry",
	NULL,
};

VkMenuDesc optionMenu[] = {
	{ ACTION, "makenorm", TestAlignment::normalOptionCallback },
	{ ACTION, "aligntop", TestAlignment::topOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "alignbot", TestAlignment::bottomOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "alignleft", TestAlignment::leftOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "alignright", TestAlignment::rightOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "alignwidths", TestAlignment::widthOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "alignheights", TestAlignment::heightOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "disthoriz", TestAlignment::horizOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "distvert", TestAlignment::vertOptionCallback,
	NULL, NULL, TestAlignment::normalOptionCallback },
	{ ACTION, "printgeom", TestAlignment::printOptionCallback },
	{ END },
};
	
TestAlignment::TestAlignment(const char* name, Widget parent)
	: VkComponent(name)
{
	setDefaultResources(parent, defaultResources);
	
	_baseWidget = XtVaCreateWidget(
		name, xmBulletinBoardWidgetClass, parent,
		NULL);

	XtVaSetValues(_baseWidget,
				  XmNmarginWidth, 0,
				  XmNmarginHeight, 0,
				  NULL);

	installDestroyHandler();

	VkTraceOpen("/dev/stdout");
	vkTraceEnable = true;
	vkTraceDetailEnable = true;
	VkTrace("Started Alignment");
	VkTraceMark("Mark Start");
	
	mTopAlign = new VkAlignmentGroup();
	mBottomAlign = new VkAlignmentGroup();
	mLeftAlign = new VkAlignmentGroup();
	mRightAlign = new VkAlignmentGroup();
	mOptionMenuAlign = new VkAlignmentGroup();

	
	srand((unsigned int)time(0));
	long int xrnd = rand() / (RAND_MAX / 200);
	long int yrnd = rand() / (RAND_MAX / 200);
	Widget t1 = XtVaCreateManagedWidget(
		"t-1", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget t2 = XtVaCreateManagedWidget(
		"t-1-2", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget t3 = XtVaCreateManagedWidget(
		"t-1-2-3", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	mTopAlign->add(t1);
	mTopAlign->add(t2);
	mTopAlign->add(t3);

	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget b1 = XtVaCreateManagedWidget(
		"b-1", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget b2 = XtVaCreateManagedWidget(
		"b-1-2", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget b3 = XtVaCreateManagedWidget(
		"b-1-2-3", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	mBottomAlign->add(b1);
	mBottomAlign->add(b2);
	mBottomAlign->add(b3);

	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget l1 = XtVaCreateManagedWidget(
		"l-1", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget l2 = XtVaCreateManagedWidget(
		"l-1-2", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget l3 = XtVaCreateManagedWidget(
		"l-1-2-3", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	mLeftAlign->add(l1);
	mLeftAlign->add(l2);
	mLeftAlign->add(l3);

	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget r1 = XtVaCreateManagedWidget(
		"r-1", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget r2 = XtVaCreateManagedWidget(
		"r-1-2", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	xrnd = rand() / (RAND_MAX / 200);
	yrnd = rand() / (RAND_MAX / 200);
	Widget r3 = XtVaCreateManagedWidget(
		"r-1-\n2-3", xmLabelWidgetClass, _baseWidget,
		XmNx, xrnd, XmNy, yrnd,
		XmNborderWidth, 1,
		NULL);
	mRightAlign->add(r1);
	mRightAlign->add(r2);
	mRightAlign->add(r3);

	mOptionMenu =
		new VkOptionMenu(_baseWidget, "optionmenu", optionMenu, this);
	XmString s = XmStringCreateLocalized(const_cast<char*>("Align"));
	XtVaSetValues(mOptionMenu->baseWidget(),
				  XmNx, 120, XmNy, 2,
				  XmNlabelString, s,
				  NULL);
	XmStringFree(s);
	mOptionMenuAlign->add(mOptionMenu);

	VkTrace("Finished Alignment");
	VkTraceDetail("Some Details");
	VkTrace2("Two", "Messages");
	VkTracev("Variable", "Message %s, %c%f", "string", 'a', 12.345);
	VkTraceDetailv("With", "variable %s, %s", "details", "too");
	VkTraceMarkv("A Message", "More %s %d", "stuff; Number ", 7);
	VkTraceMark("Mark End");

// 	cerr << "TestAlignment::TestAlignment mOptionMenu = " << mOptionMenu << endl
//  << "                                    this = " << this << endl;
	
}

TestAlignment::~TestAlignment()
{
	delete mTopAlign;
	delete mBottomAlign;
	delete mLeftAlign;
	delete mRightAlign;
	delete mOptionMenuAlign;

//  cerr << "TestAlignment::~TestAlignment mOptionMenu = " << mOptionMenu << endl
//  << "                                     this = " << this << endl;
	
	delete mOptionMenu;
}

void
TestAlignment::normalOptionCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->makeNormal();
	me->mBottomAlign->makeNormal();
	me->mLeftAlign->makeNormal();
	me->mRightAlign->makeNormal();
	me->mOptionMenuAlign->makeNormal();
}

void
TestAlignment::topOptionCallback(Widget w, XtPointer clientData,
								 XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->alignTop();
	me->mBottomAlign->alignTop();
	me->mLeftAlign->alignTop();
	me->mRightAlign->alignTop();
	me->mOptionMenuAlign->alignTop();
}

void
TestAlignment::bottomOptionCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->alignBottom();
	me->mBottomAlign->alignBottom();
	me->mLeftAlign->alignBottom();
	me->mRightAlign->alignBottom();
	me->mOptionMenuAlign->alignBottom();
}

void
TestAlignment::leftOptionCallback(Widget w, XtPointer clientData,
								  XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->alignLeft();
	me->mBottomAlign->alignLeft();
	me->mLeftAlign->alignLeft();
	me->mRightAlign->alignLeft();
	me->mOptionMenuAlign->alignLeft();
}

void
TestAlignment::rightOptionCallback(Widget w, XtPointer clientData,
								   XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->alignRight();
	me->mBottomAlign->alignRight();
	me->mLeftAlign->alignRight();
	me->mRightAlign->alignRight();
	me->mOptionMenuAlign->alignRight();
}

void
TestAlignment::widthOptionCallback(Widget w, XtPointer clientData,
								   XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->alignWidth();
	me->mBottomAlign->alignWidth();
	me->mLeftAlign->alignWidth();
	me->mRightAlign->alignWidth();
	me->mOptionMenuAlign->alignWidth();
}

void
TestAlignment::heightOptionCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->alignHeight();
	me->mBottomAlign->alignHeight();
	me->mLeftAlign->alignHeight();
	me->mRightAlign->alignHeight();
	me->mOptionMenuAlign->alignHeight();
}

void
TestAlignment::horizOptionCallback(Widget w, XtPointer clientData,
								   XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->distributeHorizontal();
	me->mBottomAlign->distributeHorizontal();
	me->mLeftAlign->distributeHorizontal();
	me->mRightAlign->distributeHorizontal();
	me->mOptionMenuAlign->distributeHorizontal();
}

void
TestAlignment::vertOptionCallback(Widget w, XtPointer clientData,
								  XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	me->mTopAlign->distributeVertical();
	me->mBottomAlign->distributeVertical();
	me->mLeftAlign->distributeVertical();
	me->mRightAlign->distributeVertical();
	me->mOptionMenuAlign->distributeVertical();
}

void
TestAlignment::printOptionCallback(Widget w, XtPointer clientData,
								   XtPointer callData)
{
	TestAlignment* me = (TestAlignment*)clientData;
	cout << "Top    :" << endl << *(me->mTopAlign) << endl;
	cout << "Bottom :" << endl << *(me->mBottomAlign) << endl;
	cout << "Left   :" << endl << *(me->mLeftAlign) << endl;
	cout << "Right  :" << endl << *(me->mRightAlign) << endl;
	cout << "Option :" << endl << *(me->mOptionMenuAlign) << endl;
}

