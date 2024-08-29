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

    Copyright (C) 2001 Hordur Thor Jonsson
    hordur@addr.com
*****************************************************************/

/**
 *
 * VkAlignmentGroup.C
 *
 * This file contains the class implementation for the
 * VkAlignmentGroup class.
 *
 * Hordur Thor Jonsson
 * Copyright (C) 2001
 *
 **/

#include <iostream>

using namespace std;

#include <Xm/Label.h>
#include <Xm/LabelG.h>

#include <Vk/VkAlignmentGroup.h>

VkAlignmentGroup::VkAlignmentGroup()
	: VkWidgetList(),
	  _maxWidth(0),
	  _maxHeight(0),
	  _x(0),
	  _y(0),
	  _maxTop(0),
	  _maxBottom(0),
	  _maxLeft(0),
	  _maxRight(0)
{
	// Nothing yet...
}

VkAlignmentGroup::~VkAlignmentGroup()
{
	for (unsigned int i = 0; i < _initialGeometry.size(); ++i) {
		delete _initialGeometry[i];
	}
}

void
VkAlignmentGroup::add(Widget w)
{
	XtWidgetGeometry* initial = new XtWidgetGeometry();

	XtQueryGeometry(w, NULL, initial);

	// Remember the widget's initial preferred geometry
	_initialGeometry.push_back(initial);

	// Update the group's extents
	if (_x > initial->x)
		_x = initial->x;

	if (_y > initial->y)
		_y = initial->y;

	if (_maxWidth < initial->width)
		_maxWidth = initial->width;

	if (_maxHeight < initial->height)
		_maxHeight = initial->height;

	if (_maxTop < initial->y)
		_maxTop = initial->y;

	if (_maxBottom < initial->y + initial->height)
		_maxBottom = initial->y + initial->height;

	if (_maxLeft < initial->x)
		_maxLeft = initial->x;

	if (_maxRight < initial->x + initial->width)
		_maxRight = initial->x + initial->width;

	// Let us control the size of label widgets.
	if (XmIsLabel(w)) {
		XtVaSetValues(w, XmNrecomputeSize, false, NULL);
	}
	
	VkWidgetList::add(w);
}

void
VkAlignmentGroup::add(VkComponent* c)
{
	add(c->baseWidget());
}

void
VkAlignmentGroup::add(VkOptionMenu* menu)
{
	// According to the man page;
	// "Adds ... all the entries in a VkOptionMenu pane
	//  to the group of widgets."
	// I wonder if this is what they mean?
	for (int i = 0; i < menu->numItems(); ++i) {
		add((*menu)[i]->baseWidget());
	}
}

void
VkAlignmentGroup::QueryGeometry()
{
	XtWidgetGeometry current;

	// Initialize all sizes
	_x = _y = 0x7fff;
	_maxWidth = _maxHeight = 0;
	_maxTop = _maxBottom = _maxLeft = _maxRight = 0;
	// Walk though all the widgets
	for (unsigned int i = 0; i < _items.size(); i++) {
		XtQueryGeometry(_items[i], NULL, &current);

		// Update the group's extents
		if (_x > current.x)
			_x = current.x;

		if (_y > current.y)
			_y = current.y;

		if (_maxWidth < current.width)
			_maxWidth = current.width;

		if (_maxHeight < current.height)
			_maxHeight = current.height;

		if (_maxTop < current.y)
			_maxTop = current.y;

		if (_maxBottom < current.y + current.height)
			_maxBottom = current.y + current.height;

		if (_maxLeft < current.x)
			_maxLeft = current.x;

		if (_maxRight < current.x + current.width)
			_maxRight = current.x + current.width;
	}
}

void
VkAlignmentGroup::alignLeft()
{
	QueryGeometry();

	for (int i = 0; i < size(); i++) {
		XtVaSetValues(_items[i], XmNx, _maxLeft, NULL);
	}
	
	QueryGeometry();
}

void
VkAlignmentGroup::alignRight()
{
	QueryGeometry();

	for (int i = 0; i < size(); i++) {
		Widget w = _items[i];
		XtWidgetGeometry geom;
		XtQueryGeometry(w, NULL, &geom);
		Position x = _maxRight - geom.width;
		XtVaSetValues(w, XmNx, x, NULL);
	}
	
	QueryGeometry();
}

void
VkAlignmentGroup::alignTop()
{
	QueryGeometry();

	for (unsigned int i = 0; i < _items.size(); i++) {
		XtVaSetValues(_items[i], XmNy, _maxTop, NULL);
	}
	
	QueryGeometry();
}

void
VkAlignmentGroup::alignBottom()
{
	QueryGeometry();

	for (int i = 0; i < size(); i++) {
		Widget w = _items[i];
		XtWidgetGeometry geom;
		XtQueryGeometry(w, NULL, &geom);
		Position y = _maxBottom - geom.height;
		XtVaSetValues(w, XmNy, y, NULL);
	}
	
	QueryGeometry();
}

void
VkAlignmentGroup::alignWidth()
{
	QueryGeometry();

	for (unsigned int i = 0; i < _items.size(); i++) {
		XtVaSetValues(_items[i], XmNwidth, _maxWidth, NULL);
	}
	
	QueryGeometry();
}

void
VkAlignmentGroup::alignHeight()
{
	QueryGeometry();

	for (unsigned int i = 0; i < _items.size(); i++) {
		XtVaSetValues(_items[i], XmNheight, _maxHeight, NULL);
	}
	
	QueryGeometry();
}

void
VkAlignmentGroup::makeNormal()
{
	for (unsigned int i = 0; i < _items.size(); i++) {
		Widget w = _items[i];
		XtWidgetGeometry* initial = _initialGeometry[i];

		XtVaSetValues(w,
					  XmNx,		initial->x,
					  XmNy,		initial->y,
					  XmNwidth,	initial->width,
					  XmNheight,	initial->height,
					  NULL);
	}
	
	QueryGeometry();
}

ostream& operator<<(ostream& os, VkAlignmentGroup& me)
{
	os << me.className() << " : "
	   << " x, y, w, h = " << me._x << ", " << me._y << ", "
	   << me._maxWidth << ", " << me._maxHeight << ", " << endl
	   << " t, b, l, r = " << me._maxTop << ", " << me._maxBottom << ", "
	   << me._maxLeft << ", " << me._maxRight << ", " << endl;

	for (unsigned int i = 0; i < me._items.size(); i++) {
		XtWidgetGeometry geom;
		XtQueryGeometry(me._items[i], NULL, &geom);
		os << "current : "
		   << " x, y, w, h = " << geom.x << ", " << geom.y << ", "
		   << geom.width << ", " << geom.height << ", " << endl;
			
		XtWidgetGeometry* init = me._initialGeometry[i];
		os << "initial : "
		   << " x, y, w, h = " << init->x << ", " << init->y << ", "
		   << init->width << ", " << init->height << ", " << endl;
	}
	return os;
}

void
VkAlignmentGroup::distributeVertical()
{
	QueryGeometry();

	Dimension totalHeight = 0;
	int spacing;
	for (int i = 0; i < size(); i++) {
		Widget w = _items[i];
		XtWidgetGeometry geom;
		XtQueryGeometry(w, NULL, &geom);
		totalHeight += geom.height;
	}
	spacing = (_maxBottom - _y - totalHeight) / (size() - 1);
	
	Position y = _y;
	for (int i = 0; i < size(); i++) {
		Widget w = _items[i];
		XtWidgetGeometry geom;
		XtQueryGeometry(w, NULL, &geom);

		XtVaSetValues(w, XmNy, y, NULL);
		y += geom.height + spacing;
	}
	
	QueryGeometry();
}

void
VkAlignmentGroup::distributeHorizontal()
{
	QueryGeometry();

	Dimension totalWidth = 0;
	int spacing;
	for (int i = 0; i < size(); i++) {
		Widget w = _items[i];
		XtWidgetGeometry geom;
		XtQueryGeometry(w, NULL, &geom);
		totalWidth += geom.width;
	}
	spacing = (_maxRight - _x - totalWidth) / (size() - 1);
	
	Position x = _x;
	for (int i = 0; i < size(); i++) {
		Widget w = _items[i];
		XtWidgetGeometry geom;
		XtQueryGeometry(w, NULL, &geom);

		XtVaSetValues(w, XmNx, x, NULL);
		x += geom.width + spacing;
	}
	
	QueryGeometry();
}

