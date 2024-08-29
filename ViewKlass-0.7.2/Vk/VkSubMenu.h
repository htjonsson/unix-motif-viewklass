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
 * $Id: VkSubMenu.h,v 1.5 2003/04/08 11:31:42 jostle Exp $
 * 
 * This file contains the class definition for the class VkSubMenu.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKSUBMENU_H
#define VKSUBMENU_H

#include <Vk/VkConfig.h>
#include <Vk/VkMenu.h>
#include <Vk/VkApp.h>
#include <Xm/RowColumn.h>
#include <Xm/CascadeBG.h>

class VkSubMenu : public VkMenu {
  
//	friend class VkMenuItem;

public:
	VkSubMenu(const char *name,
			  VkMenuDesc *menuDesc = NULL,
			  XtPointer defaultClientData = NULL);
  
	VkSubMenu(Widget parent,
			  const char *name,
			  VkMenuDesc *menuDesc = NULL,
			  XtPointer defaultClientData = NULL);
  
	void showTearOff(Boolean showIt);
  
	Widget pulldown() { return _pulldown; }
  
	VkMenuItemType menuType() { return SUBMENU; }

	virtual const char *className() { return "VkSubMenu"; }
  
	Boolean isContainer() { return True; }

	void build(Widget parent);

protected:
	Widget _pulldown;
	Boolean _tearOff;
};

#endif // VKSUBMENU_H
