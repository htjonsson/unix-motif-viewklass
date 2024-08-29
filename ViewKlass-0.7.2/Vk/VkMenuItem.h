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
 * $Id: VkMenuItem.h,v 1.8 2006/02/13 07:23:27 jostle Exp $
 *
 * This file contains the class definition for VkMenuItem.h
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMENUITEM_H
#define VKMENUITEM_H

#include <string>

#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>
#include <Vk/VkWidgetList.h>

typedef enum {ACTION, ACTIONWIDGET, CONFIRMFIRSTACTION, TOGGLE, LABEL,
			  SEPARATOR, SUBMENU, RADIOSUBMENU, BAR, OPTION, POPUP, OBJECT,
			  END} VkMenuItemType;

class VkMenu;

class VkMenuItem : public VkComponent {
	friend class VkMenu;
public:
	virtual ~VkMenuItem();
  
	void show(Widget parent = 0);
	void hide();
	int remove();
  
	void activate();
	void deactivate();
  
	virtual void setLabel(const char *str);
  
	void setPosition(int position);
  
	virtual VkMenuItemType menuType() = 0;
	virtual Boolean isContainer() = 0;
  
	virtual const char* className() { return "VkMenuItem"; }

	virtual void build(Widget parent);

protected:
	VkMenuItem();
	VkMenuItem(const char *name);

	static void manageAll();

	int _position;
	Boolean _isBuilt;
	Boolean _isHidden;
	Boolean _sensitive;

	Widget _parent;
	VkMenu* _parentMenu;
	std::string* _label;

	static VkWidgetList _unmanagedWidgets;

};

// Include all the other menu item sub-class headers
#include <Vk/VkMenuAction.h>
#include <Vk/VkMenuConfirmFirstAction.h>
#include <Vk/VkMenuActionObject.h>
#include <Vk/VkMenuActionWidget.h>
#include <Vk/VkMenuLabel.h>
#include <Vk/VkMenuSeparator.h>
#include <Vk/VkMenuToggle.h>
#include <Vk/VkMenuUndoManager.h>

#endif /* VKMENUITEM_H */
