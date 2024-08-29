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
 * $Id: VkSubProcess.h,v 1.2 2003/04/08 11:31:42 jostle Exp $
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKSUBPROCESS_H
#define VKSUBPROCESS_H

#include <Vk/VkConfig.h>
#include <Vk/VkCallbackObject.h>
#include <Vk/VkPipe.h>
#include <Vk/VkNameList.h>
#include <signal.h>

class VkSubProcess : public VkCallbackObject {
private:
    pid_t _pid;
    char *_cmd;
    VkNameList *_args;

    int _killMeOnExit;
    int _redirectIn;

    int stdinFd;

    VkPipe *_stdout;
    VkPipe *_stderr;
    VkPipe *_stdin;

public:
    VkSubProcess(char *cmd,
		 VkNameList *argv,
		 int killChildOnExit,
		 int redirectIn);

    virtual ~VkSubProcess();

    pid_t pid();
    int exitStatus();
    int stdinfd();
    VkPipe *getStdoutPipe();
    VkPipe *getStderrPipe();

    void signal(int sig);
    void kill(int sig = SIGTERM);
    void run(void);
};

#endif // VKSUBPROCESS_H
