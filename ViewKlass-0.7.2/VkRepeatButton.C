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
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

/**
 *
 * VkRepeatButton.C
 *
 * This file contains the class implementation for
 * the VkRepeatButton class, which allows programmers
 * to add buttons that repeatedly call callbacks once
 * armed.
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
= "$Id: VkRepeatButton.C,v 1.12 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkApp.h>
#include <Vk/VkRepeatButton.h>
#include <Vk/VkResource.h>

using namespace std;

const char* const VkRepeatButton::_defaultResources[] = {
	"*initialDelay: 1000",
	"*repeatDelay: 200",
	NULL
};

VkRepeatButton::VkRepeatButton(const char *name, Widget parent,
							   VkRepeatButtonType type)
	: VkComponent(name),
	  _initialDelay(1000),
	  _repeatDelay(200),
	  _type(type)
{
	setDefaultResources(parent, _defaultResources);

	switch (_type){
	case RB_pushButton:
        _baseWidget = XmCreatePushButton(parent,
                                         const_cast<char*>(name),
                                         NULL, 0);
		installDestroyHandler();
        break;
	case RB_pushButtonGadget:
        _baseWidget = XmCreatePushButtonGadget(parent,
                                               const_cast<char*>(name),
                                               NULL, 0);
        break;
	case RB_arrowButton:
        _baseWidget = XmCreateArrowButton(parent,
                                          const_cast<char*>(name),
                                          NULL, 0);
		installDestroyHandler();
        break;
	case RB_arrowButtonGadget:
        _baseWidget = XmCreateArrowButtonGadget(parent,
                                                const_cast<char*>(name),
                                                NULL, 0);
        break;
	}


	XtAddCallback(_baseWidget, XmNarmCallback, beginRepeatCallback, this);
	XtAddCallback(_baseWidget, XmNdisarmCallback, endRepeatCallback, this);

	XtManageChild(_baseWidget);

  	_initialDelay =(long)VkGetResource(_baseWidget,
									  "initialDelay", "InitialDelay",
									  XmRInt, "1000");
  	_repeatDelay = (long)VkGetResource(_baseWidget,
									  "repeatDelay", "RepeatDelay",
									  XmRInt, "200");
}

VkRepeatButton::~VkRepeatButton()
{
		// cout << "VkRepeatButton::~VkRepeatButton()" << endl;
}


void
VkRepeatButton::setParameters(long initial, long repeat)
{
	_initialDelay = initial;
	_repeatDelay = repeat;
}

void
VkRepeatButton::beginRepeat(XtPointer callData)
{
	XmAnyCallbackStruct *cb = (XmAnyCallbackStruct*)callData;

	_myCallbackInfo.reason = cb->reason;
	_myCallbackInfo.event = cb->event;

	_repeatId = XtAppAddTimeOut(theApplication->appContext(),
								(unsigned long)_initialDelay,
								repeatTimeOut, this);
}

void
VkRepeatButton::beginRepeatCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	VkRepeatButton *obj = (VkRepeatButton*)clientData;
	obj->beginRepeat(callData);
}

void
VkRepeatButton::endRepeat()
{
	XtRemoveTimeOut(_repeatId);
}

void
VkRepeatButton::endRepeatCallback(Widget w, XtPointer clientData,
								  XtPointer callData)
{
	VkRepeatButton *obj = (VkRepeatButton*)clientData;
	obj->endRepeat();
}

void
VkRepeatButton::repeat()
{
	_repeatId = XtAppAddTimeOut(theApplication->appContext(),
								_repeatDelay,
								repeatTimeOut, this);

	callCallbacks(VkRepeatButton::buttonCallback,
				  (void*) &_myCallbackInfo);
}

void
VkRepeatButton::repeatTimeOut(XtPointer clientData, XtIntervalId *id)
{
	VkRepeatButton *obj = (VkRepeatButton*)clientData;
	obj->repeat();
}

const char*
VkRepeatButton::buttonCallback = "VkRepeatButton::buttonCallback";

