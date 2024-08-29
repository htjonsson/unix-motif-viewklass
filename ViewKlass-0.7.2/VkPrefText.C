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
 * VkPrefText.h
 *
 * This file contains the class implementation for 
 * VkPrefText, the class which allows the programmer 
 * to define text field widgets in preference dialogs.
 *
 * Chris Toshok
 * Copyright (C) 1994
 * The Hungry Programmers, Inc
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPrefText.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <Xm/Label.h>
#include <Xm/TextF.h>

#include <Vk/VkPrefText.h>

using namespace std;

VkPrefText::VkPrefText(const char *name, int columns)
	: VkPrefItem(name),
	  _columns(columns)
{
	
}

VkPrefText::~VkPrefText()
{
}

Boolean
VkPrefText::changed()
{
	char* s = XmTextFieldGetString(_baseWidget);
	Boolean changed = strcmp(_value.c_str(), s);
	XtFree(s);
	return changed;
}
    
const char *
VkPrefText::getValue()
{
	char* s = XmTextFieldGetString(_baseWidget);
	_value = s;
	XtFree(s);
	return _value.c_str();
}

void
VkPrefText::setValue(const char *str)
{
	_value = str;
	XmTextFieldSetString(_baseWidget, (char*)str);
}

void
VkPrefText::instantiate(Widget parent)
{
	_baseWidget = XtVaCreateManagedWidget(
		_baseName.c_str(), xmTextFieldWidgetClass, parent,
		XmNcolumns, _columns,
		NULL);

	installDestroyHandler();
}
