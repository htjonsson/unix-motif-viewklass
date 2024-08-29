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
 * $Id: VkCompletionField.h,v 1.3 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the class definition for
 * VkCompletionField, which forms the base class for
 * all items which are allowable inside of preference
 * dialogs.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKCOMPLETIONFIELD_H
#define VKCOMPLETIONFIELD_H

#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>

class VkNameList;

class VkCompletionField : public VkComponent {
public:
    VkCompletionField(const char* name, Widget parent);
    virtual ~VkCompletionField();

	void add(const char* name);
	void clear();

	const char* getText();

    virtual const char* className() { return "VkCompletionField"; }

	static const char* const enterCallback;

protected:
	virtual void expand(XmTextVerifyCallbackStruct* cbs);
    virtual void activate(XmTextVerifyCallbackStruct* cbs);

	VkNameList* _currentMatchList;
	VkNameList* _nameList;

private:
	static const char* const _defaultResources[];

	static void activateCallback(Widget w, XtPointer clientData,
								 XtPointer callData);

	static void modifyCallback(Widget w, XtPointer clientData,
							   XtPointer callData);

};

#endif // VKCOMPLETIONFIELD_H
