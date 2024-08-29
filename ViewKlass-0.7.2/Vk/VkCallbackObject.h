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
 * $Id: VkCallbackObject.h,v 1.6 2006/02/13 07:23:27 jostle Exp $
 *
 * This file defines the class structure for the
 * VkCallbackObject class, which forms the base class
 * for all of the user interface components in the
 * ViewKlass library.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKCALLBACKOBJECT_H
#define VKCALLBACKOBJECT_H

#include <vector>

#include <Vk/VkConfig.h>

class VkCallbackObject;

typedef void (VkCallbackObject::*VkCallbackMethod)(
	VkCallbackObject *caller,
	void *clientData,
	void *callData);

typedef void (*VkCallbackFunction)(
	VkCallbackObject *caller,
	void *clientData,
	void *callData);

enum CallbackType {VKCALLBACKFUNCTION = 0,  VKCALLBACKMETHOD};

class VkCallbackList;

class VkCallbackObject {
public:
	virtual ~VkCallbackObject();

	// stuff for use with member functions 
	void addCallback (const char *name,
					  VkCallbackObject *component,
					  VkCallbackMethod callbackFunction,
					  void *clientData = 0);

	void removeCallback (const char *name,
						 VkCallbackObject *otherObject,
						 VkCallbackMethod memberFunction,
						 void *clientData = 0);

	// stuff for use with non-member functions
	void addCallback (const char *name,
					  VkCallbackFunction callbackFunction,
					  void *clientData = 0);

	void removeCallback (const char *name,
						 VkCallbackFunction callbackFunction,
						 void *clientData = 0);

	// stuff for both member and non-member functions

	void removeAllCallbacks(void);
	// remove all callbacks from an object

	void removeAllCallbacks(VkCallbackObject *obj); 
	//removes callbacks registered by obj

	bool hasCallbacks(const char* const callback);

	virtual const char* className() { return "VkCallbackObject"; }

protected:
	VkCallbackObject();
	
	void callCallbacks(const char * const callback, void *callData);

private:
	std::vector<VkCallbackList*> _cbLists;
	std::vector<VkCallbackList*>::iterator _iter;

	VkCallbackList* addNewCallbackList(const char *name);

	// Dynamic loading methods
	// NOT YET IMPLEMENTED
//  	static VkCallbackObject *loadObject(const char *name,
//  										const char *className,
//  										const char *filename);
//  	const VkNameList* getMethods();
//  	const char *getMethodArgType(const char *methodName);
//  	void invokeMethod(const char *method, void *arg);
//  	void invokeMethod(const char *method, int arg);
//  	void invokeMethod(const char *method, Boolean arg);
//  	void invokeMethod(const char *method, const char *arg);
//  	void invokeMethod(const char *method);

};

#define VkAddCallbackFunction(name, otherObject, func, clientData) \
		( (otherObject)->addCallback((name), (func), (clientData)) )

#define VkAddCallbackMethod(name, otherObject, thisObject, func, clientData) \
        ( (otherObject)->addCallback((name), (thisObject), \
		(VkCallbackObject::VkCallbackMethod)(func), (clientData)) )

#define VkRemoveCallbackFunction(name, otherObject, func, clientData) \
        ( (otherObject)->removeCallback((name), (func), (clientData)) )

#define VkRemoveCallbackMethod(name, otherObject, thisObject, func, clientData) \
        ( (otherObject)->removeCallback((name), (thisObject), \
		(VkCallbackObject::VkCallbackMethod)(func), (clientData)) )

#endif /* VKCALLBACKOBJECT_H */
