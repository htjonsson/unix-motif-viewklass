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
 * $Id: VkMenuAction.h,v 1.7 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the VkMenuAction class,
 * which is implemented as a push button gadget within the menu.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMENUACTION_H
#define VKMENUACTION_H

#include <Xm/PushBG.h>
#include <Vk/VkConfig.h>
#include <Vk/VkMenuItem.h>

class VkMenuAction : public VkMenuItem {
public:
	VkMenuAction(const char *name,
				 XtCallbackProc  callback = NULL,
				 XtPointer       clientData = NULL); 

	VkMenuAction(const char *name,
				 XtCallbackProc  callback,
				 XtCallbackProc  undoCallback,
				 XtPointer       clientData = NULL);
	
	virtual ~VkMenuAction();

	virtual void undo();

	virtual void build(Widget parent);

	Boolean hasUndo() { return _undoCallback != 0; }

	virtual const char *className() { return "VkMenuAction"; }
  
	virtual Boolean isContainer() { return False; }

	virtual VkMenuItemType menuType() { return ACTION; }

protected:
	// User defined callbacks
	XtCallbackProc _actionCallback;
	XtCallbackProc _undoCallback;
	XtPointer _clientData;

	// Callback to tie the action to theUndoManager.
	static void actionCallback(Widget w, XtPointer clientData,
							   XtPointer callData);
};

class VkMenuActionStub : public VkMenuAction {
//  See man VkMenuUndoManager
//
//  VkComponentList *historylist()
//        Returns a list of objects representing commands that have been
//        executed and that are currently available to be undone. The objects
//        will all be subclasses of VkMenuItem. Actions registered explicitly
//        or using VkAction objects will be returned as VkMenuActionStub
//        objects.  VkMenuActionStub is an empty subclass of VkMenuAction.

public:
	VkMenuActionStub(const char *name,
					 XtCallbackProc  callback,
					 XtCallbackProc  undoCallback,
					 XtPointer       clientData = NULL)
		: VkMenuAction(name, callback, undoCallback, clientData)
		{}
	
	virtual const char *className() { return "VkMenuActionStub"; }
};

#endif // VKMENUACTION_H
