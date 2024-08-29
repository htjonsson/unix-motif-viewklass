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
 * VkSimpleWindow.C
 *
 * This file contains the implementation for the VkSimpleWindow
 * class, which implements the base class for all windows that
 * appear on the screen (except dialogs, of course).
 *
 * Chris Toshok
 * Copyright (C) 1994
 * The Hungry Programmers, Inc
 *
 **/

#include <iostream>

using namespace std;

#include <Vk/VkSimpleWindow.h>
#include <Vk/VkApp.h>

#include <Xm/AtomMgr.h>
#include <Xm/Protocols.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xmu/Editres.h>

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkSimpleWindow.C,v 1.18 2009/03/21 11:44:34 jostle Exp $";



VkSimpleWindow::VkSimpleWindow(const char *name,
							   ArgList args,
							   Cardinal argCount)
	: VkComponent(name),
	  _windowTitle(0),
	  _iconName(0)
{
    Atom WM_DELETE_WINDOW;
    Atom WM_QUIT_APP;

    WM_DELETE_WINDOW = XmInternAtom(theApplication->display(),
									(char*)"WM_DELETE_WINDOW", False);

    WM_QUIT_APP = XmInternAtom(theApplication->display(),
							   (char*)"WM_QUIT_APP", True);

    _baseWidget = XtCreatePopupShell(
		name, topLevelShellWidgetClass,
		theApplication->baseWidget(), args, argCount);

	XtVaSetValues(_baseWidget, XmNdeleteResponse, XmUNMAP, NULL);

    installDestroyHandler();

    XmAddWMProtocolCallback(
		_baseWidget, WM_DELETE_WINDOW, wm_delete_window, this);

    if (WM_QUIT_APP != None)
		XmAddWMProtocolCallback(_baseWidget, WM_QUIT_APP, wm_quit_app, this);

    XtAddEventHandler(
		_baseWidget, (EventMask)0, True,
		(XtEventHandler)_XEditResCheckMessages, NULL);

    _mainWindowWidget = XmCreateMainWindow(_baseWidget,
										   (char *)name,
										   args,
										   argCount);

    XtManageChild(_mainWindowWidget);

    theApplication->registerWindow(this);
    _currentView = NULL;

    _iconState = ICON_UNKNOWN;
    _visibleState = VISIBLE_UNKNOWN;
    _stackingState = STACKING_UNKNOWN;
}

VkSimpleWindow::~VkSimpleWindow()
{
    theApplication->unregisterWindow(this);
    XtRemoveEventHandler(_baseWidget, StructureNotifyMask, False,
						 change_state_handler, this);
	XtRemoveEventHandler(_baseWidget, (EventMask)0, True,
						 (XtEventHandler)_XEditResCheckMessages, NULL);
    delete []_windowTitle;
    delete []_iconName;
}

void
VkSimpleWindow::show()
{
    if (_visibleState == VISIBLE_UNKNOWN) {
		/* This only happens when the window hasn't
		   appeared on the screen before. */

		if (theApplication->_startupIconified) {
            XtVaSetValues(_baseWidget, XtNiconic, True, NULL);
			_iconState = CLOSED;
		} else {
			_iconState = OPEN;
		}

		if (!_currentView) {
			addView(setUpInterface(mainWindowWidget()));
		}

		XtPopup(_baseWidget, XtGrabNonexclusive);

		_visibleState = VISIBLE;

		XtAddEventHandler(_baseWidget, StructureNotifyMask, False,
						  change_state_handler, this);

		setUpWindowProperties();
		afterRealizeHook();
    } else if (_visibleState == HIDDEN && _iconState != CLOSED) {
		XtPopup(_baseWidget, XtGrabNonexclusive);
		_visibleState = VISIBLE;
    }
}

void
VkSimpleWindow::setUpWindowProperties()
{
    XTextProperty *wm_name = NULL;
    XTextProperty *icon_name = NULL;

    if (_windowTitle) {
		wm_name = new XTextProperty;
		XStringListToTextProperty(&_windowTitle, 1, wm_name);
    }

    if (_iconName) {
		icon_name = new XTextProperty;
		XStringListToTextProperty(&_iconName, 1, icon_name);
    }

    XSetWMProperties(theApplication->display(),
					 XtWindow(_baseWidget),
					 wm_name,
					 icon_name,
					 theApplication->argv(),
					 theApplication->argc(),
					 NULL, /* normal_hints */
					 NULL, /* wm_hints */
					 NULL  /* class_hints */);

    if (icon_name) {
		XFree (icon_name->value);
		icon_name->value = NULL;
		delete icon_name;
    }

    if (wm_name) {
		XFree (wm_name->value);
		wm_name->value = NULL;
		delete wm_name;
    }
}

void
VkSimpleWindow::hide()
{
    XtPopdown(_baseWidget);
    _visibleState = HIDDEN;
}

void
VkSimpleWindow::iconify()
{
    if (_visibleState != HIDDEN && _iconState != CLOSED) {
		XIconifyWindow(theApplication->display(),
					   XtWindow(_baseWidget),
					   XScreenNumberOfScreen(XtScreen(_baseWidget)));

		stateChanged(CLOSED);
    }
}

void
VkSimpleWindow::open()
{
    if (_iconState == CLOSED) {
		XtPopup(_baseWidget, XtGrabNonexclusive);
		stateChanged(OPEN);
    }
}

void
VkSimpleWindow::raise()
{
	XRaiseWindow(theApplication->display(),
				 XtWindow(baseWidget()));
}

void
VkSimpleWindow::lower()
{
    XLowerWindow(theApplication->display(),
				 XtWindow(baseWidget()));
}

void
VkSimpleWindow::handleRawEvent(XEvent *event)
{
    /* empty */
}

Widget
VkSimpleWindow::mainWindowWidget() const
{
    return _mainWindowWidget;
}

void
VkSimpleWindow::addView(Widget w)
{
    if (_currentView) {
		removeView();
	}
    XtManageChild(w);
    _currentView = w;
}

void
VkSimpleWindow::addView(VkComponent *component)
{
	addView(component->baseWidget());
}

void
VkSimpleWindow::removeView()
{
    XtUnmanageChild(_currentView);
    _currentView = NULL;
}

Widget
VkSimpleWindow::viewWidget() const
{
    return _currentView;
}

Boolean
VkSimpleWindow::visible() const
{
    return _visibleState == VISIBLE;
}

Boolean
VkSimpleWindow::iconic() const
{
    return _iconState == CLOSED;
}

int
VkSimpleWindow::getVisualState()
{
	int state = 0;
	if (_visibleState == VISIBLE) {
		if (_iconState == CLOSED) {
			state = IconicState;
		} else {
			state = NormalState;
		}
	} else {
		if (_iconState == CLOSED) {
			state = WithdrawnIconicState;
		} else {
			state = WithdrawnNormalState;
		}
	}
	return state;
}

void
VkSimpleWindow::stateChanged(IconState newState)
{
    _iconState = newState;
}

void
VkSimpleWindow::afterRealizeHook()
{
    //  do nothing.  let the user override.
}

void
VkSimpleWindow::setTitle(const char *newTitle)
{
	// Check if the string names a resource ...
	char* title = (char*)VkGetResource(_baseWidget, newTitle, "Title",
									   XmRString, newTitle);

	if (title != 0) {
		delete [] _windowTitle;
		_windowTitle = new char[strlen(title) + 1];
		strcpy(_windowTitle, title);

		// Make sure the widget has a window to set the property
		// (if not the proerty will be set in setUpWindowProperties)
		if (XtIsRealized(_baseWidget)) {
			XTextProperty wm_name;
			XStringListToTextProperty(&_windowTitle, 1, &wm_name);

			XSetWMName(XtDisplayOfObject(_baseWidget),
					   XtWindow(_baseWidget), &wm_name);

			XFree(wm_name.value);
		}
	}
}

const char*
VkSimpleWindow::getTitle()
{
    return _windowTitle;
}

void
VkSimpleWindow::setIconName(const char *newName)
{
	// Check if the string names a resource ...
	char* name  = (char*)VkGetResource(_baseWidget, newName, "Title",
									   XmRString, newName);

	if (name != 0) {
		delete []_iconName;
		_iconName = new char[strlen(name) + 1];
		strcpy(_iconName, name);

		// Make sure the widget has a window to set the property
		// (if not the proerty will be set in setUpWindowProperties)
		if (XtIsRealized(_baseWidget)) {
			XTextProperty icon_name;
			XStringListToTextProperty(&_iconName, 1, &icon_name);

			XSetWMIconName(theApplication->display(),
						   XtWindow(_baseWidget),
						   &icon_name);

			XFree(icon_name.value);
		}
	}
}

void
VkSimpleWindow::setIconPixmap(Pixmap pix)
{
    XtVaSetValues(_baseWidget, XtNiconPixmap, pix, NULL);
}

void
VkSimpleWindow::handleWMDeleteMessage()
{
	if (okToQuit()) {
		delete this;
	}
}

void
VkSimpleWindow::handleWMQuitMessage()
{
    theApplication->quitYourself();
}

void
VkSimpleWindow::wm_delete_window(Widget w, XtPointer clientData,
								 XtPointer callData)
{
    VkSimpleWindow *obj = (VkSimpleWindow *)clientData;

    obj->handleWMDeleteMessage();
}

void
VkSimpleWindow::wm_quit_app(Widget w, XtPointer clientData, XtPointer callData)
{
    VkSimpleWindow *obj = (VkSimpleWindow*)clientData;

    obj->handleWMQuitMessage();
}

void
VkSimpleWindow::change_state_handler(Widget w, XtPointer clientData,
									 XEvent *event, Boolean *)
{
    VkSimpleWindow *obj = (VkSimpleWindow*)clientData;

    obj->changeState(event);
}

void
VkSimpleWindow::changeState(XEvent *event)
{
    XCirculateEvent *xcirculate;
    XConfigureEvent *xconfigure;

    switch (event->type) {
    case CirculateNotify:
		xcirculate = (XCirculateEvent*)event;
		if (xcirculate->place == PlaceOnTop)
			_stackingState = RAISED;
		else
			_stackingState = LOWERED;
		break;
    case ConfigureNotify:
		xconfigure = (XConfigureEvent*)event;
		if (xconfigure->above == None)
			_stackingState = LOWERED;
		else
			_stackingState = STACKING_UNKNOWN;
		break;
    case MapNotify:
		_iconState = OPEN;
		break;
    case UnmapNotify:
		_iconState = CLOSED;
		break;
    }
}

VkSimpleWindow*
VkSimpleWindow::getWindow(VkComponent* component)
{
    Widget current = component->baseWidget();

	if (current == 0) return 0;

	// Find component's shell parent
    while (!XtIsShell(current)) {
		current = XtParent(current);
	}
    if (XtIsSubclass(current, applicationShellWidgetClass)) {
		// Find the app's window which matches
		VkComponentList cl = *(theApplication->winList());
		for (int i = 0; i < cl.size(); ++i) {
			if (cl[i]->baseWidget() == current) {
				try {
  					VkSimpleWindow* sw = dynamic_cast<VkSimpleWindow*>(cl[i]);
					return sw;
				} catch(exception e) {
					// dynamic_cast will throw an exception if the object
					// is not a VkSimpleWindow or subclass
					cerr << "VkSimpleWindow::getWindow - " << e.what() << endl;
					return 0;
				}
			}
		}
		// No matching window found
		return 0;
    } else {
		return 0;
	}
}

