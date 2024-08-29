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
 * VkRadioGroup.C
 *
 * This file contains the class implementation for
 * the VkRadioGroup class, which allows programmers
 * to enforce radio-like behavior on toggle buttons
 * and pushbuttons which inhabit different parts
 * of the interface (that is, are not children of the
 * same RowColumn).
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
= "$Id: VkRadioGroup.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkRadioGroup.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>

VkRadioGroup::VkRadioGroup()
	: VkWidgetList()
{
}

VkRadioGroup::~VkRadioGroup()
{
}

void 
VkRadioGroup::add(Widget item)
{
    if (XmIsToggleButton(item) || XmIsToggleButtonGadget(item)) {
		XtVaSetValues(item,
					  XmNindicatorType, XmONE_OF_MANY,
#if XmVERSION >=2
					  XmNtoggleMode, XmTOGGLE_BOOLEAN,
#endif
					  NULL);
		XtAddCallback(item, XmNvalueChangedCallback,
					  valueChangedCallback, this);

		VkWidgetList::add(item);
    } else {
		cerr << "Tried to add non ToggleButton to RadioGroup" << endl;
	}
}

void 
VkRadioGroup::add(VkComponent *component)
{
    add(component->baseWidget());
}

void 
VkRadioGroup::remove(Widget item)
{
	XtRemoveCallback(item, XmNvalueChangedCallback,
					 valueChangedCallback, this);

    VkWidgetList::remove(item);
}

void 
VkRadioGroup::remove(VkComponent *component)
{
    remove(component->baseWidget());
}

void 
VkRadioGroup::removeFirst()
{
    remove((*this)[0]);
}

void 
VkRadioGroup::removeLast()
{
    remove((*this)[size() - 1]);
}

void
VkRadioGroup::valueChanged(Widget w, XtPointer callData)
{
	XmToggleButtonCallbackStruct* cbs =
		(XmToggleButtonCallbackStruct*) callData;

	// Enforce radioAlwaysOne behaviour.
	// If this callback is called when a user clicks on
	// a toggle which is already 'set' then force it back to 'set'.
	//
	// cerr << "VkRadioGroup::valueChanged set = " << cbs->set << endl;
	
	if (!cbs->set) {
		XmToggleButtonSetState(w, true, False);
		return;
	}

	for (_iter = _items.begin(); _iter != _items.end(); _iter++) {
		Widget which = *_iter;
		Boolean on = (which == w);
		if (XmIsToggleButton(which)) {
			XmToggleButtonSetState(which, on, False);
		} else if (XmIsToggleButtonGadget(which)) {
			XmToggleButtonGadgetSetState(which, on, False);
		}
	}
}

void
VkRadioGroup::valueChangedCallback(Widget w, 
								   XtPointer clientData, 
								   XtPointer callData)
{
    VkRadioGroup *obj = (VkRadioGroup*)clientData;

    obj->valueChanged(w, callData);
}
