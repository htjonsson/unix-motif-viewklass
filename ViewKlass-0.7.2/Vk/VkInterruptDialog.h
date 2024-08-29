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
 * $Id: VkInterruptDialog.h,v 1.5 2003/08/03 13:23:23 jostle Exp $
 *
 * This file contains the class definition for the 
 * VkInterruptDialog class.
 * 
 *
 *
 **/

#ifndef VKINTERRUPTDIALOG_H
#define VKINTERRUPTDIALOG_H

#include <Vk/VkConfig.h>
#include <Vk/VkBusyDialog.h>

class VkInterruptDialog : public VkBusyDialog {
  
 public:
  
    VkInterruptDialog(const char *name);
	virtual ~VkInterruptDialog() {}

    virtual Widget createDialog(Widget parent);

    virtual const char *className() { return "VkInterruptDialog"; }

	Boolean wasInterupted(); // Yes "Interupted" according to the man page!
	Boolean wasInterrupted() { return wasInterupted(); } // typo fixed in later viewkit

 protected:
	virtual void cancel(Widget dialog, XtPointer);

 private:
	bool _cancelled;

	// The widget which receives events while busy
	Widget _dialogBox;

	static const char *const interruptedCallback;
};

extern VkInterruptDialog* theInterruptDialogInstance();
#define theInterruptDialog theInterruptDialogInstance()

#endif // VKINTERRUPTDIALOG
