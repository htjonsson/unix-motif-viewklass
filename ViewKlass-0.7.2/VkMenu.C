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
 * VkMenu.C
 *
 * This file contains the source code for the implementation of the
 * VkMenu class, which forms the base class for the container classes
 * of menu elements.
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
= "$Id: VkMenu.C,v 1.12 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkMenu.h>
#include <Vk/VkSubMenu.h>
#include <Vk/VkMenuAction.h>
#include <Vk/VkMenuActionWidget.h>
#include <Vk/VkMenuConfirmFirstAction.h>
#include <Vk/VkMenuToggle.h>
#include <Vk/VkMenuLabel.h>
#include <Vk/VkMenuSeparator.h>
#include <Vk/VkRadioSubMenu.h>
#include <Vk/VkOptionMenu.h>
#include <Vk/VkMenuUndoManager.h>

VkMenu::VkMenu(const char* name)
	: VkMenuItem (name),
	  _defaultClientData(0)
{

}

VkMenu::~VkMenu()
{
	for (int i = 0; i < _elements.size(); i++) {
		// Don't delete theUndoManager!
		// Other menu items remove themselves from its
		// history when they are deleted so it needs to
		// stay around. It may also be used by other
		// parts of the application.
		if (_elements[i] != theUndoManager) {
			delete _elements[i];
		}
	}
}

void
VkMenu::add(VkMenuItem* item, int position)
{

	if (position == -1) {
		// place it at the end of the array
		_elements.add(item);
	} else {
		// place it somewhere in the middle, and move all the others down
		_elements.insert(position, item);
	}
	
	item->_position = position;
	item->_parentMenu = this;

	if (_isBuilt) {
		switch(menuType()) {
		case SUBMENU:
			item->build(((VkSubMenu*)this)->pulldown());
			break;
		case OPTION:
			item->build(((VkOptionMenu*)this)->pulldown());
			break;
		default:
			item->build(baseWidget());
			break;
		}
	}
}

VkMenuAction*
VkMenu::addAction(const char* name,
				  XtCallbackProc actionCallback,
				  XtPointer clientData,
				  int position)
{
	return addAction(name, actionCallback, (XtCallbackProc)NULL,
					 clientData, position);
}

VkMenuAction*
VkMenu::addAction(const char* name,
				  XtCallbackProc actionCallback,
				  XtCallbackProc undoCallback,
				  XtPointer clientData,
				  int position)
{
	VkMenuAction* newAction =
		new VkMenuAction(name, actionCallback, undoCallback, clientData);

	add(newAction, position);
	return newAction;
}

VkMenuActionWidget*
VkMenu::addActionWidget(const char* name,
				  XtCallbackProc actionCallback,
				  XtCallbackProc undoCallback,
				  XtPointer clientData,
				  int position)
{
	VkMenuActionWidget* newActionWidget =
		new VkMenuActionWidget(name, actionCallback, undoCallback, clientData);

	add(newActionWidget, position);
	return newActionWidget;
}

VkMenuActionWidget*
VkMenu::addActionWidget(const char* name,
				  XtCallbackProc actionCallback,
				  XtPointer clientData,
				  int position)
{
	return addActionWidget(name, actionCallback, (XtCallbackProc)NULL,
					 clientData, position);
}

VkMenuConfirmFirstAction*
VkMenu::addConfirmFirstAction(const char* name,
							  XtCallbackProc actionCallback,
							  XtPointer clientData,
							  int position)
{
	VkMenuConfirmFirstAction* newAction =
		new VkMenuConfirmFirstAction(name, actionCallback, clientData);

	add(newAction, position);
	return newAction;
}

VkMenuToggle*
VkMenu::addToggle(const char* name,
				  XtCallbackProc actionCallback,
				  XtPointer clientData,
				  int state,
				  int position)
{
	VkMenuToggle* newToggle =
		new VkMenuToggle(name, actionCallback, clientData);

	add(newToggle, position);
	newToggle->setVisualState(state == -1 ? FALSE : state);
	return newToggle;
}

VkMenuToggle*
VkMenu::addToggle(const char* name,
				  XtCallbackProc actionCallback,
				  XtCallbackProc undoCallback,
				  XtPointer clientData,
				  int state,
				  int position)
{
	VkMenuToggle* newToggle =
		new VkMenuToggle(name, actionCallback, undoCallback, clientData);

	add(newToggle, position);
	newToggle->setVisualState(state == -1 ? FALSE : state);
	return newToggle;
}

VkMenuLabel*
VkMenu::addLabel(const char* name, int position)
{
	VkMenuLabel* newLabel = new VkMenuLabel(name);
	add(newLabel, position);
	return newLabel;
}

VkMenuSeparator*
VkMenu::addSeparator(const char* name, int position)
{
	VkMenuSeparator* newSeparator = new VkMenuSeparator(name);
	add(newSeparator, position);
	return newSeparator;
}

VkMenuSeparator*
VkMenu::addSeparator(int position)
{
	return addSeparator("separator", position);
}

VkSubMenu*
VkMenu::addSubmenu(VkSubMenu* submenu, int position)
{
	add(submenu, position);
	return submenu;
}

VkSubMenu*
VkMenu::addSubmenu(const char* name, int position)
{
	VkSubMenu* newSubMenu = new VkSubMenu(name);
	add(newSubMenu, position);
	return newSubMenu;
}


VkSubMenu*
VkMenu::addSubmenu(const char* name,
				   VkMenuDesc* menuDesc,
				   XtPointer defaultClientData,
				   int position)
{
	VkSubMenu* newSubMenu = new VkSubMenu(name);
	add(newSubMenu, position);
	newSubMenu->createFromMenuDesc(menuDesc, defaultClientData);
	return newSubMenu;
}

VkRadioSubMenu*
VkMenu::addRadioSubmenu(VkRadioSubMenu* submenu, int position)
{
	add(submenu, position);
	return submenu;
}

VkRadioSubMenu*
VkMenu::addRadioSubmenu(const char* name, int position)
{
	VkRadioSubMenu* newSubMenu = new VkRadioSubMenu(name);
	add(newSubMenu, position);
	return newSubMenu;	
}

VkRadioSubMenu*
VkMenu::addRadioSubmenu(const char* name,
						VkMenuDesc* menuDesc,
						XtPointer defaultClientData,
						int position)
{
	VkRadioSubMenu* newSubMenu = new VkRadioSubMenu(name);
	add(newSubMenu, position);
	newSubMenu->createFromMenuDesc(menuDesc, defaultClientData);
	return newSubMenu;
}

void
VkMenu::createFromMenuDesc(VkMenuDesc* menuDesc, XtPointer defaultClientData)
{
	if (menuDesc == 0 ) return;
	
	VkMenuDesc* current;
	
	for (current = menuDesc; current->menuType != END; current++) {
		switch (current->menuType) {
		case ACTION:
			addAction(current->name,
					  current->callback,
					  current->undoCallback,
					  current->clientData
					  ? current->clientData : defaultClientData);
			break;
		case ACTIONWIDGET:
			addActionWidget(current->name,
							current->callback,
							current->undoCallback,
							current->clientData
							? current->clientData : defaultClientData);
			break;
		case CONFIRMFIRSTACTION:
			addConfirmFirstAction(current->name,
								  current->callback,
								  current->clientData
								  ? current->clientData : defaultClientData);
			break;
		case TOGGLE:
			addToggle(current->name,
					  current->callback,
					  current->clientData
					  ? current->clientData : defaultClientData);
			break;
		case LABEL:
			addLabel(current->name);
			break;
		case SEPARATOR:
			addSeparator();
			break;
		case SUBMENU:
			addSubmenu(current->name,
					   current->submenu,
					   current->clientData
					   ? current->clientData : defaultClientData);
			break;
		case RADIOSUBMENU:
			addRadioSubmenu(current->name,
							current->submenu,
							current->clientData
							? current->clientData : defaultClientData);
			break;
		default:
			break;
		}
	}
}

VkMenuItem*
VkMenu::findNamedItem(const char* name, Boolean caseless)
{
	VkMenuItem* subMenuItem;

	for (int i = 0; i < _elements.size() ; i++) {
		VkMenuItem* mi = (VkMenuItem*)_elements[i];
		if (caseless) {
			if (!strcasecmp(mi->name(), name)) {
				return (VkMenuItem*)_elements[i];
			} else if (mi->menuType() == SUBMENU
					 || mi->menuType() == RADIOSUBMENU) {
				subMenuItem =
					((VkMenu*)mi)->findNamedItem(name, caseless);
				if (subMenuItem) {
					return subMenuItem;
				} else {
					continue;
				}
			}
		} else {
			if (mi->name()) {
				if (!strcmp(mi->name(), name)) {
					return (VkMenuItem*)_elements[i];
				} else if (mi->menuType() == SUBMENU
						 || mi->menuType() == RADIOSUBMENU) {
					subMenuItem =
						((VkMenu*)mi)->findNamedItem(name, caseless);
					if (subMenuItem) {
						return subMenuItem;
					} else {
						continue;
					}
				}
			}
		}
	}
	return NULL;
}

VkMenuItem*
VkMenu::activateItem(const char* name)
{
	VkMenuItem* mi = findNamedItem(name, False);
	if (mi) {
		mi->activate();
	}
	return mi;
}

VkMenuItem*
VkMenu::deactivateItem(const char* name)
{
	VkMenuItem* mi = findNamedItem(name, False);
	if (mi) {
		mi->deactivate();
	}
	return mi;
}

VkMenuItem*
VkMenu::removeItem(const char* name)
{
	int itemPosition = getItemPosition((char*)name);
	VkMenuItem* result = (VkMenuItem*)_elements[itemPosition];
	result->hide();
	_elements.remove(itemPosition);
	
	return result;
}

VkMenuItem*
VkMenu::replace(const char* name, VkMenuItem* newItem)
{
	int itemPosition = getItemPosition((char*)name);
	VkMenuItem* result = removeItem(name);
	add(newItem, itemPosition);

	return result;
}

int
VkMenu::numItems() const
{
	return _elements.size();
}

int
VkMenu::getItemPosition(VkMenuItem* item)
{
	for (int i = 0; i < _elements.size(); i++) {
		if (_elements[i] == item) {
			return i;
		}
	}
	return -1;
}

int
VkMenu::getItemPosition(const char* name)
{
	for (int i = 0; i < _elements.size(); i++) {
		if (!strcmp(_elements[i]->name(), name)) {
			return i;
		}
	}
	return -1;
}

int
VkMenu::getItemPosition(Widget w)
{
	for (int i = 0; i < _elements.size(); i++) {
		if (w == _elements[i]->baseWidget()) {
			return i;
		}
	}
	return -1;
}

VkMenuItem*
VkMenu::operator[] (int indx) const
{
	return (VkMenuItem*)_elements[indx];
}

