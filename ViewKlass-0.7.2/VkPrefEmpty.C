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
 * VkPrefEmpty.h
 *
 * This file contains the class implementation for 
 * VkPrefEmpty, the class which allows the programmer 
 * to define empty space in preference dialogs.
 *
 * Copyright (C) 2001
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPrefEmpty.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkPrefEmpty.h>

using namespace std;

VkPrefEmpty::VkPrefEmpty(const char *name)
	: VkPrefCustom(name)
{
	// Empty
}

void
VkPrefEmpty::instantiate(Widget parent)
{
	VkPrefCustom::instantiate(parent);
	if (_labelWidget) {
      XmString xmstr = XmStringCreateLocalized(const_cast<char*>(""));
		XtVaSetValues(_labelWidget,
					  XmNlabelString, xmstr,
					  NULL);
		XmStringFree(xmstr);
	}
}
