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
 * VkProgressDialog.C
 *
 * This file contains the class implementation for the 
 * VkProgressDialog class.
 *
 * Chris Toshok
 * Copyright (C) 1994
 * The Hungry Programmers, Inc
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkProgressDialog.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <string.h>

#include <Xm/Form.h>
#include <Xm/Scale.h>

#include <Vk/VkProgressDialog.h>
#include <Vk/VkApp.h>

VkProgressDialog::VkProgressDialog(const char *name, Boolean showCancel)
	: VkInterruptDialog(name)
{
	_progressScale = 0;
	_dialogShellTitle = 0;
	_showOK = False;
	_showHelp = False;
	_showCancel = showCancel;
	_percentDone = 0;
}

Widget
VkProgressDialog::createDialog(Widget parent)
{
	Widget base = VkInterruptDialog::createDialog(parent);

	_progressScale = XtVaCreateManagedWidget(
		"progress",
		xmScaleWidgetClass, base,
		XmNorientation, XmHORIZONTAL,
		XmNshowValue, True,
		XmNeditable, False,
		NULL);

#if XmVERSION >= 2
	XtVaSetValues(_progressScale, XmNslidingMode, XmTHERMOMETER, NULL);
#endif

	return base;
}

void
VkProgressDialog::setPercentDone(int percent)
{
	_percentDone = percent;
	if (_progressScale != 0) {
		XtVaSetValues(_progressScale, XmNvalue, percent, NULL);
	}
}

VkProgressDialog* theProgressDialogInstance()
{
	static VkProgressDialog* instance = 0;
	if (instance == 0) {
		instance = new VkProgressDialog("Progress");
	}
	return instance;
}
