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
 * VkPrefItem.C
 *
 * This file contains the implementation for
 * the base, abstract class VkPrefItem
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
= "$Id: VkPrefItem.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <Xm/Label.h>
#include <Vk/VkPrefItem.h>

using namespace std;

VkPrefItem::VkPrefItem(const char *name)
	: VkComponent(name),
	  _labelWidget(0),
	  _changed(false),
	  _activated(true),
	  _homogeneous(true),
	  _instantiated(false),
	  _NotYetImplemented(true)
{
	_baseName = name;
	_baseName += "Base";
	_labelName = name;
	_labelName += "Label";
}

VkPrefItem::~VkPrefItem()
{
}

void
VkPrefItem::activate()
{
	if (!_baseWidget) return;
	
    XtSetSensitive(_baseWidget, True);
	_activated = True;
}

void
VkPrefItem::deactivate()
{
	if (!_baseWidget) return;
	
	// Just desensitise the base widget; leave the label readable
    XtSetSensitive(_baseWidget, False);
	_activated = False;
}

void
VkPrefItem::setLabelHeight(Dimension h)
{
	if (!_labelWidget) return;
	
	XtVaSetValues(_labelWidget, XmNheight, h, NULL);
}

void
VkPrefItem::setBaseHeight(Dimension h)
{
	if (!_baseWidget) return;
	
	XtVaSetValues(_baseWidget, XmNheight, h, NULL);
}

Dimension
VkPrefItem::labelHeight()
{
	if (!_labelWidget) return 0;
	
	Dimension h;
	XtVaGetValues(_labelWidget, XmNheight, &h, NULL);
	return h;
}

Dimension
VkPrefItem::baseHeight()
{
	if (!_baseWidget) return 0;
	
	Dimension h;
	XtVaGetValues(_baseWidget, XmNheight, &h, NULL);
	return h;
}

Dimension
VkPrefItem::getHeight()
{
	return std::max(labelHeight(), baseHeight());
}

void
VkPrefItem::setHeight(Dimension h) {
	setBaseHeight(h);
	setLabelHeight(h);
}

Widget
VkPrefItem::buildLabel()
{
	if (!_baseWidget) return 0;
	
	_labelWidget = XtVaCreateManagedWidget(
		_labelName.c_str(), xmLabelWidgetClass, XtParent(_baseWidget),
		NULL);
	return _labelWidget;
}	
