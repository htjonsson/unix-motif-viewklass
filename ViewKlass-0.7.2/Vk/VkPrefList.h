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
 * $Id: VkPrefList.h,v 1.4 2003/12/13 02:09:34 jostle Exp $
 *
 * This file contains the class definition for
 * the preference dialog list thingy, which
 * allows the programmer to list preference
 * items together.
 *
 *
 *
 **/

#ifndef VKPREFLIST_H
#define VKPREFLIST_H

#include <iostream>

#include <Vk/VkConfig.h>
#include <Vk/VkComponentList.h>
#include <Vk/VkPrefGroup.h>

class VkPrefList : public VkPrefGroup {

 public:
    VkPrefList(const char *name);

	virtual ~VkPrefList() {}
	
    virtual const char *className() { return "VkPrefList"; }

    VkPrefItemType type() { return PI_list; }

	void instantiate(Widget parent);
	
 private:

};

#endif // VkPREFLIST_H
