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
 * VkAction.h
 *
 * This file contains the class declaration for the
 * VkAction class, which encapsulates the programmer's
 * interface to reversible commands.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKACTION_H
#define VKACTION_H

#include <Vk/VkConfig.h>
#include <X11/Intrinsic.h>

class VkAction {

 public:
	VkAction(const char *name);
	virtual ~VkAction();

	void execute();

 protected:
	virtual void doit() = 0;
	virtual void undoit() = 0;
	char *_name;

 private:
    static void actionUndoCallback(Widget, XtPointer, XtPointer);


};

#endif // VKACTION_H
