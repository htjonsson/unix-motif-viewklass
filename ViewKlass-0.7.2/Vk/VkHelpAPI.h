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
 * $Id: VkHelpAPI.h,v 1.4 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the API to the
 * ViewKlass help system.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKHELPAPI_H
#define VKHELPAPI_H

#include <X11/Xlib.h>
#include <Vk/VkConfig.h>

extern "C" {
    int SGIHelpInit(Display* display, const char* appClass,
                    const char* reserved);
    int SGIHelpMsg(const char* in_key, const char* in_book,
                   const char* reserved);
    int SGIHelpIndexMsg(const char* in_key, const char* in_book);
};

#endif /* VKHELPAPI_H */
