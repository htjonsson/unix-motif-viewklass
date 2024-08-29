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
 * $Id: VkMenuUndoManager.h,v 1.7 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class declaration for
 * the undo manager.  The programmer registers
 * actions with this manager, and the manager
 * provides the mechanism for the user of the
 * program to undo the action.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved.
 *
 **/

#ifndef VKMENUUNDOMANAGER_H
#define VKMENUUNDOMANAGER_H

#include <Vk/VkConfig.h>
#include <Vk/VkMenuItem.h>
#include <Vk/VkComponentList.h>


class VkMenuUndoManager : public VkMenuAction {

public:
    VkMenuUndoManager(const char* name);
    virtual ~VkMenuUndoManager();

    virtual const char* className() { return "VkMenuUndoManager";};

	void add(VkMenuAction* action);
	
    void add(const char* name, 
			 XtCallbackProc undoCallback,
			 XtPointer clientData);

    VkComponentList* historyList() { return _history; }
    void reset();

    void multiLevel(Boolean flag) { _isMultiLevel = flag; }

    VkMenuItemType menuType() { return ACTION; };
    
    void build(Widget parent);

private:
    static void menuUndoCallback(Widget w, XtPointer clientData,
								 XtPointer callData);

	void actionDeleted(VkCallbackObject* caller, void* clientData,
					   void* callData);

	void updateLabel();

    VkComponentList* _history;
    Boolean _isMultiLevel;

};

extern VkMenuUndoManager* theMenuUndoInstance();
#define theUndoManager theMenuUndoInstance()

#endif // VKMENUUNDOMANAGER_H
