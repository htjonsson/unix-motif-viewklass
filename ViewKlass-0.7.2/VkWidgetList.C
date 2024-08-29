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
 * VkWidgetList.C
 *
 * This file contains the class implementation for
 * the VkWidgetList class, which contains a dynamically
 * resizable array of widgets.
 *
 * Copyright (C) 1994
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/
  
static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkWidgetList.C,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkWidgetList.h>

using namespace std;

VkWidgetList::~VkWidgetList()
{
	for (_iter = _items.begin(); _iter != _items.end(); ++_iter) {
		XtRemoveCallback(*_iter, XmNdestroyCallback, widgetDestroyedCB,
						 (XtPointer)this);
	}
}

void
VkWidgetList::widgetDestroyedCB(Widget w, XtPointer clientData,
								XtPointer callData)
{
	VkWidgetList* wl = (VkWidgetList*)clientData;

	wl->_items.erase(std::remove(wl->_items.begin(), wl->_items.end(), w),
				 wl->_items.end());
}

void
VkWidgetList::add(Widget w)
{
	_items.push_back(w); 
	XtAddCallback(w, XmNdestroyCallback, widgetDestroyedCB, this);
}

void
VkWidgetList::add(VkComponent* c)
{
	add(c->baseWidget()); 
}

void 
VkWidgetList::remove(Widget w)
{
	XtRemoveCallback(w, XmNdestroyCallback, widgetDestroyedCB, this);
	_items.erase(std::remove(_items.begin(), _items.end(), w),
				 _items.end());
}

void
VkWidgetList::remove(VkComponent* c)
{
	remove(c->baseWidget());
}

void
VkWidgetList::removeLast()
{
	vector<Widget>::iterator it = _items.end() - 1;
	XtRemoveCallback(*it,
					 XmNdestroyCallback, widgetDestroyedCB, this);
	_items.erase(it);
}

void
VkWidgetList::removeFirst()
{
	XtRemoveCallback(*(_items.begin()),
					 XmNdestroyCallback, widgetDestroyedCB, this);
	_items.erase(_items.begin());
}

Boolean
VkWidgetList::exists(Widget w)
{
	if (std::find(_items.begin(), _items.end(), w) == _items.end()) {
		return False;
	} else {
		return True;
	}
}
