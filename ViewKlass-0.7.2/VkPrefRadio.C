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
 * VkPrefRadio.C
 *
 * This file contains the implementation for
 * the preference item radio class.
 * 
 *
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPrefRadio.C,v 1.6 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Xm/RowColumn.h>
#include <Xm/Form.h>

#include <Vk/VkPrefRadio.h>

// A VkPrefRadio is a vertical VkPrefGroup with no label
VkPrefRadio::VkPrefRadio(const char *name,
						 Boolean horizOrientation,
						 Boolean noLabel)
	: VkPrefGroup(name, horizOrientation, noLabel)
{
	// Empty
}

void
VkPrefRadio::instantiate(Widget parent)
{
	_baseWidget = XtVaCreateManagedWidget(
		_name, xmRowColumnWidgetClass, parent,
		XmNorientation, _horizOrientation ? XmHORIZONTAL : XmVERTICAL,
		XmNpacking, XmPACK_TIGHT,
		XmNradioBehavior, True,
		XmNadjustLast, False,
		NULL);

	installDestroyHandler();

	// Create all our pref items
	for (int i = 0; i < _items.size(); ++i) {
		VkPrefItem* pi = (VkPrefItem*)_items[i];
		if (pi->type() == PI_toggle) {
			pi->instantiate(_baseWidget);
		} else {
			cerr << "Error - VkPrefRadio can only contain VkPrefToggles."
				 << endl;
		}
	}
}
