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
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 Hordur Thor Jonsson
    hordur@addr.com
*****************************************************************/

#ifndef VKALIGNMENTGROUP_H
#define VKALIGNMENTGROUP_H

#include <Vk/VkWidgetList.h>
#include <Vk/VkOptionMenu.h>

class VkAlignmentGroup : public VkWidgetList {
public:
	// Constructor/Destructor
	VkAlignmentGroup();
	virtual ~VkAlignmentGroup();

	// Adding Items
 	virtual void add(Widget w);
 	virtual void add(VkComponent* c);
 	virtual void add(VkOptionMenu* menu);

	// Aligning Items By Position
	void alignLeft();
	void alignRight();
	void alignTop();
	void alignBottom();

	// Aligning Sizes
	void alignWidth();
	void alignHeight();

	// Reset widgets to their original size and position
	void makeNormal();

	// Controlling Spacing
	void distributeVertical();
	void distributeHorizontal();

	// Access Functions
	Dimension 	width() { return _maxWidth; }
	Dimension 	height() { return _maxHeight; }
	Position 	x() { return _x; }
	Position 	y() { return _y; }

	const char* className() { return "VkAlignmentGroup"; }

	friend std::ostream& operator<<(std::ostream& os, VkAlignmentGroup& me);

protected:
	// Data Members
	Dimension	_maxWidth;
	Dimension	_maxHeight;
	// These are the minimum x & y values as returned by x() & y()
	Position	_x;
	Position	_y;

private:
	void QueryGeometry();

	// These are the positions to which alignments are made
	// The man page states that the "right-most" or "bottom-most"
	// widget determines the position.
	Position	_maxTop;
	Position	_maxBottom;
	Position	_maxLeft;
	Position	_maxRight;

	std::vector<XtWidgetGeometry*> _initialGeometry;
};

#endif // VKALIGNMENTGROUP_H
