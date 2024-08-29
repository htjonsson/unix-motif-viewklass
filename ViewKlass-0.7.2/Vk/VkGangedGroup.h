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
 * $Id: VkGangedGroup.h,v 1.3 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class declaration
 * for the VkGangedGroup class, which allows the
 * programmer to keep a group of scrollbars or
 * scales at the same value, meaning if you update
 * one, they are all updated.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKGANGEDGROUP_H
#define VKGANGEDGROUP_H

#include <Vk/VkConfig.h>
#include <Vk/VkWidgetList.h>

class VkGangedGroup : public VkWidgetList {
public:
	VkGangedGroup();
	virtual ~VkGangedGroup() {}
	
	virtual void add(Widget w);
	virtual void add(VkComponent *obj);

	virtual void remove(Widget w);
	virtual void remove(VkComponent *obj);

	virtual void removeFirst();
	virtual void removeLast();

private:
	void change(int value);
	static void changeCallback(Widget w, XtPointer clientData,
							   XtPointer callData);
};

#endif // VKGANGEDGROUP_H
