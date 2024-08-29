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
 * VkPeriodic.C
 *
 * This file contains the class implementation for the 
 * VkPeriodic class, which encapsulates the Xt timeout
 * implementation, and offers periodic timeouts.
 *
 * Chris Toshok
 * Copyright (C) 1994, 1995
 * The Hungry Programmers, Inc.
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPeriodic.C,v 1.9 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkPeriodic.h>
#include <Vk/VkApp.h>

using namespace std;

const char* VkPeriodic::timerCallback = "VkPeriodicTimerCallback";

VkPeriodic::VkPeriodic(int interval)
	: VkCallbackObject(),
	  _interval(interval),
	  _id(0)
{
}

VkPeriodic::~VkPeriodic()
{
	if (_id != 0) {
		stop();
	}
}

void
VkPeriodic::start()
{
    _id = XtAppAddTimeOut(theApplication->appContext(),
			  _interval,
			  tickTimeOut,
			  this);
}

void
VkPeriodic::stop()
{
	// Xt doesn't like removing timeout with an id of zero.
	if (_id != 0) {
		XtRemoveTimeOut(_id);
		// Guard against callbacks occurring after we have been deleted.
		_id = 0;
	}
}

void
VkPeriodic::tickTimeOut(XtPointer clientData, XtIntervalId* intervalId)
{
    VkPeriodic *obj = (VkPeriodic*)clientData;

	// Guard against callbacks occurring after we have been deleted.
	if (obj->_id != 0) {
		// It is important to start the new timeout before
		// calling tick() because that is when the user gets the
		// chance to call stop().
		obj->_id = XtAppAddTimeOut(theApplication->appContext(),
								   obj->_interval,
								   obj->tickTimeOut,
								   obj);
		
		obj->tick();
		obj->callCallbacks(timerCallback, NULL);
	}
}

void
VkPeriodic::tick()
{
}
