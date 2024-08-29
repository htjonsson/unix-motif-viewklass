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
 * $Id: VkBackground.h,v 1.2 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the definition for the VkBackground 
 * class, which gives a C++ interface to Xt work procedures.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved.
 *
 **/

#ifndef VKBACKGROUND_H
#define VKBACKGROUND_H

#include <X11/Intrinsic.h>
#include <Vk/VkConfig.h>

class VkBackground {
private:
    XtWorkProcId _id;
    static Boolean timeSliceHandler(XtPointer clientData);

protected:
    virtual Boolean timeSlice() = 0;

public:
    VkBackground();
    virtual ~VkBackground();

    void start();
    void stop();
};

#endif // VKBACKGROUND_H
