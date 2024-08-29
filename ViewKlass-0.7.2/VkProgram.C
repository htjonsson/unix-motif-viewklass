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
= "$Id: VkProgram.C,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkProgram.h>

using namespace std;

VkProgram::VkProgram(const char *cmd, 
					 int killChildOnExit) : VkCallbackObject()
{
    _killChildOnExit = killChildOnExit;
    _cmd = strdup(cmd);
    _redirectIn = 0;
}

VkProgram::~VkProgram()
{
    free(_cmd);
}

VkSubProcess *
VkProgram::run()
{
    VkSubProcess *foo = new VkSubProcess(_cmd,
										 (VkNameList*)NULL,
										 _killChildOnExit,
										 _redirectIn);

    foo->run();

    return foo;
}

void
VkProgram::redirectIn(int do_redirect)
{
    _redirectIn = do_redirect;
}

const char *const
VkProgram::exitCallback = "VkProgram::exitCallback";

const char *const
VkProgram::stdoutCallback = "VkProgram::stdoutCallback";

const char *const
VkProgram::stderrCallback = "VkProgram::stderrCallback";

