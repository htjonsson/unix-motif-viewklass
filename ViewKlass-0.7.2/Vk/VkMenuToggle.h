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
 * $Id: VkMenuToggle.h,v 1.7 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition of the VkMenuToggle
 * class, which is implemented as a toggle button gadget within
 * the interface's menus.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMENUTOGGLE_H
#define VKMENUTOGGLE_H

#include <Xm/ToggleBG.h>
#include <Vk/VkConfig.h>
#include <Vk/VkMenuItem.h>

class VkMenuToggle : public VkMenuAction {
public:
	VkMenuToggle(const char *name,
				 XtCallbackProc  callback,
				 XtCallbackProc  undoCallback,
				 XtPointer       clientData = NULL); 

	VkMenuToggle(const char *name,
				 XtCallbackProc  callback,
				 XtPointer       clientData = NULL);

	virtual ~VkMenuToggle();

	void setVisualState(Boolean state);
	void setStateAndNotify(Boolean state);
	Boolean getState();

	VkMenuItemType menuType() { return TOGGLE; }
	Boolean isContainer() { return False; }

	virtual void build(Widget parent);

	virtual const char *className() { return "VkMenuToggle"; }

private:
	Boolean _initialState;
};


#endif // VKMENUTOGGLE_H
