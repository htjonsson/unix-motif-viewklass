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
 * $Id: VkPrefGroup.h,v 1.4 2006/02/24 07:40:26 jostle Exp $
 *
 * This file contains the class definition for
 * the preference dialog group thingy, which
 * allows the programmer to group preference
 * items together.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKPREFGROUP_H
#define VKPREFGROUP_H

#include <Vk/VkConfig.h>
#include <Vk/VkComponentList.h>
#include <Vk/VkPrefItem.h>

class VkPrefGroup : public VkPrefItem {

 public:
    VkPrefGroup(const char *name,
				Boolean horizOrientation = FALSE,
				Boolean noLabel = FALSE);

	virtual ~VkPrefGroup();
	
    virtual const char *className() { return "VkPrefGroup"; }

    void addItem(VkPrefItem *item);
    VkPrefItem *item(int item);

    int size();
    virtual Boolean hasChildren() { return size() > 0; }

    virtual void deleteChildren();

    virtual VkPrefItemType type() { return PI_group; }
    Boolean isContainer() { return True; }

	Boolean changed();

	void activate();
	void deactivate();

	virtual void instantiate(Widget parent);

	Widget buildLabel();

 protected:
	VkComponentList _items;

	Boolean _horizOrientation;
	Boolean _noLabel;
	
	Dimension _maxLabelWidth;
	Dimension _maxHeight;

	VkPrefItemType _firstType;
};

#endif // VkPREFGROUP_H
