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
 * VkMenuUndoManager.C
 *
 * This file contains the class implementation for
 * the undo manager.  The programmer registers 
 * actions with this manager, and the manager provides
 * the mechanism for the user of the program to undo
 * the action.
 *
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkMenuUndoManager.C,v 1.16 2009/03/21 11:44:34 jostle Exp $";

#include <Xm/PushBG.h>
#include <Vk/VkResource.h>
#include <Vk/VkMenuItem.h>

using namespace std;

VkMenuUndoManager::VkMenuUndoManager(const char* name)
	: VkMenuAction(name),
	  _isMultiLevel(true)
{
	_history = new VkComponentList();
}

VkMenuUndoManager::~VkMenuUndoManager()
{
	reset();
	delete _history;
}

void 
VkMenuUndoManager::build(Widget parent)
{
	Arg args[4];
	int n = 0;

	short pos = _position == -1 ? XmLAST_POSITION : _position;
	XtSetArg(args[n], XmNpositionIndex, pos); ++n;

    _baseWidget = XmCreatePushButtonGadget(parent, (char*)name(), args, n);

	installDestroyHandler();

	XtAddCallback(_baseWidget, XmNactivateCallback,
				  (XtCallbackProc)VkMenuUndoManager::menuUndoCallback,
				  (XtPointer)this);

	XtManageChild(_baseWidget);
	
	XtSetSensitive(_baseWidget, _sensitive);
    
    _isBuilt = TRUE;
}

void
VkMenuUndoManager::add(VkMenuAction* action)
{
	if (_isMultiLevel || _history->size() == 0) {
		_history->add(action);
	} else {
		_history->remove(0);
		_history->add(action);
	}

	updateLabel();
	
	activate();

	action->addCallback(VkComponent::deleteCallback, this,
						(VkCallbackMethod)&VkMenuUndoManager::actionDeleted);
}

void
VkMenuUndoManager::add(const char* name,
		       XtCallbackProc undoCallback,
		       XtPointer clientData)
{
	VkMenuActionStub* stub = new VkMenuActionStub(name, NULL,
											 undoCallback, clientData);
	add(stub);
}

void
VkMenuUndoManager::reset()
{
	for (int i = _history->size() - 1; i >= 0; --i) {
		// Check if this is an action stub which has been
		// created by this class. If so we are responsible
		// for deleting it.
		VkMenuAction* action =
			dynamic_cast<VkMenuAction*>((*_history)[i]);
		if (strcmp("VkMenuActionStub", action->className()) == 0) {
			// The item will remove itself from the list when it is deleted.
			delete action;
		} else {
			// Just remove the item from our list
			_history->remove(i);
		}
	}
	updateLabel();
}

void
VkMenuUndoManager::actionDeleted(VkCallbackObject* caller, void* clientData,
								 void* callData)
{
	// cerr << "VkMenuUndoManager::actionDeleted action = " << caller << endl;
	
	VkMenuAction* action =
		(VkMenuAction*)(caller);
	// Just remove the item from our list
	_history->remove(action);
	
	updateLabel();
}

void
VkMenuUndoManager::menuUndoCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	VkMenuUndoManager* me = (VkMenuUndoManager*)clientData;
	// Check that there is actually something to undo
	int histSize = me->_history->size();
	if (histSize > 0) {
		// If the action is undoable, call its undo method
		VkMenuAction* action =
			dynamic_cast<VkMenuAction*>((*(me->_history))[histSize - 1]);
		if (action->hasUndo()) {
			action->undo();
		}

		// Check if this is an action stub which has been
		// created by this class. If so we are responsible
		// for deleting it.
		if (strcmp("VkMenuActionStub", action->className()) == 0) {
			// Deleting the action will also remove it from the list.
			delete action;
		} else {
			// Remove the action from the undo list.
			me->_history->remove(histSize - 1);
		}

		me->updateLabel();
	}
}

void
VkMenuUndoManager::updateLabel()
{
	char* resourceLabel =
		(char*)VkGetResource(_baseWidget, "Undo.labelString", XmCString,
							 XmRString, "Undo");
	string label = resourceLabel;
	int histSize = _history->size();
	if (histSize > 0) {
		label += ":";
		// Update the undo label
		VkMenuItem* action =
			(VkMenuItem*)(*(_history))[histSize - 1];
		if (strcmp("VkMenuActionStub", action->className()) == 0) {
			label += action->name();
		} else {		
			XmString xmstr;
			XtVaGetValues(action->baseWidget(),
						  XmNlabelString, &xmstr, NULL);
			char* actionLabel;
			XmStringGetLtoR(xmstr, XmFONTLIST_DEFAULT_TAG, &actionLabel);
			label += actionLabel;
			XtFree(actionLabel);
			XmStringFree(xmstr);
		}
	} else {
		// Disable the menu button
		deactivate();
	}
	setLabel(label.c_str());
}

VkMenuUndoManager* theMenuUndoInstance()
{
	static VkMenuUndoManager* instance = 0;
	if (instance == 0) {
		instance = new VkMenuUndoManager("Undo");
		instance->deactivate();
	}
	return instance;
}
