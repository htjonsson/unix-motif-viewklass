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
 * VkCallbackList.C
 *
 * This file contains the class implementation for
 * the VkCallbackList object, which makes the implementation
 * of VkCallbackObject substantially simpler.
 *
 * Chris Toshok
 * Copyright (C) 1994, 1995
 * The Hungry Programmers, Inc.
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkCallbackList.C,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>
#include <string>
#include <set>

using namespace std;

#include <Vk/VkCallbackList.h>

VkCallbackList::VkCallbackList(const char *name)
    : _name(name)
{
}

VkCallbackList::~VkCallbackList()
{
}

void
VkCallbackList::addMemberFunction(VkCallbackObject *component,
				  VkCallbackMethod callbackMember,
				  void *clientData)
{
	VkCallbackListEntry entry;
    entry.type = VKCALLBACKMETHOD;
    entry.callbackFunction = 0;

    entry.component = component;
    entry.callbackMemberFunction = callbackMember;
    entry.clientData = clientData;

	_callbacks.push_back(entry);
}

void
VkCallbackList::addCStyleFunction(VkCallbackFunction callbackFunction,
				  void *clientData)
{
	VkCallbackListEntry entry;
    entry.type = VKCALLBACKFUNCTION;
    entry.callbackMemberFunction = 0;

    entry.callbackFunction = callbackFunction;
    entry.clientData = clientData;

	_callbacks.push_back(entry);
}

void
VkCallbackList::removeMemberFunction(VkCallbackObject *otherObject,
				     VkCallbackMethod memberFunction,
				     void *clientData)
{
    vector<VkCallbackListEntry>::iterator iter;
	for (iter = _callbacks.begin(); iter != _callbacks.end();) {
		if (iter->type == VKCALLBACKMETHOD
			&& iter->component == otherObject
			&& iter->callbackMemberFunction == memberFunction
			&& iter->clientData == clientData) {
			
			iter = _callbacks.erase(iter);
		} else {
		    ++iter;
		}
	}
}

void
VkCallbackList::removeCStyleFunction(VkCallbackFunction callbackFunction,
				     void *clientData)
{
    vector<VkCallbackListEntry>::iterator iter;
	for (iter = _callbacks.begin(); iter != _callbacks.end();) {
		if (iter->type == VKCALLBACKFUNCTION
			&& iter->callbackFunction == callbackFunction
			&& iter->clientData == clientData) {

			iter = _callbacks.erase(iter);
	    } else {
		++iter;
	    }
	}
}

void
VkCallbackList::removeAll()
{
	_callbacks.clear();
}

void
VkCallbackList::removeAllMethods(VkCallbackObject *obj)
{
    vector<VkCallbackListEntry>::iterator iter;
	for (iter = _callbacks.begin(); iter != _callbacks.end();) {
		if (iter->type == VKCALLBACKMETHOD
			&& iter->component == obj) {
			iter = _callbacks.erase(iter);
		} else {
		    ++iter;
		}
	}
}

struct cbCompare {
    bool operator()(const VkCallbackListEntry& a, const VkCallbackListEntry& b)
    {
	return memcmp(&a, &b, sizeof(VkCallbackListEntry)) < 0;
    }
};

void
VkCallbackList::call(VkCallbackObject *caller, void *callData)
{
    // Must be careful here -- removeCallback might be called by the callback,
    // and _callbacks list will change out from under us.
    // It's not sufficient just to make a deep copy of the list and iterate
    // over that, because an early callback in the list can delete items
    // that appear later in the list.
    //
    // This implementation repeatedly goes through the _callbacks list
    // from the beginning, until all callbacks have been issued exactly once.

    set<VkCallbackListEntry, cbCompare> alreadyInvoked;

    int invokeCount;
    do {
	invokeCount = 0;

    vector<VkCallbackListEntry>::iterator iter;
	for (iter = _callbacks.begin(); iter != _callbacks.end(); ++iter) {
	    if(alreadyInvoked.insert(*iter).second) {
		switch(iter->type) {
		case VKCALLBACKFUNCTION:
			(*(iter->callbackFunction))
				(caller,
				 iter->clientData,
				 callData);
			break;
		case VKCALLBACKMETHOD:
			((iter->component)->*
			 (iter->callbackMemberFunction))
				(caller,
				 iter->clientData,
				 callData);
			break;
		default:
			cerr << "VkCallbackList bad type " << iter->type << endl;
			return;
		}
		invokeCount++;
		break; // restart loop!
	    }
	}
    } while(invokeCount > 0);
}
