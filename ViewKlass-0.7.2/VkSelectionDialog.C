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
 * VkSelectionDialog.C
 *
 * This file contains the class implementation for the VkSelectionDialog
 * class.
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
= "$Id: VkSelectionDialog.C,v 1.11 2009/03/21 11:44:34 jostle Exp $";

#include <string>
#include <iostream>

using namespace std;

#include <Xm/TextF.h>
#include <Xm/List.h>

#include <Vk/VkSelectionDialog.h>
#include <Vk/VkApp.h>

VkSelectionDialog::VkSelectionDialog(const char *name)
	: VkDialogManager(name),
	  _dialogBox(0),
	  _items(0),
	  _numVisible(8),
	  _listLabelString(0)
{
	_dialogShellTitle = NULL;
	_showOK = True;
	_showHelp = False;
	_showCancel = True;

	_items = new VkNameList();
}

VkSelectionDialog::~VkSelectionDialog()
{
	XmStringFree(_listLabelString);
}

Widget
VkSelectionDialog::createDialog(Widget parent)
{
	Arg args[8];
	int n = 0;
	XtSetArg(args[n], XmNlistVisibleItemCount, _numVisible); n++;
	if (_listLabelString) {
		XtSetArg(args[n], XmNlistLabelString, _listLabelString); n++;
	}
	_dialogBox = XmCreateSelectionDialog(parent, (char*)_name, args, n);
	_list = XtNameToWidget(_dialogBox, "ItemsListSW.ItemsList");

	// Check if there are any items in the list already.
	// Must have been set using a resource.
	// Convert them to string and store them in a VkNameList
	int num;
	XmStringTable xst;
	XtVaGetValues(_list, XmNitemCount, &num, XmNitems, &xst, NULL);
	VkNameList resourceItems;
	for (int i = 0; i < num; ++i) {
		char* s;
		if (XmStringGetLtoR(xst[i], XmFONTLIST_DEFAULT_TAG, &s)) {
			resourceItems.add(s);
			XtFree(s);
		}
	}
	
	// Now add any items which have been put into our
	// _items VkNameList.
	if (_items->size() > 0) {
		XmStringTable st = _items->getXmStringTable();
		XmListAddItems(_list, st, _items->size(), 0);
		VkNameList::freeXmStringTable(st);
	}

	// Concatenate the two lists in the _items list.
	if (resourceItems.size() > 0) {
		resourceItems.add(*_items);
		delete _items;
		_items = new VkNameList(resourceItems);
	}
	
	return _dialogBox;
}

void
VkSelectionDialog::clearList()
{
	// Don't have a VkNameList::clear() so delete and re-create
	delete _items;
	_items = new VkNameList();
	
	if (_dialogBox != 0) {
		Widget list = XtNameToWidget(_baseWidget, "ItemsList");
		if (list) {
			XmListDeleteAllItems(list);
		}
	}
}

// Add an item to the list.
// If the dialog has already been created and the update
// argument is true then update the displayed list, otherwise
// just add to the internal name list.
//
void
VkSelectionDialog::addItem(const char *item, bool update)
{
	_items->add(item);

	if (update && _dialogBox != 0) {
		XmString s = XmStringCreateLocalized((char*)item);
		XmListAddItem(_list, s, 0);
		XmStringFree(s);
	}
}

int
VkSelectionDialog::itemIndex(const char* item)
{
    return _items->getIndex(item);
}

void
VkSelectionDialog::setListLabel(const char* label)
{
	if (_listLabelString) {
		XmStringFree(_listLabelString);
	}
	_listLabelString = XmStringCreateLocalized(const_cast<char*>(label));
	if (_dialogBox != 0) {
		XtVaSetValues(_dialogBox,
					  XmNlistLabelString, _listLabelString,
					  NULL);
	}
}

char*
VkSelectionDialog::getSelection()
{
	Widget tf = XtNameToWidget(_dialogBox, "Text");
	char* s = XmTextFieldGetString(tf);
	return s;
}

Widget
VkSelectionDialog::getNamedChild(const char* name)
{
	return XtNameToWidget(_baseWidget, name);
}

Widget
VkSelectionDialog::getListWidget()
{
	return _list;
}

VkSelectionDialog* theSelectionDialogInstance()
{
	static VkSelectionDialog* instance = 0;
	if (instance == 0) {
		instance = new VkSelectionDialog("Selection");
	}
	return instance;
}
