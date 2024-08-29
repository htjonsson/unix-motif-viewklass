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
 * $Id: VkCheckBox.h,v 1.7 2006/12/23 05:11:33 jostle Exp $
 *
 * This file contains the class declaration for the
 * VkCheckBox class, which allows programmers to
 * create groups of check-box type toggle buttons
 * with a title and frame surrounding them.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKCHECKBOX_H
#define VKCHECKBOX_H

#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>
#include <Vk/VkWidgetList.h>

class VkCheckBox : public VkComponent {
public:
    VkCheckBox(const char* name, Widget parent);
	virtual ~VkCheckBox();

    Widget addItem(char* name, 
		   Boolean state = FALSE,
		   XtCallbackProc proc = NULL,
		   XtPointer clientData = NULL);

    void setValue(int indx, Boolean newValue);
    void setValues(Boolean* values, int numValues);

    int getValue(int indx);

    static const char* const itemChangedCallback;
    
    virtual const char* className() { return "VkCheckBox"; }

protected:
    VkWidgetList* _widgetList;
    Widget _rc;
    Widget _label;

    virtual void valueChanged(int indx, Boolean newValue);

private:
    static void valueChangedCallback(Widget w, XtPointer clientData,
									 XtPointer callData);
};

#endif // VKCHECKBOX_H
