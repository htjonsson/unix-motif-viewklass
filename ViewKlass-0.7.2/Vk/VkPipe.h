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
 * $Id: VkPipe.h,v 1.4 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for VkPipe, which
 * provides an interface to unix pipes.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKPIPE_H
#define VKPIPE_H

#include <Vk/VkConfig.h>
#include <Vk/VkCallbackObject.h>
#include <Vk/VkInput.h>

typedef enum {READ, WRITE} End;

class VkPipe : public VkCallbackObject {
public:
    VkPipe(int &fd);

    virtual ~VkPipe();

    int operator[](End whichEnd);

    static const char *const inputCallback;

protected:
    int pipefd[2];
    VkInput* _input;

    void handleInput(VkCallbackObject *, void *, void *);

private:
	// Post a Fatal Error dialog with msg and system error string.
	void die(int err, const char* msg);
	
};

#endif // VKPIPE_H

