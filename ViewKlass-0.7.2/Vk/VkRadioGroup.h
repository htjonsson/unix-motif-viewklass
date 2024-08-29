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
 * $Id: VkRadioGroup.h,v 1.5 2006/12/23 11:38:37 jostle Exp $
 *
 * This file contains the class declaration for
 * the VkRadioGroup class, which allows programmers
 * to enforce radio-like behavior on toggle buttons
 * and pushbuttons which inhabit different parts
 * of the interface (that is, are not children of the
 * same RowColumn).
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKRADIOGROUP_H
#define VKRADIOGROUP_H

#include <Vk/VkConfig.h>
#include <Vk/VkWidgetList.h>

class VkRadioGroup : public VkWidgetList {
 public:
	VkRadioGroup();
	virtual ~VkRadioGroup();

	virtual void valueChanged(Widget w, XtPointer callData);

	virtual void add(Widget item);
	virtual void add(VkComponent *component);

	virtual void remove(Widget item);
	virtual void remove(VkComponent *component);

	virtual void removeFirst();
	virtual void removeLast();

 private:

	static void valueChangedCallback(Widget w, XtPointer clientData,
									 XtPointer callData);
};

#endif // VKRADIOGROUP_H
