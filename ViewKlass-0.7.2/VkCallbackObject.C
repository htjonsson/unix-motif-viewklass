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
 * VkCallbackObject.C
 * This file defines the class implementation for the
 * VkCallbackObject class, which forms the base class
 * for all of the user interface components in the Open
 * ViewKlass library.
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
= "$Id: VkCallbackObject.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <string>
#include <iostream>

using namespace std;

#include <Vk/VkCallbackObject.h>
#include <Vk/VkCallbackList.h>

VkCallbackObject::VkCallbackObject()
{
}

VkCallbackObject::~VkCallbackObject()
{
	for (unsigned int i = 0; i < _cbLists.size(); ++i) {
		delete _cbLists[i];
	}
}

VkCallbackList*
VkCallbackObject::addNewCallbackList(const char *name)
{
	VkCallbackList* list = new VkCallbackList(name);
    _cbLists.push_back(list);
	return list;
}

void
VkCallbackObject::addCallback(const char *name,
							  VkCallbackObject *component,
							  VkCallbackMethod callbackFunction,
							  void *clientData)
{
    // First we check to see if a callback of this
	// type has been registered before.
	// If not, we create a new callback list for it and then 
	// add the callback.

	VkCallbackList* list = 0;
	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter) {
		if (!strcmp(name, (*iter)->name())) { // we found it
			list = *iter;
		}
    }

    if (list == 0) {
		list = addNewCallbackList(name);
	}

	list->addMemberFunction(component, callbackFunction, clientData);
}

void
VkCallbackObject::removeCallback(const char *name,
								 VkCallbackObject *otherObject,
								 VkCallbackMethod memberFunction,
								 void *clientData)
{
    // First we need to find the callback list named NAME, then we need to
    // locate the object and method within the callback list.  We then
    // pop everything down one.

	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter)
	{
		if (!strcmp(name, (*iter)->name())){ // we found it
			(*iter)->removeMemberFunction(otherObject, memberFunction,
										   clientData);
			return;
		}
    }
}

void
VkCallbackObject::addCallback(const char *name,
							  VkCallbackFunction callbackFunction,
							  void *clientData)
{
    // First we check to see if a callback of this
	// type has been registered before.
	// If not, we create a new callback list for it and then 
	// add the callback.

	VkCallbackList* list = 0;
	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter) {
		if (!strcmp(name, (*iter)->name())) { // we found it
			list = *iter;
		}
    }

    if (list == 0) {
		list = addNewCallbackList(name);
	}

	list->addCStyleFunction(callbackFunction, clientData);
}

void
VkCallbackObject::removeCallback(const char *name,
								 VkCallbackFunction callbackFunction,
								 void *clientData)
{
	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter) {
		if (!strcmp(name, (*iter)->name())){ // we found it
			(*iter)->removeCStyleFunction(callbackFunction,
										   clientData);
			return;
		}
    }
}

void
VkCallbackObject::removeAllCallbacks(void)
{
	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter) {
		(*iter)->removeAll();
    }
}    


void
VkCallbackObject::removeAllCallbacks(VkCallbackObject *obj)
{
	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter) {
		(*iter)->removeAllMethods(obj);
	}
}

void
VkCallbackObject::callCallbacks(const char *const callback, void *callData)
{
	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter) {
		if (*iter == 0) {
			cerr << "VkCallbackObject::callCallbacks iter == 0" << endl;
			continue;
		}
		if (!strcmp((*iter)->name(), callback)) {
			(*iter)->call(this, callData);
		}
	}
}

bool
VkCallbackObject::hasCallbacks(const char *const callback)
{
	bool has = false;
	vector<VkCallbackList*>::iterator iter;
    for (iter = _cbLists.begin(); iter != _cbLists.end(); ++iter) {
		if (!strcmp((*iter)->name(), callback)) {
			if ((*iter)->number() > 0) {
				has = true;
			}
			break;
		}
	}
	return has;
}
