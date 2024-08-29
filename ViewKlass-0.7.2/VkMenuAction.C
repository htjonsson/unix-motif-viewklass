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
 * VkMenuAction.C
 *
 *
 * This file contains the source for the VkMenuAction class.
 * This class, and its derivatives, account for most of the user
 * interface acreage that you normally see.  It's a pretty important
 * class.
 *
 * Chris Toshok
 * Copyright (C) 1994
 * The Hungry Programmers, Inc
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: VkMenuAction.C,v 1.12 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkMenuItem.h>

VkMenuAction::VkMenuAction(const char *name,
						   XtCallbackProc callback,
						   XtCallbackProc undoCallback,
						   XtPointer clientData)
	: VkMenuItem(name),
	  _actionCallback(callback),
	  _undoCallback(undoCallback),
	  _clientData(clientData)
{

}

VkMenuAction::VkMenuAction(const char *name,
						   XtCallbackProc callback,
						   XtPointer clientData)
	: VkMenuItem(name),
	  _actionCallback(callback),
	  _undoCallback(0),
	  _clientData(clientData)
{
}

VkMenuAction::~VkMenuAction()
{
	if (_isBuilt) {
		XtRemoveAllCallbacks(_baseWidget, XmNactivateCallback);
	}
}

void
VkMenuAction::undo()
{
	if (_undoCallback) {
		// Do some undoing!
		(*_undoCallback)(_baseWidget, _clientData, 0);
	}
}

void
VkMenuAction::build(Widget parent)
{
	Arg args[4];
	int n = 0;

	short pos = _position == -1 ? XmLAST_POSITION : _position;
	XtSetArg(args[n], XmNpositionIndex, pos); ++n;

	_baseWidget = XmCreatePushButtonGadget(parent, (char*)name(), args, n);

	installDestroyHandler();

	XtAddCallback(_baseWidget, XmNactivateCallback,
				  &VkMenuAction::actionCallback, this);
  
	XtManageChild(_baseWidget);

	XtSetSensitive(_baseWidget, _sensitive);

	VkMenuItem::build(parent);
}

void
VkMenuAction::actionCallback(Widget w, XtPointer clientData,
							 XtPointer callData)
{
	VkMenuAction* me = (VkMenuAction*)clientData;
	if (me->_actionCallback) {
		(*(me->_actionCallback))(w, me->_clientData, callData);
		if (me->_undoCallback) {
			theUndoManager->add(me);
		}
	}
}
