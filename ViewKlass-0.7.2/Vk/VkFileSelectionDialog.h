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
 * $Id: VkFileSelectionDialog.h,v 1.3 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the 
 * VkFileSelectionDialog class.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKFILESELECTIONDIALOG_H
#define VKFILESELECTIONDIALOG_H

#include <Xm/FileSB.h>
#include <Vk/VkConfig.h>
#include <Vk/VkDialogManager.h>

class VkFileSelectionDialog : public VkDialogManager {
public:

    VkFileSelectionDialog(const char *name);
    virtual Widget createDialog(Widget parent);
    virtual const char *className() { return "VkFileSelectionDialog"; }

    void setDirectory(const char *directory);
    void setFilterPattern(const char *pattern);
    void setSelection(const char *selection);

    const char *fileName();
	XmFileSelectionBoxCallbackStruct* callData(void);

	virtual void ok(Widget w, XtPointer callData);

 protected:
  
    char *_directory;
    char *_pattern;
    char *_selection;
    char *_filename;

	Widget _dialogBox;
};

extern VkFileSelectionDialog* theFileSelectionDialogInstance();
#define theFileSelectionDialog theFileSelectionDialogInstance()

#endif // VKFILESELECTIONDIALOG_H
