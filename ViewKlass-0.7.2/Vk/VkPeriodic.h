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
 * $Id: VkPeriodic.h,v 1.2 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for VkPeriodic,
 * which provides a class wrapper for X toolkit time outs.
 *
 * This class isn't publicly documented by SGI (at least, not
 * in the Programmer's Guide), so I had to use to man page to
 * reconstruct it.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKPERIODIC_H
#define VKPERIODIC_H

#include <X11/Intrinsic.h>
#include <Vk/VkConfig.h>
#include <Vk/VkCallbackObject.h>

class VkPeriodic : public VkCallbackObject {
private:
    int _interval;
    XtIntervalId _id;

    static void tickTimeOut(XtPointer, XtIntervalId *);

protected:
    virtual void tick();

public:
    VkPeriodic(int interval);

    virtual ~VkPeriodic();

    void start();
    void stop();

    static const char* timerCallback;
};

#endif // VKPERIODIC_H
