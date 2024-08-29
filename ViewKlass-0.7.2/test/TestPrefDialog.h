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

#ifndef TESTPREFDIALOG_H
#define TESTPREFDIALOG_H
 
using namespace std;

#include <iostream>

#include <Vk/VkPrefDialog.h>
#include <Vk/VkPrefGroup.h>
#include <Vk/VkPrefOption.h>
#include <Vk/VkPrefText.h>
#include <Vk/VkPrefList.h>
#include <Vk/VkPrefRadio.h>
#include <Vk/VkPrefToggle.h>
#include <Vk/VkPrefLabel.h>
#include <Vk/VkPrefSeparator.h>
#include <Vk/VkPrefCustom.h>
#include <Vk/VkPrefEmpty.h>
#include <Xm/Scale.h>
#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/ArrowB.h>

#include "Slider.h"

class TestPrefDialog : public VkPrefDialog {
public:
	TestPrefDialog(const char *name);

	virtual ~TestPrefDialog();

	virtual const char* className() { return ("TestPrefDialog");}

	friend ostream& operator<<(ostream& os, TestPrefDialog& me);

	Widget createDialog(Widget parent);

	void ok(Widget w, XtPointer callData);
	void apply(Widget w, XtPointer callData);
	void cancel(Widget w, XtPointer callData);
	
	void setOptionValue(int i);
private:
  	VkPrefGroup* pg1;
  	VkPrefGroup* pg2;
	
  	VkPrefList* pls1;
	
  	VkPrefRadio* pr1;
	
	VkPrefText* pt1;
	VkPrefText* pt2;
	VkPrefText* pt3;
	
	VkPrefToggle* ptg1;
	VkPrefToggle* ptg2;
	VkPrefToggle* ptg3;
	VkPrefToggle* ptg4;
	
	VkPrefOption* po1;
	VkPrefOption* po2;
	VkPrefOption* po3;

	VkPrefLabel* pl1;
	VkPrefLabel* pl2;
	VkPrefLabel* pl3;

	VkPrefSeparator* ps1;
	VkPrefSeparator* ps2;
	VkPrefSeparator* ps3;

	VkPrefCustom* pc1;

	VkPrefEmpty* pe1;

	Slider* sl1;
	
	static const char* const _defaultResources[];

	static void customCB(Widget w, XtPointer clientData, XtPointer cbd);

	static void textChangedCb(Widget w, XtPointer clientData,
							  XmAnyCallbackStruct*  callData);
	void textChanged(int value);
	
};

#endif // TESTPREFDIALOG_H
