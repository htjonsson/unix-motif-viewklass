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
 * VkPopupMenu.C
 *
 * This file contains the source for the class implementation of the
 * VkPopupMenu class.  This class makes doing popup menus a lot easier.
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
	= "$Id: VkPopupMenu.C,v 1.11 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkPopupMenu.h>

using namespace std;

VkPopupMenu::VkPopupMenu(VkMenuDesc* menuDesc, XtPointer defaultClientData)
	: VkMenu("popupMenu")
{
	createFromMenuDesc(menuDesc, defaultClientData);
}

VkPopupMenu::VkPopupMenu(const char* name, VkMenuDesc* menuDesc,
						 XtPointer defaultClientData)
	: VkMenu(name)
{
	createFromMenuDesc(menuDesc, defaultClientData);
}

VkPopupMenu::VkPopupMenu(Widget parent, VkMenuDesc* menuDesc,
						 XtPointer defaultClientData)
	: VkMenu ("popupMenu")
{
	createFromMenuDesc(menuDesc, defaultClientData);
	attach (parent);
}

VkPopupMenu::VkPopupMenu(Widget parent, const char* name, VkMenuDesc* menuDesc,
						 XtPointer defaultClientData)
	: VkMenu (name)
{
	createFromMenuDesc(menuDesc, defaultClientData);
	attach (parent);  
}

void
VkPopupMenu::attach(Widget w)
{
	if (!_isBuilt) {
	    build(w);
	}
	XtAddEventHandler(w, ButtonPressMask, FALSE, popup, this);
}

void
VkPopupMenu::build(Widget parent)
{
	_baseWidget = XmCreatePopupMenu(parent, (char*)name(), NULL, 0);
	installDestroyHandler();
	for (int i = 0; i < _elements.size(); i++) {		
		((VkMenuItem*)_elements[i])->build(_baseWidget);
	}
	_isBuilt = TRUE;
}

void
VkPopupMenu::show()
{
    VkMenuItem::show();
}

void
VkPopupMenu::show(XEvent* event)
{
	XButtonPressedEvent* e = (XButtonPressedEvent*)event;
	XmMenuPosition(baseWidget(), e);
	XtManageChild(baseWidget());
}

void
VkPopupMenu::popup(Widget w, XtPointer clientData, XEvent* event, Boolean* b)
{
	XButtonPressedEvent* e = (XButtonPressedEvent*)event;
	if (e->button == Button3) {
		((VkPopupMenu*)clientData)->show(event);
	}
}

