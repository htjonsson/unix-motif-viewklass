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
 * VkAction.C
 *
 * This file contains the class implementation for the
 * VkAction class, which encapsulates the programmer's
 * interface to reversible commands.
 *
 * Copyright (C) 1994
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkAction.C,v 1.11 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkAction.h>
#include <Vk/VkMenuUndoManager.h>

using namespace std;

VkAction::VkAction(const char *name)
{
    _name = new char[strlen(name) + 1];
	strcpy(_name, name);
}

VkAction::~VkAction()
{
	// cerr << "VkAction::~VkAction : this =" << this << endl;

	// FIX ME - This assumes that all actions have unique names.
	VkComponentList* l = theUndoManager->historyList();
	for (int i = 0; i < l->size(); ++i) {
		if (strcmp((*l)[i]->name(), _name) == 0) {
			delete (*l)[i];
			// delete will cause the action to be
			// removed from the history list. Don't do that here!
		}
	}

	delete [] _name;
}

void 
VkAction::execute()
{
	theUndoManager->add(_name, &VkAction::actionUndoCallback, this);

	doit();
}

void
VkAction::actionUndoCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	VkAction* me = (VkAction*)clientData;
	me->undoit();
}
