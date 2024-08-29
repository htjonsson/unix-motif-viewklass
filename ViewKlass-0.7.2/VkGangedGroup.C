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
 * VkGangedGroup.C
 *
 * This file contains the class implementation
 * for the VkGangedGroup class, which allows the
 * programmer to keep a group of scrollbars or
 * scales at the same value, meaning if you update
 * one, they are all updated.
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
	= "$Id: VkGangedGroup.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkGangedGroup.h>
#include <Xm/ScrollBar.h>
#include <Xm/Scale.h>

using namespace std;

VkGangedGroup::VkGangedGroup()
	: VkWidgetList()
{
}

void 
VkGangedGroup::add(Widget w)
{
	if (XmIsScrollBar(w)){
		XtAddCallback(w, XmNincrementCallback, changeCallback, this);
		XtAddCallback(w, XmNdecrementCallback, changeCallback, this);
		XtAddCallback(w, XmNpageIncrementCallback, changeCallback, this);
		XtAddCallback(w, XmNpageDecrementCallback, changeCallback, this);
		XtAddCallback(w, XmNtoTopCallback, changeCallback, this);
		XtAddCallback(w, XmNtoBottomCallback, changeCallback, this);
		XtAddCallback(w, XmNdragCallback, changeCallback, this);
		XtAddCallback(w, XmNvalueChangedCallback, changeCallback, this);
	}
	else if (XmIsScale(w)){
		XtAddCallback(w, XmNvalueChangedCallback, changeCallback, this);
		XtAddCallback(w, XmNdragCallback, changeCallback, this);
	}

	VkWidgetList::add(w);
}

void 
VkGangedGroup::add(VkComponent *obj)
{
	add(obj->baseWidget());
}

void 
VkGangedGroup::remove(Widget w)
{
	/* remove the callbacks.  see add() above. */
	if (XmIsScrollBar(w)){
		XtRemoveAllCallbacks(w, XmNincrementCallback);
		XtRemoveAllCallbacks(w, XmNdecrementCallback);
		XtRemoveAllCallbacks(w, XmNpageIncrementCallback);
		XtRemoveAllCallbacks(w, XmNpageDecrementCallback);
		XtRemoveAllCallbacks(w, XmNtoTopCallback);
		XtRemoveAllCallbacks(w, XmNtoBottomCallback);
		XtRemoveAllCallbacks(w, XmNdragCallback);
		XtRemoveAllCallbacks(w, XmNvalueChangedCallback);
	}
	else if (XmIsScale(w)){
		XtRemoveAllCallbacks(w, XmNvalueChangedCallback);
		XtRemoveAllCallbacks(w, XmNdragCallback);
	}

	VkWidgetList::remove(w);
}

void 
VkGangedGroup::remove(VkComponent *obj)
{
	remove (obj->baseWidget());
}

void 
VkGangedGroup::removeFirst()
{
	remove((*this)[0]);
}

void 
VkGangedGroup::removeLast()
{
	remove((*this)[size() -1]);
}

void
VkGangedGroup::change(int value)
{
	for (int i = 0; i < size(); ++i) {
		XtVaSetValues((*this)[i], XmNvalue, value, NULL);
	}
}

void
VkGangedGroup::changeCallback(Widget w, XtPointer clientData,
							  XtPointer callData)
{
	VkGangedGroup* me = (VkGangedGroup*)clientData;

	if (XmIsScrollBar(w)) {
		XmScrollBarCallbackStruct *cb = (XmScrollBarCallbackStruct*)callData;
		me->change(cb->value);
	} else if (XmIsScale(w)) {
		XmScaleCallbackStruct *cb = (XmScaleCallbackStruct*)callData;
		me->change(cb->value);
	}
}
