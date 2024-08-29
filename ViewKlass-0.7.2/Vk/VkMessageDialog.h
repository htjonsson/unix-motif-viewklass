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
 * $Id: VkMessageDialog.h,v 1.1 2003/07/22 10:40:43 jostle Exp $
 *
 * This file contains the class definition for the VkMessageDialog class.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMESSAGEDIALOG_H
#define VKMESSAGEDIALOG_H

#include <Vk/VkConfig.h>
#include <Vk/VkDialogManager.h>

class VkMessageDialog : public VkDialogManager {
  
public:

    VkMessageDialog(const char *name);
    virtual Widget createDialog(Widget parent);
    virtual const char *className() { return "VkMessageDialog"; }
};

extern VkMessageDialog* theMessageDialogInstance();
#define theMessageDialog theMessageDialogInstance()

#endif // VKMESSAGEDIALOG
