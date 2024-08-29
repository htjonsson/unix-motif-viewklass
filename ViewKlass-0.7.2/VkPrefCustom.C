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
 * VkPrefCustom.h
 *
 * This file contains the class implementation for 
 * VkPrefCustom, the class which allows the programmer 
 * to define custom preference dialogs.
 *
 *
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPrefCustom.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <Xm/Label.h>
#include <Vk/VkPrefCustom.h>

using namespace std;

VkPrefCustom::VkPrefCustom(const char *name)
	: VkPrefItem(name)
{
	// Empty
}

void
VkPrefCustom::instantiate(Widget parent)
{
	_baseWidget = XmCreateWorkArea(
		parent, const_cast<char*>(_baseName.c_str()),
		NULL, 0);

	installDestroyHandler();

	XtManageChild(_baseWidget);
}
