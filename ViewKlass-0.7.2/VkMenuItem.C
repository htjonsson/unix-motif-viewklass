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

/**
 *
 * VkMenuItem.C
 *
 *
 * This file contains the class implementation for the VkMenuItem class, which
 * forms the base for all the menu elements in the ViewKlass Library.
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
	= "$Id: VkMenuItem.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkResource.h>
#include <Vk/VkMenu.h>

#include <Vk/VkMenuItem.h>

VkWidgetList VkMenuItem::_unmanagedWidgets;

VkMenuItem::VkMenuItem(const char* name)
	: VkComponent(name),
	  _position(-1),
	  _isBuilt(false),
	  _isHidden(false),
	  _sensitive(true),
	  _parent(0),
	  _parentMenu(0),
	  _label(0)
{
}

VkMenuItem::~VkMenuItem()
{
	delete _label;
}

void
VkMenuItem::show(Widget parent)
{
	_isHidden = false;
	if (_isBuilt) {
		XtManageChild(_baseWidget);
		_unmanagedWidgets.remove(_baseWidget);
	} else {
		_parent = parent;
		build(parent);
	}
}

void
VkMenuItem::hide()
{
	_isHidden = true;
	if (_isBuilt) {
		XtUnmanageChild(_baseWidget);
		_unmanagedWidgets.add(_baseWidget);
	}
}

void
VkMenuItem::manageAll()
{
	for (int i = 0; i < _unmanagedWidgets.size(); ++i) {
		XtManageChild(_unmanagedWidgets[i]);
		_unmanagedWidgets.remove(_unmanagedWidgets[i]);
	}
}

int
VkMenuItem::remove()
{
	if (_parentMenu) {
		_parentMenu->removeItem(name());
	}
	return 0; // I wonder what the return value means...
}

void
VkMenuItem::activate()
{
	_sensitive = True;
	if (_isBuilt) {
		XtSetSensitive(_baseWidget, True);
  	}
}

void
VkMenuItem::deactivate()
{
	_sensitive = False;
	if (_isBuilt) {
		XtSetSensitive(_baseWidget, False);
	}
}

void
VkMenuItem::setPosition(int position)
{
	_position = position;
}

void
VkMenuItem::setLabel(const char* label)
{
	if (!isContainer()) {
		delete _label;
		_label = new string(label);

		if (_baseWidget) {
			// Check if the string names a resource ...
			XmString xmstr =
				(XmString)VkGetResource(_baseWidget, label, "MenuLabel",
										XmRXmString, label);
			XtVaSetValues(_baseWidget, XmNlabelString, xmstr, NULL);
		}
	}
}

void
VkMenuItem::build(Widget parent)
{
	_parent = parent;
	_isBuilt = true;
}

