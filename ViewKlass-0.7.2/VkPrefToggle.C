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
 * VkPrefToggle.h
 *
 * This file contains the class implementation for 
 * VkPrefToggle, the class which allows the programmer 
 * to define toggle button widgets in preference dialogs.
 *
 *
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPrefToggle.C,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <Xm/Label.h>
#include <Vk/VkPrefToggle.h>

using namespace std;

VkPrefToggle::VkPrefToggle(const char *name, Boolean forceLabelFormat)
	: VkPrefItem(name),
	  _value(false),
	  _forceLabelFormat(forceLabelFormat)
{
	// Empty
}

Boolean
VkPrefToggle::changed()
{
	Boolean set;
	XtVaGetValues(_baseWidget, XmNset, &set, NULL);
	return (_value != set);
}

Boolean
VkPrefToggle::getValue()
{
	XtVaGetValues(_baseWidget, XmNset, &_value, NULL);
	return _value;
}

void
VkPrefToggle::setValue(Boolean set)
{
	_value = set;
	XtVaSetValues(_baseWidget, XmNset, set, NULL);
}

void
VkPrefToggle::instantiate(Widget parent)
{
	if (_forceLabelFormat) {
      XmString xmstr = XmStringCreateLocalized(const_cast<char*>(" "));
		_baseWidget = XtVaCreateManagedWidget(
			_baseName.c_str(), xmToggleButtonWidgetClass, parent,
			XmNlabelString, xmstr,
			NULL);
		XmStringFree(xmstr);
	} else {
		_baseWidget = XtVaCreateManagedWidget(
			_baseName.c_str(), xmToggleButtonWidgetClass, parent,
			NULL);
	}

	installDestroyHandler();
}

Widget
VkPrefToggle::buildLabel()
{
		if (_forceLabelFormat) {
			_labelWidget = XtVaCreateManagedWidget(
			_labelName.c_str(), xmLabelWidgetClass, XtParent(_baseWidget),
			NULL);
		}
		return _labelWidget;
}
