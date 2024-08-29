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
 * $Id: VkPrefText.h,v 1.5 2006/02/13 07:23:27 jostle Exp $
 *
 * This file contains the class definition for VkPrefText,
 * the class which allows the programmer to define 
 * text field widgets in preference dialogs.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKPREFTEXT_H
#define VKPREFTEXT_H

#include <string>

#include <Xm/TextF.h>
#include <Vk/VkConfig.h>
#include <Vk/VkPrefItem.h>

class VkPrefText : public VkPrefItem {
public:

    VkPrefText(const char *name, int columns = 5);
	virtual ~VkPrefText();
	
	Boolean changed();
    const char *getValue();
    void setValue(const char *str);
    
    VkPrefItemType type() { return PI_text; }
    Boolean isContainer() { return False; }
    virtual const char *className() { return "VkPrefText"; }

private:
    std::string _value;
	int _columns;

	void instantiate(Widget parent);
};
 
#endif // VKPREFTEXT_H
