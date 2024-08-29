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
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkSubProcess.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkSubProcess.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h> // for exec*

VkSubProcess::VkSubProcess(char *prog,
						   VkNameList *given,
						   int killChildOnExit,
						   int redirectIn)
{
    _pid = 0;
    _redirectIn = redirectIn;
    _killMeOnExit = killChildOnExit;
    _cmd = strdup(prog);
    _args = new VkNameList(*given);

    _stdin = _stderr = _stdout = NULL;
}

VkSubProcess::~VkSubProcess()
{
    delete _stdout;
    delete _stderr;
    delete _stdin;

	delete _args;

    free(_cmd);
}

pid_t
VkSubProcess::pid()
{
    return _pid;
}

int
VkSubProcess::exitStatus()
{
	// Don't know what to do here!!
	return 0;
}

int 
VkSubProcess::stdinfd()
{
    return stdinFd;
}

VkPipe *
VkSubProcess::getStdoutPipe()
{
    return _stdout;
}

VkPipe *
VkSubProcess::getStderrPipe()
{
    return _stderr;
}

void
VkSubProcess::signal(int sig)
{
    kill(sig);
}

void
VkSubProcess::kill(int sig)
{
	cerr << "VkSubProcess calling ::kill() for " << _cmd << endl;
    ::kill(_pid, sig);
}

void
VkSubProcess::run()
{
    int stdoutOut;
    int stderrOut;

    if (_redirectIn)
		_stdin = new VkPipe(stdinFd);

    _stdout = new VkPipe(stdoutOut);
    _stderr = new VkPipe(stderrOut);

    if ((_pid = fork()) == 0)
    {
		/* child */

		dup2(stdoutOut, 1);
		dup2(stderrOut, 2);
		dup2((*_stdin)[READ], 0);

		execvp(_cmd, (char**)(*_args));
    }
    else
    {
		/* parent */
    }
}
