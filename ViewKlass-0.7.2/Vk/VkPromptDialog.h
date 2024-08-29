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
 * $Id: VkPromptDialog.h,v 1.6 2003/12/13 02:09:34 jostle Exp $
 *
 * This file contains the class definition for VkPromptDialog.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKPROMPTDIALOG_H
#define VKPROMPTDIALOG_H

#include <Vk/VkConfig.h>
#include <Vk/VkDialogManager.h>

class VkPromptDialog : public VkDialogManager {
  
public:

    VkPromptDialog(const char *name);
	virtual ~VkPromptDialog();

	const char* text();
	void setText(const char* text);

    virtual const char *className() { return "VkPromptDialog"; }
	
protected:
    virtual Widget createDialog(Widget parent);

	char* _text;
	
private:
	Widget _dialogBox;
	
};

extern VkPromptDialog* thePromptDialogInstance();
#define thePromptDialog thePromptDialogInstance()

#endif /* VKPROMPTDIALOG_H */

