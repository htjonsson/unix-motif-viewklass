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
 * VkMenuActionObject.C
 *
 * This file contains the class implementation for the
 * VkMenuActionObject class, which encapsulates the programmer's
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
= "$Id: VkMenuActionObject.C,v 1.6 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkMenuItem.h>

using namespace std;

VkMenuActionObject::VkMenuActionObject(const char *name, XtPointer clientData)
	: VkMenuAction(name, actionCallback, actionUndoCallback, clientData)
{
    _name = new char[strlen(name) + 1];
	strcpy(_name, name);
}

VkMenuActionObject::~VkMenuActionObject()
{
	delete [] _name;
}

void
VkMenuActionObject::actionCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	VkMenuActionObject* me = (VkMenuActionObject*)clientData;
	theUndoManager->add(me->_name, &VkMenuActionObject::actionUndoCallback,
						me);

	me->doit();
}

void
VkMenuActionObject::actionUndoCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	VkMenuActionObject* me = (VkMenuActionObject*)clientData;
	me->undoit();
}
