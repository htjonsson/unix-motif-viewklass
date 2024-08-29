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
 * $Id: VkPrefOption.h,v 1.4 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the definition for preference
 * dialog option menus.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmer, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKPREFOPTION_H
#define VKPREFOPTION_H

#include <Vk/VkConfig.h>
#include <Vk/VkPrefItem.h>

class VkPrefOption : public VkPrefItem {
public:
    VkPrefOption(const char* name, int NumEntries);
	virtual ~VkPrefOption();

    void setOptionLabel(const char* label);

    void setLabel(int indx, const char* label);
    char* getLabel(int indx);
    void setSize(int numEntries);
    int getSize();
    Widget getButton(int indx);
    
	Boolean changed();
    int getValue();
    void setValue(int value);

    void instantiate(Widget parent);

    VkPrefItemType type() { return PI_option; }
    Boolean isContainer() { return False; }
    virtual const char *className() { return "VkPrefOption"; }

 private:
    char** _labels;
    Widget* _buttons;
    char* _labelString;
    int _numOptions;

    int _value;
};

#endif // VKPREFOPTION_H


