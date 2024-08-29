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
 * VkMenuConfirmFirstAction.C
 *
 * This file contains the source code for the implementation of the
 * VkMenuConfirmFirstAction controls.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkMenuConfirmFirstAction.C,v 1.13 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkMenuItem.h>
#include <Vk/VkQuestionDialog.h>
#include <Vk/VkApp.h>

#include <stdio.h>

using namespace std;

VkMenuConfirmFirstAction::VkMenuConfirmFirstAction(const char *name,
						   XtCallbackProc callback,
						   XtCallbackProc undoCallback,
						   XtPointer clientData)
	: VkMenuAction(name, callback, undoCallback, clientData)
{
}

VkMenuConfirmFirstAction::VkMenuConfirmFirstAction(const char *name,
						   XtCallbackProc callback,
						   XtPointer clientData)
	: VkMenuAction(name, callback, clientData)
{
}

void
VkMenuConfirmFirstAction::confirmCallback(Widget, XtPointer clientData,
										   XtPointer callData)
{
    VkMenuConfirmFirstAction *obj = (VkMenuConfirmFirstAction*)clientData;
  
	string resource = "*";
	resource += obj->name();
	resource += ".";
	resource += "noUndoQuestion";
	
    char* msg = (char*)VkGetResource(obj->baseWidget(),
									 resource.c_str(),
									 "NoUndoQuestion",
									 XmRString,
									 "This action cannot be undone.\n"
									 "Do you want to proceed anyway?");

	theQuestionDialog->post(
		msg, obj->_actionCallback, NULL, NULL,
		obj->_clientData, NULL,
		theApplication->mainWindow(), NULL);

}

void
VkMenuConfirmFirstAction::build(Widget parent)
{
	Arg args[4];
	int n = 0;

	short pos = _position == -1 ? XmLAST_POSITION : _position;
	XtSetArg(args[n], XmNpositionIndex, pos); ++n;

    _baseWidget = XmCreatePushButtonGadget(parent, (char*)name(), args, n);

	installDestroyHandler();

    if (_actionCallback) {
		XtAddCallback(_baseWidget, XmNactivateCallback,
					  confirmCallback, (XtPointer)this);
	}

    XtManageChild(_baseWidget);

	XtSetSensitive(_baseWidget, _sensitive);

    _isBuilt = TRUE;
}

