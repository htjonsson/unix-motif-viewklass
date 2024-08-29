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

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

/**
 *
 * VkMenuLabel.C
 *
 * 
 * This file contains the source code for the implementation of the
 * (rather boring) VkMenuLabel class, which give the programmer
 * the ability to place (rather boring) labels within menus.
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
	= "$Id: VkMenuLabel.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkMenuItem.h>

using namespace std;

VkMenuLabel::VkMenuLabel(const char *name)
	: VkMenuItem (name)
{
	// empty.
}

void
VkMenuLabel::build(Widget parent)
{
	Arg args[4];
	int n = 0;

	short pos = _position == -1 ? XmLAST_POSITION : _position;
	XtSetArg(args[n], XmNpositionIndex, pos); ++n;

	_baseWidget = XmCreateLabelGadget(parent, (char *)name(), args, n);

	installDestroyHandler();

	XtManageChild(_baseWidget);

	XtSetSensitive(_baseWidget, _sensitive);
	
	_isBuilt = TRUE;
}
