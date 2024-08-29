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
 * $Id: VkMenuActionWidget.h,v 1.2 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the VkMenuActionWidget class,
 * which is implemented as a push button gadget within the menu.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMENUACTIONWIDGET_H
#define VKMENUACTIONWIDGET_H

#include <Xm/PushBG.h>
#include <Vk/VkConfig.h>
#include <Vk/VkMenuItem.h>

class VkMenuActionWidget : public VkMenuAction {
public:
	VkMenuActionWidget(const char *name,
				 XtCallbackProc  callback = NULL,
				 XtPointer       clientData = NULL)
		: VkMenuAction(name, callback, clientData)
		{}

	VkMenuActionWidget(const char *name,
				 XtCallbackProc  callback,
				 XtCallbackProc  undoCallback,
				 XtPointer       clientData = NULL)
		: VkMenuAction(name, callback, undoCallback, clientData)
		{}
	
	virtual ~VkMenuActionWidget() {}

	virtual void build(Widget parent);

	virtual const char *className() { return "VkMenuActionWidget"; }
  
	virtual VkMenuItemType menuType() { return ACTIONWIDGET; }

};

#endif // VKMENUACTIONWIDGET_H
