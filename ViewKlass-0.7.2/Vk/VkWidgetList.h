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
 * $Id: VkWidgetList.h,v 1.5 2006/02/13 07:23:27 jostle Exp $
 *
 * This file contains the class declaration for
 * the VkWidgetList class, which contains a dynamically
 * resizable array of widgets.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKWIDGETLIST_H
#define VKWIDGETLIST_H

#include <vector>
#include <algorithm>

#include <X11/Intrinsic.h>
#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>

class VkWidgetList {
 public:
    VkWidgetList() {}
    virtual ~VkWidgetList();
  
    virtual void add(Widget w);
    virtual void add(VkComponent* c);

    virtual void remove(Widget w);
    virtual void remove(VkComponent *component);
    virtual void removeFirst();
    virtual void removeLast();

	virtual Boolean exists(Widget w);

    int size() { return _items.size(); }

    Widget operator[](int indx) const { return _items[indx]; }

 protected:
	std::vector<Widget>::iterator find(Widget w)
		{ return std::find(_items.begin(), _items.end(), w); }

    std::vector<Widget> _items;
    std::vector<Widget>::iterator _iter;

 private:
	static void widgetDestroyedCB(Widget w, XtPointer clientData,
								  XtPointer callData);
};

#endif // VKWIDGETLIST_H
