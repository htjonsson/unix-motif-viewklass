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
 * VkBackground.C
 *
 * This file contains the implementation for VkBackground,
 * which gives the programmer an interface to Xt work
 * procs.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkBackground.C,v 1.6 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkBackground.h>
#include <Vk/VkApp.h>

using namespace std;

VkBackground::VkBackground()
{
    _id = 0;
}

VkBackground::~VkBackground()
{
    stop();
}

void
VkBackground::start()
{
    _id = XtAppAddWorkProc(theApplication->appContext(),
						   (XtWorkProc)timeSliceHandler,
						   (XtPointer)this);
}

void
VkBackground::stop()
{
    if (_id != 0) {
		XtRemoveWorkProc(_id);
		_id = 0;
	}
}

Boolean 
VkBackground::timeSliceHandler(XtPointer clientData)
{
    VkBackground *obj = (VkBackground *)clientData;
    
	Boolean ret = obj->timeSlice();
	if (ret) 
	{
		obj->_id = 0;
	}
    return ret;
}
