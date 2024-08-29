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
 * $Id: VkProgram.h,v 1.2 2003/04/08 11:31:42 jostle Exp $
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmer, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKPROGRAM_H
#define VKPROGRAM_H

#include <Vk/VkConfig.h>
#include <Vk/VkCallbackObject.h>
#include <Vk/VkSubProcess.h>

class VkProgram : public VkCallbackObject {
protected:
    char *_cmd;
    int _killChildOnExit;
    int _redirectIn;

public:
    VkProgram(const char *cmd, int killChildOnExit = 1);
    
    virtual ~VkProgram(void);

    virtual VkSubProcess *run(void);

    void redirectIn(int do_redirect);

    static const char *const exitCallback;
    static const char *const stdoutCallback;
    static const char *const stderrCallback;
};

#endif // VKPROGRAM_H
