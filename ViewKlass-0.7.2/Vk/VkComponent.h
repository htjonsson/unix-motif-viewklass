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
 * $Id: VkComponent.h,v 1.8 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the class definition for the 
 * VkComponent class.  This class is an abstract one,
 * meaning it doesn't make any sense to define an object
 * as a VkComponent.  It _does_ make sense to derive objects
 * from it.  It is derived from the VkCallbackObject class,
 * which allows any components to receive and register 
 * callbacks.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKCOMPONENT_H
#define VKCOMPONENT_H

#include <Xm/Xm.h>
#include <X11/Xresource.h>
#include <X11/Intrinsic.h>
#include <string.h>
#include <Vk/VkConfig.h>
#include <Vk/VkCallbackObject.h>

class VkComponent : public VkCallbackObject {
 public:
    virtual ~VkComponent();
    Widget baseWidget() const { return _baseWidget; } 
    const char* name() const { return _name; }

    void installDestroyHandler(); 
    void removeDestroyHandler(); 
    void setDefaultResources(const Widget parent,
							 const char* const resourceSpec[]);
  
    void getResources (const XtResourceList resources,
					   const int numResources);
  
    virtual operator Widget() const { return _baseWidget; }
    virtual const char* className() { return "VkComponent"; }
    virtual void show(); 
    virtual void hide();
	void manage() { show(); };
	void unmanage() { hide(); };
    virtual void widgetDestroyed(); 
    virtual Boolean okToQuit() { return TRUE; } 
//  static Boolean isComponent(VkComponent* component);  I don't know if this will work, or even if it's necessary

    static const char* const deleteCallback;

 protected:
    char* _name;
    Widget _baseWidget;
    VkComponent(const char* name); 
    virtual void afterRealizeHook() {};

 private:
    static void widgetDestroyedCallback(Widget w, XtPointer clientData,
										XtPointer callData);
	static void mapCB(Widget w, XtPointer clientData,
					  XEvent* event, Boolean* continueDispatch);
    XrmDatabase xrm_db;

};

typedef struct {
    void *client_data;
    void *obj;
} VkCallbackStruct;

#endif /* VKCOMPONENT_H */
