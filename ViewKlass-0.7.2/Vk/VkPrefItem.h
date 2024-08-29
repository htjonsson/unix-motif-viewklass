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
 * $Id: VkPrefItem.h,v 1.5 2006/02/13 07:23:27 jostle Exp $
 *
 * This file contains the class definition for
 * VkPrefItem, which forms the base class for
 * all items which are allowable inside of preference
 * dialogs.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKPREFITEM_H
#define VKPREFITEM_H

#include <assert.h>

#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>

#include <string>

class VkPrefItem : public VkComponent {
public:
    enum VkPrefItemType {PI_group, PI_list, PI_radio, PI_text, PI_toggle,
			 PI_option, PI_empty, PI_label, PI_separator,
			 PI_custom, PI_none};

    VkPrefItem(const char* name);
    virtual ~VkPrefItem();

    virtual Boolean changed() { return _changed; }

	// Set the item's baseWidget's sensitivity
    virtual void activate();
    virtual void deactivate();

	// Get the item's components' heights
	virtual Dimension labelHeight();
	virtual Dimension baseHeight();

	// Set the item's components' heights
    virtual void setLabelHeight(Dimension h);
    virtual void setBaseHeight(Dimension h);

    Widget labelWidget() { return _labelWidget; }

	virtual VkPrefItemType type() = 0;

    virtual Boolean isContainer() = 0;

    virtual const char* className() = 0;

    virtual void instantiate(Widget parent) = 0;

	// Mentioned in VkPrefDialog man page.
	// Copy value from our widget to our internal value.
	// Default behaviour is to do nothing.
	virtual void updateValue() {};

	// Not mentioned anywhere but surely we need this for the
	// cancel operation.
	// Copy our internal value to our widget.
	virtual void resetValue() {};
	
	virtual Widget buildLabel();

	// Implement for containers
	virtual void deleteChildren() { return; }
	virtual Boolean hasChildren() { return false; }

protected:

  	void setHeight(Dimension h);
  	Dimension getHeight();

	Widget _labelWidget;
	std::string _baseName;
	std::string _labelName;

	bool _changed;

	bool _activated;
	bool _homogeneous;

    bool _instantiated;

#undef NDEBUG
	bool _NotYetImplemented;
	void installDestroyHandlers() { assert((_NotYetImplemented == false)); }
};

#endif // VKPREFITEM_H
