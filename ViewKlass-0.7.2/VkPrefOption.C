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

/**
 *
 * VkPrefOption.C
 *
 * This file contains the implementation for option 
 * menus used in preference dialogs.
 *
 * Chris Toshok
 * Copyright (C) 1994
 * The Hungry Programmers, Inc.
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPrefOption.C,v 1.11 2009/03/21 11:44:34 jostle Exp $";

#include <string.h>

#include <Xm/RowColumn.h>
#include <Xm/PushBG.h>

#include <Vk/VkResource.h>
#include <Vk/VkPrefOption.h>

using namespace std;

VkPrefOption::VkPrefOption(const char *name, int numEntries)
	: VkPrefItem(name),
	  _value(0)
{
	_labels = new char*[numEntries];
	_buttons = new Widget[numEntries];
	for (int i = 0; i < numEntries; ++i) {
		_labels[i] = 0;
		_buttons[i] = 0;
	}
	_numOptions = numEntries;
}

VkPrefOption::~VkPrefOption()
{
	delete [] _labels;
	delete [] _buttons;
}

void
VkPrefOption::setLabel(int indx, const char* label)
{
	// Check for a valid index
	if (indx < _numOptions) {
		// Save the label
 		_labels[indx] = (char*)label;
		// Update the button's labelString if the button has been created.
		if(_buttons[indx] != 0) {
			XmString xmstr =
				(XmString)VkGetResource(_buttons[indx], label,
										"PrefOptionLabel",
										XmRXmString, label);
			XtVaSetValues(_buttons[indx], XmNlabelString, xmstr, NULL);
		}
	}
}

char*
VkPrefOption::getLabel(int indx)
{
	return _labels[indx];
}

void
VkPrefOption::setSize(int numEntries)
{
	delete [] _labels;
	_labels = new char*[numEntries];

	delete [] _buttons;
	_buttons = new Widget[numEntries];

	_numOptions = numEntries;
}

int
VkPrefOption::getSize()
{
	return _numOptions;
}

Widget
VkPrefOption::getButton(int indx)
{
	return _buttons[indx];
}

Boolean
VkPrefOption::changed()
{
	Widget w;
	XtVaGetValues(_baseWidget, XmNmenuHistory, &w, NULL);
	return (_buttons[_value] != w);
}
    
int
VkPrefOption::getValue()
{
	Widget w;
	XtVaGetValues(_baseWidget, XmNmenuHistory, &w, NULL);
	for (int i = 0; i < _numOptions; ++i) {
		if (_buttons[i] == w) {
			_value = i;
			break;
		}
	}
	return _value;
}

void
VkPrefOption::setValue(int value)
{
	_value = value;
	XtVaSetValues(_baseWidget, XmNmenuHistory, _buttons[value], NULL);
}

void
VkPrefOption::setOptionLabel(const char* label)
{
	Widget w = XmOptionLabelGadget(_baseWidget);
	XmString str = XmStringCreateLocalized((char*)label);
	XtVaSetValues(w, XmNlabelString, str, NULL);
	XmStringFree(str);
}

void
VkPrefOption::instantiate(Widget parent)
{
	string bName = _name;
	bName += "Pulldown";
	
  	Widget pulldown =
		XmCreatePulldownMenu(parent, (char*)(bName.c_str()), NULL, 0);

  	string buttonName;
  	string buttonNumber = "Button00";
  	for (int i = 0; i < _numOptions; ++i) {
		// Set the numeric part of the button's name.
		// (assumes no more than 99 buttons)
  		buttonNumber[6] = ('0' + i/10);
  		buttonNumber[7] = ('0' + i%10);
  		buttonName = _name + buttonNumber;

		XmString xmstr =
			(XmString)VkGetResource(parent, _labels[i],
									"PrefOptionLabel",
									XmRXmString, _labels[i]);
  		_buttons[i] = XtVaCreateManagedWidget(
  			buttonName.c_str(), xmPushButtonGadgetClass,
  			pulldown,
			XmNlabelString, xmstr,
  			NULL);
  	}

	Arg args[8];
	int n = 0;
	XtSetArg(args[n], XmNsubMenuId, pulldown); n++;
  	_baseWidget = XmCreateOptionMenu(parent, (char*)(_baseName.c_str()),
 									 args, n);

	installDestroyHandler();

	XtManageChild(_baseWidget);
}
