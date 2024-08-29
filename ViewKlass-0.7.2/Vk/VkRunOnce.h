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
 * $Id: VkRunOnce.h,v 1.4 2003/12/13 02:17:38 jostle Exp $
 *
 * This file contains the definition for the VkRunOnce class,
 * which allows applications to specify that they should only
 * be run once on a given machine. 
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All RIghts Reserved
 *
 **/

#ifndef VKRUNONCE_H
#define VKRUNONCE_H

#include <Vk/VkConfig.h>
#include <Vk/VkCallbackObject.h>
#include <Vk/VkNameList.h>

class VkRunOnce : public VkCallbackObject {
public:
    VkRunOnce(VkNameList *args, Boolean per_host);
    virtual ~VkRunOnce() {}

    int numArgs();
    char *arg(int indx);

    const char *const invokedCallback;
};

#endif // VKRUNONCE_H
