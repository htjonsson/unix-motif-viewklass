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
 * $Id: VkPopupMenu.h,v 1.6 2003/04/08 11:31:42 jostle Exp $
 *
 *
 * This file contains the class definition for VkPopup menus.
 * These menus allow the programmer to specify which menu should 
 * pop up over which widgets, when the user hits the right mouse button.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKPOPUPMENU_H
#define VKPOPUPMENU_H

#include <X11/Intrinsic.h>
#include <Xm/RowColumn.h>
#include <Vk/VkConfig.h>
#include <Vk/VkMenu.h>

class VkPopupMenu : public VkMenu {
public:
	VkPopupMenu(VkMenuDesc* menuDesc,
				XtPointer defaultClientData = NULL);
  
	VkPopupMenu(const char* name = "popupMenu",
				VkMenuDesc* menuDesc = NULL,
				XtPointer defaultClientData = NULL);
  
	VkPopupMenu(Widget parent,
				VkMenuDesc* menuDesc = NULL,
				XtPointer defaultClientData = NULL);
  
	VkPopupMenu(Widget parent,
				const char* name = "popupMenu",
				VkMenuDesc* menuDesc = NULL,
				XtPointer defaultClientData = NULL);
  
	virtual void attach(Widget w);
  
	virtual void build(Widget parent);
 
	virtual void show(); 
	virtual void show(XEvent* buttonPressEvent);
  
	VkMenuItemType menuType() { return POPUP; }
  
	Boolean isContainer() { return True; }
  
	virtual const char* className() { return "VkPopupMenu"; }
  
private:
	static void popup(Widget w, XtPointer clientData, XEvent* event,
					  Boolean* b);
};

#endif // VKPOPUPMENU_H
