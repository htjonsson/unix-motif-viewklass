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
 * VkPipe.C
 *
 * This file contains the implementation for the VkPipe
 * class, which gives the programmer an interface to 
 * unix pipes.
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
= "$Id: VkPipe.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkPipe.h>
#include <Vk/VkFatalErrorDialog.h>

#include <fcntl.h>
#include <sys/file.h>  // dumb HPUX
#include <unistd.h>

using namespace std;

VkPipe::VkPipe(int &fd)
{
	int err = 0;
    if ((err = pipe(pipefd)) < 0) {
		die(err, "pipe() system call failed");
	}
	
    fd = pipefd[1];

    if ((err = fcntl(pipefd[0], F_SETFL, FNDELAY)) < 0) {
		die(err, "fcntl() on read fd failed");
	}
	
	if ((err = fcntl(pipefd[1], F_SETFL, FNDELAY)) < 0) {
		die(err, "fcntl() on write fd failed");
	}

    _input = new VkInput();
    _input->attach(pipefd[0], XtInputReadMask);
    _input->addCallback(VkInput::inputCallback, 
						this,
						(VkCallbackMethod)(&VkPipe::handleInput));
}

VkPipe::~VkPipe()
{
    close(pipefd[0]);
    close(pipefd[1]);
}

int
VkPipe::operator[](End whichEnd)
{
    switch (whichEnd){
    case READ:
		return pipefd[0];
		break;
    case WRITE:
		return pipefd[1];
		break;
    }
	// Can't legally get here so return a harmless READ
	return pipefd[0];
}

void
VkPipe::handleInput(VkCallbackObject *obj, void *, void *callData)
{
    callCallbacks(VkPipe::inputCallback, this);
}

const char *const 
VkPipe::inputCallback = "VkPipe::inputCallback";

void
VkPipe::die(int err, const char* msg)
{
	string message = msg;
	message += "\n";
	message += strerror(err);
	theFatalErrorDialog->postModal(message.c_str());
}

