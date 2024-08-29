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
 * VkComponent.C
 * 
 * This file contains the class implementation of
 * the VkComponent Class.  For all intents and purposes,
 * this class is useless to the end-user, as it is almost
 * completely abstract.
 *
 * Chris Toshok
 * Copyright (C) 1994
 * The Hungry Programmer, Inc
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkComponent.C,v 1.18 2009/03/21 11:44:34 jostle Exp $";

#include <cstdlib>
#include <iostream>
#include <string>

#include <Vk/VkComponent.h>
#include <Vk/VkApp.h>

using namespace std;

const char *const VkComponent::deleteCallback = "VkComponentDeleteCallback";

VkComponent::VkComponent(const char *name)
    : VkCallbackObject(),
	  _name(0),
      _baseWidget(0)
{
    if (name) {
		_name = new char[strlen(name) + 1];
		strcpy(_name, name);
    }
}

VkComponent::~VkComponent()
{
    callCallbacks(VkComponent::deleteCallback, NULL);

	// Make sure the widget has not already been destroyed.
	if (_baseWidget != 0) {
		removeDestroyHandler();

		// XmDropSiteUnregister(_baseWidget);
		
		XtDestroyWidget(_baseWidget);
		_baseWidget = 0;
	}

    delete [] _name;
    _name = 0;
}

void
VkComponent::show()
{
    /* By default, just manage the baseWidget */
    XtManageChild(_baseWidget);
}

void 
VkComponent::hide()
{
    /* By default, just unmanage the baseWidget */
    XtUnmanageChild(_baseWidget);
}

void
VkComponent::installDestroyHandler()
{
    XtAddCallback(_baseWidget, XmNdestroyCallback, widgetDestroyedCallback,
				  (XtPointer)this);

    // Add a map notify callback to trigger the afterRealizeHook() call
    // This seems to be the only place to put the event handler
    // registration ... it just doesn't feel like the right place.
	// The user is _supposed_ to _always_ call installDestroyHandler
	// immediately after creating _baseWidget; but what if they forget?
    // JSL 31/7/00
	// Check that the base widget is not a Gadget!
	// Gadgets do not handle events and trying to add an event handler
	// to a gadget will cause a crash.
	// jostle 29/11/01
	if (XtIsWidget(_baseWidget)) {
		XtAddEventHandler(_baseWidget, StructureNotifyMask, False, mapCB,
						  (XtPointer)this);
	}
}

void
VkComponent::mapCB(Widget w, XtPointer clientData,
				   XEvent* event, Boolean* continueDispatch)
{
	if (event->type == MapNotify) {
		VkComponent* me = (VkComponent*)clientData;
		me->afterRealizeHook();
		// This is a one-shot process so now remove the event handler
		XtRemoveEventHandler(me->_baseWidget, StructureNotifyMask, False,
							 me->mapCB, (XtPointer)me);
	}
}

void
VkComponent::removeDestroyHandler()
{
    XtRemoveAllCallbacks(_baseWidget, XmNdestroyCallback);
}

void
VkComponent::widgetDestroyedCallback(Widget w, XtPointer clientData,
									 XtPointer callData)
{
    VkComponent* me = (VkComponent*)clientData;
	me->widgetDestroyed();
}

void 
VkComponent::widgetDestroyed()
{
	removeDestroyHandler();
    _baseWidget = 0;
}

void
VkComponent::setDefaultResources(const Widget parent,
								 const char* const resourceSpec[])
{
    Display *display = XtDisplay(parent);

    XrmDatabase display_db = XrmGetDatabase(display);

    xrm_db = XrmGetStringDatabase("");

	string tempStr;
    for (int current = 0; resourceSpec[current] != NULL; current ++) {
		if (resourceSpec[current][0] == '-') {
			// If the spec starts with '-' treat it as a global resource
			// by just removing the '-' and do not qualify
			// the spec with the widget name.
			tempStr = &(resourceSpec[current][1]);
			XrmPutLineResource (&xrm_db, tempStr.c_str());
		} else if (resourceSpec[current][0] == '+') {
			// If the spec starts with '+' qualify the spec with the
			// application class name. Useful for overriding resources
			// set by SGI Schemes (or CDE?)
			tempStr = theApplication->applicationClassName();
			tempStr += &(resourceSpec[current][1]);
			XrmPutLineResource (&xrm_db, tempStr.c_str());
		} else {
			tempStr = "*";
			tempStr += _name;
			tempStr += resourceSpec[current];
			XrmPutLineResource (&xrm_db, tempStr.c_str());
		}
    }
    XrmCombineDatabase(xrm_db, &display_db, False);
    XrmSetDatabase(display, display_db);
}

void
VkComponent::getResources(const XtResourceList resources,
						  const int numResources)
{
  if (_baseWidget == NULL) {
    cerr << "_baseWidget NULL inside of getResources" << endl;
    exit(1);
  }
  
  XtGetApplicationResources(_baseWidget,
                            this,
                            resources,
                            numResources,
                            NULL, 0);
}
