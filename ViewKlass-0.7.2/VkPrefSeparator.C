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
 * VkPrefSeparator.h
 *
 * This file contains the class implementation for 
 * VkPrefSeparator, the class which allows the programmer 
 * to define separator widgets in preference dialogs.
 *
 *
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkPrefSeparator.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkPrefSeparator.h>

using namespace std;

VkPrefSeparator::VkPrefSeparator(const char *name)
	: VkPrefItem(name)
{
	// Empty
}

void
VkPrefSeparator::instantiate(Widget parent)
{
	_baseWidget = XtVaCreateManagedWidget(
		_baseName.c_str(), xmSeparatorWidgetClass, parent,
		NULL);

	installDestroyHandler();
}
