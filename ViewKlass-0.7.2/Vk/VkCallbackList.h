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
 * $Id: VkCallbackList.h,v 1.5 2003/12/13 02:17:38 jostle Exp $
 *
 * This file contains the class declaration for callback
 * lists, which is an internally used class that helps
 * clear up the VkCallbackObject class code.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc. 
 * All Rights Reserved
 *
 **/

#ifndef VKCALLBACKLIST_H
#define VKCALLBACKLIST_H

#include <vector>
#include <string>

#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>
#include <Vk/VkCallbackObject.h>

struct VkCallbackListEntry {
    enum CallbackType type;
    VkCallbackObject *component;
    VkCallbackFunction callbackFunction;
    VkCallbackMethod callbackMemberFunction;
    void *clientData;
};

class VkCallbackList {
public:
    VkCallbackList(const char *name);
    virtual ~VkCallbackList();

    void addMemberFunction(VkCallbackObject *component,
						   VkCallbackMethod callbackMember,
						   void *clientData);

    
    void removeMemberFunction(VkCallbackObject *otherObject,
							  VkCallbackMethod memberFunction,
							  void *clientData);

    void addCStyleFunction(VkCallbackFunction callbackFunction,
						   void *clientData);

    void removeCStyleFunction(VkCallbackFunction callbackFunction,
							  void *clientData);

    void removeAllMethods(VkCallbackObject *fromObj);

    void removeAll();

    void call(VkCallbackObject *caller, void *callData);

    const char *name() const { return _name.c_str();};

    int number() { return _callbacks.size(); }

private:
    string _name;

    vector<VkCallbackListEntry> _callbacks;
};

#endif // VKCALLBACKLIST_H
