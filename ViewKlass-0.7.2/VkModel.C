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
 * VkModel.C
 *
 * This file contains the class implementation for the 
 * abstract class of VkModel, which presents a more MVC
 * like smalltalk interface to c++ programmers.
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
= "$Id: VkModel.C,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkModel.h>

using namespace std;

const char* const VkModel::updateCallback = "VkModel::updateCallback";

VkModel::VkModel()
{
}

void
VkModel::updateViews(void *data)
{
    callCallbacks(VkModel::updateCallback, data);
}

VkModel::~VkModel()
{
}
