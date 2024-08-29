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
 * $Id: VkRepeatButton.h,v 1.7 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the class declaration for
 * the VkRepeatButton class, which allows programmers
 * to add buttons that repeatedly call callbacks once
 * armed.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKREPEATBUTTON_H
#define VKREPEATBUTTON_H

#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/ArrowB.h>
#include <Xm/ArrowBG.h>

typedef enum {
	RB_pushButton,
	RB_pushButtonGadget,
	RB_arrowButton,
	RB_arrowButtonGadget
} VkRepeatButtonType;

class VkRepeatButton : public VkComponent {
public:
	VkRepeatButton(const char* name, Widget parent, VkRepeatButtonType type);
	virtual ~VkRepeatButton();

	void setParameters(long initial, long repeat);

	VkRepeatButtonType type() { return _type; }

	virtual const char* className() { return "VkRepeatButton"; }

	static const char* buttonCallback;

private:
	static const char* const _defaultResources[];

	long _initialDelay;
	long _repeatDelay;

	XtIntervalId _repeatId;
	XmAnyCallbackStruct _myCallbackInfo;

	VkRepeatButtonType _type;

	static void beginRepeatCallback(Widget w, XtPointer clientData,
									XtPointer callData);
	static void endRepeatCallback(Widget w, XtPointer clientData,
								  XtPointer callData);

	static void repeatTimeOut(XtPointer, XtIntervalId*);

	void beginRepeat(XtPointer);
	void endRepeat();
	void repeat();

};

#endif // VKREPEATBUTTON_H
