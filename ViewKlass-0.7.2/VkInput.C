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
 * VkInput.C
 *
 * This file contains the implementation for the
 * VkInput class, which encapsulates callbacks
 * on file descriptors 
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: VkInput.C,v 1.11 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkInput.h>
#include <Vk/VkApp.h>

using namespace std;

VkInput::VkInput()
	: VkCallbackObject(),
	  _id(0),
	  _fd(-1)
{
}

VkInput::~VkInput()
{
    remove();
}

void
VkInput::attach(int fd, XtInputMask mask)
{
    if (_fd != -1) {
		remove();
	}
    _fd = fd;

    _id = XtAppAddInput(theApplication->appContext(),
						fd,
						(XtPointer)mask,
						inputHandler,
						(XtPointer)this);
}

void
VkInput::remove()
{
    _fd = -1;
	if (_id != 0) {
		XtRemoveInput(_id);
		_id = 0;
	}
}

int
VkInput::fd()
{
    return _fd;
}

int
VkInput::id()
{
    return _id;
}

void
VkInput::inputHandler(XtPointer clientData,
					  int* fd,
					  XtInputId* id)
{
    VkInput *obj = (VkInput*)clientData;

	if (*fd == obj->_fd && *id == obj->_id ) {
		obj->callCallbacks(obj->inputCallback, obj);
	}
}

const char *const
VkInput::inputCallback = "VkInput::inputCallback";
