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
 * $Id: VkMenuConfirmFirstAction.h,v 1.7 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition of menu actions
 * that require user confirmation before execution.  This
 * allows the programmer to easily determine whether the
 * user wants a (possibly) dangerous or irreversible action
 * to take place.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMENUCONFIRMFIRSTACTION_H
#define VKMENUCONFIRMFIRSTACTION_H

#include <Vk/VkConfig.h>
#include <Vk/VkMenuItem.h>

class VkMenuConfirmFirstAction : public VkMenuAction {
public:
	VkMenuConfirmFirstAction(const char *name,
							 XtCallbackProc  callback,
							 XtCallbackProc  undoCallback,
							 XtPointer       clientData = NULL);

	VkMenuConfirmFirstAction(const char *name,
							 XtCallbackProc  callback,
							 XtPointer       clientData = NULL);

	virtual void build(Widget parent);

	virtual const char *className() { return "VkMenuConfirmFirstAction"; }

	Boolean isContainer() { return False; }

	VkMenuItemType menuType() { return CONFIRMFIRSTACTION; }

private:
	static void confirmCallback(Widget w, XtPointer clientData,
								 XtPointer callData);
};

#endif // VKMENUCONFIRMFIRSTACTION_H

