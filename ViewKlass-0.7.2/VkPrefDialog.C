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
 * VkPrefDialog.C
 *
 * This file contains the implementation for the 
 * VkPrefDialog class, which implements a preference
 * dialog box, subclassed from VkGenericDialog.
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
	= "$Id: VkPrefDialog.C,v 1.9 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkPrefDialog.h>

using namespace std;

const char VkPrefDialog::prefCallback[] = "VkPrefDialog::prefCallback";


VkPrefDialog::VkPrefDialog(const char *name, VkPrefItem *item)
	: VkGenericDialog(name),
	  _item(item)
{
    _showApply = True;
	_showOK = True;
	_showHelp = False;
	_showCancel = True;

	if (_item) {
		_item->instantiate(_baseWidget);
	}
}

VkPrefDialog::~VkPrefDialog()
{
}

void 
VkPrefDialog::setItem(VkPrefItem *item)
{
    _item = item;
}

VkPrefItem *
VkPrefDialog::item()
{
    return _item;
}

Widget
VkPrefDialog::createDialog(Widget parent)
{
	Widget base = VkGenericDialog::createDialog(parent);
	
    if (_item){
		_item->instantiate(base);
		_item->activate();
    }
	return base;
}

void
VkPrefDialog::ok(Widget w, XtPointer callData)
{
	callCallbacks(prefCallback, (XtPointer)VkDialogManager::OK);
	VkGenericDialog::ok(w, callData);
}

void
VkPrefDialog::apply(Widget w, XtPointer callData)
{
	callCallbacks(prefCallback, (XtPointer)VkDialogManager::APPLY);
	VkGenericDialog::apply(w, callData);
}

void
VkPrefDialog::cancel(Widget w, XtPointer callData)
{
	callCallbacks(prefCallback, (XtPointer)VkDialogManager::CANCEL);
	VkGenericDialog::cancel(w, callData);
}
