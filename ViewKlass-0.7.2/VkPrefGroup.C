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
 * VkPrefGroup.C
 *
 * This file contains the implementation for
 * the preference item grouper class.
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
= "$Id: VkPrefGroup.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

#include <Vk/VkPrefGroup.h>

using namespace std;

VkPrefGroup::VkPrefGroup(const char *name,
						 Boolean horizOrientation,
						 Boolean noLabel)
	: VkPrefItem(name),
	  _horizOrientation(horizOrientation),
	  _noLabel(noLabel),
	  _maxLabelWidth(0),
	  _maxHeight(0),
	  _firstType(PI_none)
{
	// Empty
}

VkPrefGroup::~VkPrefGroup()
{
	deleteChildren();
}

void
VkPrefGroup::addItem(VkPrefItem *item)
{
	_items.add(item);

	// Work out whether the group is homogeneous.
	if (_firstType == PI_none) _firstType = item->type();
	if (item->type() != _firstType) _homogeneous = false;
		
}

VkPrefItem *
VkPrefGroup::item(int item)
{
	return (VkPrefItem*)(_items[item]);
}

int
VkPrefGroup::size()
{
	return _items.size();
}

void
VkPrefGroup::deleteChildren()
{
	// Delete all our pref items
	for (int i = _items.size() - 1; i>= 0; --i) {
		VkPrefItem* pi = ((VkPrefItem*)_items[i]);
		delete pi;
		_items.remove(i);
	}
}

Boolean
VkPrefGroup::changed()
{
	for (int i = 0; i < _items.size(); ++i) {
		VkPrefItem* pi = ((VkPrefItem*)_items[i]);
		if (pi->changed()) return true;
	}
	return false;
}

void
VkPrefGroup::activate()
{
	for (int i = 0; i < _items.size(); ++i) {
		VkPrefItem* pi = ((VkPrefItem*)_items[i]);
		pi->activate();
	}
}

void
VkPrefGroup::deactivate()
{
	for (int i = 0; i < _items.size(); ++i) {
		VkPrefItem* pi = ((VkPrefItem*)_items[i]);
		pi->deactivate();
	}
}

void
VkPrefGroup::instantiate(Widget parent)
{
	_baseWidget = XtVaCreateManagedWidget(
		_name, xmRowColumnWidgetClass, parent,
		XmNorientation, _horizOrientation ? XmHORIZONTAL : XmVERTICAL,
		XmNpacking, XmPACK_TIGHT,
		XmNadjustLast, False,
		NULL);

	installDestroyHandler();

	// Create all our pref items
	for (int i = 0; i < _items.size(); ++i) {
		VkPrefItem* pi = (VkPrefItem*)_items[i];

		switch(pi->type()) {
		case PI_custom:
		case PI_group:
		case PI_option:
		case PI_radio:
		case PI_text:
		case PI_toggle:
		{
			Widget itemForm = XtVaCreateManagedWidget(
				"itemform", xmFormWidgetClass, _baseWidget,
				NULL);
			pi->instantiate(itemForm);
			if ((pi->type() == PI_toggle && !_homogeneous) ||
				(!_horizOrientation)) {
				pi->buildLabel();
			}
			if (pi->isContainer()) {
				if (pi->labelWidget()) {
					XtVaSetValues(pi->labelWidget(),
								  XmNtopAttachment, XmATTACH_FORM,
								  XmNbottomAttachment, XmATTACH_NONE,
								  XmNleftAttachment, XmATTACH_FORM,
								  XmNrightAttachment, XmATTACH_FORM,
								  NULL);
					XtVaSetValues(pi->baseWidget(),
								  XmNtopAttachment, XmATTACH_WIDGET,
								  XmNtopWidget, pi->labelWidget(),
								  XmNbottomAttachment, XmATTACH_FORM,
								  XmNleftAttachment, XmATTACH_FORM,
								  XmNrightAttachment, XmATTACH_FORM,
								  NULL);
				} else {
					XtVaSetValues(pi->baseWidget(),
								  XmNtopAttachment, XmATTACH_FORM,
								  XmNbottomAttachment, XmATTACH_FORM,
								  XmNleftAttachment, XmATTACH_FORM,
								  XmNrightAttachment, XmATTACH_FORM,
								  NULL);
				}
			} else {
				if (pi->labelWidget()) {
					Dimension labelWidth;
					XtVaGetValues(pi->labelWidget(),
								  XmNwidth, &labelWidth, NULL);
					_maxLabelWidth = std::max(labelWidth, _maxLabelWidth);
					XtVaSetValues(pi->labelWidget(),
								  XmNtopAttachment, XmATTACH_FORM,
								  XmNbottomAttachment, XmATTACH_FORM,
								  XmNleftAttachment, XmATTACH_FORM,
								  XmNrightAttachment, XmATTACH_NONE,
								  NULL);
				}

				XtVaSetValues(pi->baseWidget(),
							  XmNtopAttachment, XmATTACH_FORM,
							  XmNbottomAttachment, XmATTACH_FORM,
							  XmNleftAttachment, XmATTACH_FORM,
							  XmNrightAttachment, XmATTACH_FORM,
							  NULL);
			}
			break;
		}
		case PI_empty:
		case PI_separator:
		case PI_label:
		case PI_list:
		default:			
			pi->instantiate(_baseWidget);
		}
	}

	for (int i = 0; i < _items.size(); ++i) {
		VkPrefItem* pi  =  (VkPrefItem*)_items[i];

		if (!pi->isContainer()) {
			if (pi->labelWidget()) {
				XtVaSetValues(pi->baseWidget(),
							  XmNrightAttachment, XmATTACH_NONE,
							  XmNleftOffset, _maxLabelWidth,
							  NULL);
			} else {
				XtVaSetValues(pi->baseWidget(),
							  XmNrightAttachment, XmATTACH_NONE,
							  NULL);
			}
		}
	}
}

Widget
VkPrefGroup::buildLabel()
{
	Widget w = 0;
	if (!_noLabel) {
		w = VkPrefItem::buildLabel();
	}
	return w;
}
