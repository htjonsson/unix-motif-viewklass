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
 * $Id: VkOptionMenu.h,v 1.8 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the VkOptionMenu class.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKOPTIONMENU_H
#define VKOPTIONMENU_H

#include <Xm/RowColumn.h>
#include <Vk/VkConfig.h>
#include <Vk/VkMenu.h>

class VkOptionMenu : public VkMenu {
public:
	VkOptionMenu(VkMenuDesc* menuDesc,
				 XtPointer defaultClientData = NULL);
  
	VkOptionMenu(const char* name = "optionMenu",
				 VkMenuDesc* menuDesc = NULL,
				 XtPointer defaultClientData = NULL);
  
	VkOptionMenu(Widget parent,
				 VkMenuDesc* menuDesc,
				 XtPointer defaultClientData = NULL);
  
	VkOptionMenu(Widget parent,
				 const char* name = "optionMenu",
				 VkMenuDesc* menuDesc = NULL,
				 XtPointer defaultClientData = NULL);

	virtual ~VkOptionMenu() {}
	
	void set(char* name);
	void set(int indx);
	void set(VkMenuItem* item);
  
	int getIndex();
  
	VkMenuItem* getItem();
  
	void forceWidth(int width);
  
	VkMenuItemType menuType() { return OPTION; }

	virtual const char* className() { return "VkOptionMenu"; }

	Boolean isContainer() { return True; }

	void setLabel(const char* str);

	void build(Widget parent);

	Widget pulldown() { return _pulldown; }

	virtual void show();

private:
	Widget _pulldown;
  
};


#endif // VKOPTIONMENU_H
