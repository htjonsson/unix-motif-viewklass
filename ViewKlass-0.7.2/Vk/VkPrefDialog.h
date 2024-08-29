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
 * $Id: VkPrefDialog.h,v 1.4 2003/12/13 02:09:34 jostle Exp $
 *
 * This file contains the definition for the 
 * VkPrefDialog class, which implements a preference
 * dialog box, subclassed from VkGenericDialog.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKPREFDIALOG_H
#define VKPREFDIALOG_H

#include <Vk/VkConfig.h>
#include <Vk/VkGenericDialog.h>
#include <Vk/VkPrefItem.h>

class VkPrefDialog : public VkGenericDialog {
public:
    VkPrefDialog(const char *name, VkPrefItem *item = NULL);

	virtual ~VkPrefDialog();

	Widget createDialog(Widget parent);

    void setItem(VkPrefItem *item);
    
    VkPrefItem *item();

    static const char prefCallback[];

	virtual void ok(Widget w, XtPointer callData);
	virtual void apply(Widget w, XtPointer callData);
	virtual void cancel(Widget w, XtPointer callData);

private:
    VkPrefItem *_item;

	Widget _dialogBox;
};

#endif // VKPREFDIALOG_H

