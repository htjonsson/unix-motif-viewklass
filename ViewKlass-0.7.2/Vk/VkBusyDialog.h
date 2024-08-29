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
 * $Id: VkBusyDialog.h,v 1.3 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the 
 * VkBusyDialog class.
 * 
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKBUSYDIALOG_H
#define VKBUSYDIALOG_H

#include <Vk/VkConfig.h>
#include <Vk/VkDialogManager.h>

class VkBusyDialog : public VkDialogManager {
  
 public:
  
    VkBusyDialog(const char *name);
	virtual ~VkBusyDialog() {}

    virtual Widget createDialog(Widget parent);

    virtual const char *className() { return "VkBusyDialog"; }

};


extern VkBusyDialog* theBusyDialogInstance();
#define theBusyDialog theBusyDialogInstance()

#endif // VKBUSYDIALOG_H
