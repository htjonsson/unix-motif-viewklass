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
 * VkCheckBox.C
 *
 * This file contains the class implementation for the
 * VkCheckBox class, which allows programmers to
 * create groups of check-box type toggle buttons
 * with a title and frame surrounding them.
 *
 * Copyright (C) 1994
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: VkCheckBox.C,v 1.12 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkCheckBox.h>
#include <Xm/LabelG.h>
#include <Xm/ToggleB.h>
#include <Xm/Frame.h>
#include <Xm/RowColumn.h>

using namespace std;

VkCheckBox::VkCheckBox(const char *name, Widget parent)
	: VkComponent(name)
{
    _baseWidget = XmCreateFrame(parent, (char*)name, NULL, 0);

    installDestroyHandler();

    _label = XtVaCreateManagedWidget(
		"label", xmLabelGadgetClass, _baseWidget,
		XmNchildType, XmFRAME_TITLE_CHILD,
		XmNchildVerticalAlignment, XmALIGNMENT_CENTER,
		NULL);

    _rc = XtVaCreateManagedWidget(
		"rc", xmRowColumnWidgetClass, _baseWidget,
		XmNchildType, XmFRAME_WORKAREA_CHILD,
		NULL);

    _widgetList = new VkWidgetList();
}

VkCheckBox::~VkCheckBox()
{
	delete _widgetList;
}

Widget 
VkCheckBox::addItem(char *name, Boolean state,
                    XtCallbackProc proc, XtPointer clientData)
{
    Widget newItem;  
  
    newItem = XtVaCreateManagedWidget(
		name, xmToggleButtonWidgetClass, _rc,
		NULL);

    XmToggleButtonSetState(newItem, state, False);

    if (proc) {
        XtAddCallback(newItem, XmNvalueChangedCallback,
					  proc, this);
	}
    _widgetList->add(newItem);

    XtAddCallback(newItem, XmNvalueChangedCallback,
				  valueChangedCallback, this);
    return newItem;
}

void 
VkCheckBox::setValue(int indx, Boolean newValue)
{
    if (indx < _widgetList->size()) {
        XmToggleButtonSetState((*_widgetList)[indx], newValue, False);
	}
}

void 
VkCheckBox::setValues(Boolean *values, int numValues)
{
	for (int i = 0; i < numValues; i++) {
		if (i < _widgetList->size()) {
			XmToggleButtonSetState((*_widgetList)[i], values[i], False);
		}
	}
}

int 
VkCheckBox::getValue(int i)
{
    if (i < _widgetList->size()) {
		return XmToggleButtonGetState((*_widgetList)[i]);
    } else {
		return -1;
	}
}

void 
VkCheckBox::valueChanged(int indx, Boolean set)
{
    callCallbacks(VkCheckBox::itemChangedCallback, (void*)indx);
}

void
VkCheckBox::valueChangedCallback(Widget w, XtPointer clientData,
                                 XtPointer callData)
{
    VkCheckBox* obj = (VkCheckBox* )clientData;
    XmToggleButtonCallbackStruct* cb =
		(XmToggleButtonCallbackStruct*)callData;
	for (int indx = 0; indx < obj->_widgetList->size(); ++indx) {
		if ((*obj->_widgetList)[indx] == w) {
			obj->valueChanged(indx, cb->set);
			break;
		}
	}
}

const char *const
VkCheckBox::itemChangedCallback = "VkCheckBox::itemChangedCallback";
