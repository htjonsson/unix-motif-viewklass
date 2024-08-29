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
 * VkMenuActionObject.h
 *
 * This file contains the class declaration for the
 * VkMenuActionObject class, which encapsulates the programmer's
 * interface to reversible commands.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKACTIONOBJECT_H
#define VKACTIONOBJECT_H

#include <Vk/VkConfig.h>
#include <X11/Intrinsic.h>

#include <Vk/VkMenuItem.h>

class VkMenuActionObject : public VkMenuAction {

 public:
	VkMenuActionObject(const char *name, XtPointer clientData = NULL);
	virtual ~VkMenuActionObject();

	virtual const char* className() { return "VkMenuActionObject"; }
	virtual VkMenuItemType menuType() { return OBJECT; }

 protected:
	virtual void doit() = 0;
	virtual void undoit() = 0;

 private:
    static void actionCallback(Widget, XtPointer, XtPointer);
    static void actionUndoCallback(Widget, XtPointer, XtPointer);

};

#endif // VKACTIONOBJECT_H
