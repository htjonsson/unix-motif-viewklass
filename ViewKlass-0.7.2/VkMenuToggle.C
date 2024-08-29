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
 * VkMenuToggle.C
 *
 * This file contains the implementation for the VkMenuToggle class,
 * which makes it easier to deal with toggle buttons within a menu interface.
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
	= "$Id: VkMenuToggle.C,v 1.12 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkMenuItem.h>

using namespace std;

VkMenuToggle::VkMenuToggle(const char *name,
						   XtCallbackProc callback,
						   XtCallbackProc undoCallback,
						   XtPointer clientData)
	: VkMenuAction(name, callback, undoCallback, clientData),
	  _initialState(False)
{
}

VkMenuToggle::VkMenuToggle(const char *name,
						   XtCallbackProc callback,
						   XtPointer clientData)
	: VkMenuAction(name, callback, clientData),
	  _initialState(False)
{
}

VkMenuToggle::~VkMenuToggle()
{
	XtRemoveAllCallbacks(_baseWidget, XmNvalueChangedCallback);
}

void
VkMenuToggle::setVisualState(Boolean state)
{
	if (_isBuilt) {
		XmToggleButtonGadgetSetState(_baseWidget, state, FALSE);
	}
	_initialState = state;
}

void
VkMenuToggle::setStateAndNotify(Boolean state)
{
	if (_isBuilt) {
		XmToggleButtonGadgetSetState(_baseWidget, state, TRUE);
	}
	_initialState = state;
}

Boolean
VkMenuToggle::getState()
{
	if (_isBuilt) {
		return XmToggleButtonGadgetGetState(_baseWidget);
	} else {
		return FALSE;
	}
}

void
VkMenuToggle::build(Widget parent)
{
	Arg args[4];
	int n = 0;

	short pos = _position == -1 ? XmLAST_POSITION : _position;
	XtSetArg(args[n], XmNpositionIndex, pos); ++n;

	_baseWidget = XmCreateToggleButtonGadget(parent, (char*)name(), args, n);

	installDestroyHandler();

	if (_actionCallback) {
		XtAddCallback(_baseWidget, XmNvalueChangedCallback,
					  _actionCallback, _clientData);
	}
	XtManageChild(_baseWidget);
	XmToggleButtonGadgetSetState(_baseWidget, _initialState, FALSE);
  
	XtSetSensitive(_baseWidget, _sensitive);
	
	_isBuilt = TRUE;
}
