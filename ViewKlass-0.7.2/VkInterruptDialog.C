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
 * VkInterruptDialog.C
 *
 * This file contains the class implementation for the 
 * VkInterruptDialog class.
 *
 *
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkInterruptDialog.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkInterruptDialog.h>
#include <Vk/VkApp.h>
#include <string.h>

VkInterruptDialog::VkInterruptDialog(const char *name)
	: VkBusyDialog(name),
	  _cancelled(false),
	  _dialogBox(0)
{
	_dialogShellTitle = 0;
	_showOK = False;
	_showHelp = False;
	_showCancel = True;
}

Widget
VkInterruptDialog::createDialog(Widget parent)
{
	_dialogBox = VkBusyDialog::createDialog(parent);
	return _dialogBox;
}

Boolean
VkInterruptDialog::wasInterupted()
// Yes "Interupted" according to the man pages
{
	// Make sure all our requests get to the server.
	XFlush(theApplication->display());
	
	// Let Motif process all pending exposure events for us.
	XmUpdateDisplay(_baseWidget);
	
	// Check the event loop for events in the dialog.
	Window win = XtWindow(_dialogBox);
	XEvent event;
	while (XCheckMaskEvent(theApplication->display(),
						   ButtonPressMask | ButtonReleaseMask |
						   ButtonMotionMask | 
						   PointerMotionMask | KeyPressMask, &event)) {

		// got an "interesting" event.
		if (event.xany.window == win) {
			// it's in our dialog.
			XtDispatchEvent (&event);
		} else {
			// Not in the dialog; throw it away
			// and sound bell if it's a key or button press
			if (event.type == KeyPress ||
				event.type == ButtonPress) {
					XBell (theApplication->display(), 50);
			}
		}
	}
	
 	while (XtAppPending(theApplication->appContext())) {
 		XtAppProcessEvent(theApplication->appContext(), XtIMAll);
 	}

	XFlush(theApplication->display());

	Boolean res = _cancelled;
	_cancelled = false;
	return res;
}

const char *const VkInterruptDialog::interruptedCallback =
"VkInterruptDialog::interruptedCallback";
void
VkInterruptDialog::cancel(Widget dialog, XtPointer callData)
{
	_cancelled = true;
	callCallbacks(VkInterruptDialog::interruptedCallback, 0);
}

VkInterruptDialog* theInterruptDialogInstance()
{
	static VkInterruptDialog* instance = 0;
	if (instance == 0) {
		instance = new VkInterruptDialog("Interrupt");
	}
	return instance;
}
