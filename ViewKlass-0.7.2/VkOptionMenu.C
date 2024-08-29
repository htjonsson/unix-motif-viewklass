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
 * VkOptionMenu.C
 *
 * This file contains the implementation for the VkOptionMenu class.
 * This class makes it easier to deal with option menus.  However, since
 * I haven't actually played around with the real ViewKit, I have no idea
 * what they look like.  ho hum :)
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
= "$Id: VkOptionMenu.C,v 1.13 2009/03/21 11:44:34 jostle Exp $";

#include <string>

using namespace std;

#include <Vk/VkOptionMenu.h>

VkOptionMenu::VkOptionMenu(VkMenuDesc* menuDesc,
						   XtPointer defaultClientData)
	: VkMenu ("optionMenu")
{
	createFromMenuDesc(menuDesc, defaultClientData);
}

VkOptionMenu::VkOptionMenu(const char* name,
						   VkMenuDesc* menuDesc,
						   XtPointer defaultClientData)
	: VkMenu (name)
{
	createFromMenuDesc(menuDesc, defaultClientData);
}

VkOptionMenu::VkOptionMenu(Widget parent,
						   VkMenuDesc* menuDesc,
						   XtPointer defaultClientData)
	: VkMenu ("optionMenu")
{
	createFromMenuDesc(menuDesc, defaultClientData);
	build(parent);
}

VkOptionMenu::VkOptionMenu(Widget parent,
						   const char* name,
						   VkMenuDesc* menuDesc,
						   XtPointer defaultClientData)
	: VkMenu (name)
{
	createFromMenuDesc(menuDesc, defaultClientData);
	build(parent);
}

void
VkOptionMenu::set(char* name)
{
	VkMenuItem* result;
	result = findNamedItem(name);
	XtVaSetValues(_baseWidget, XmNmenuHistory, result->baseWidget(), NULL);
}

void
VkOptionMenu::set(int indx)
{
	XtVaSetValues(_baseWidget,
				XmNmenuHistory, _elements[indx]->baseWidget(),
				NULL);
}

void
VkOptionMenu::set(VkMenuItem* item)
{
	XtVaSetValues(_baseWidget, XmNmenuHistory, item->baseWidget(), NULL);
}

int
VkOptionMenu::getIndex()
{
	Widget widgetId;
	XtVaGetValues(_baseWidget, XmNmenuHistory, &widgetId, NULL);
	return getItemPosition(widgetId);
}

VkMenuItem* 
VkOptionMenu::getItem()
{
	Widget widgetId;
	XtVaGetValues(_baseWidget, XmNmenuHistory, &widgetId, NULL);
	return (VkMenuItem*)_elements[getItemPosition(widgetId)];
}

void
VkOptionMenu::forceWidth(int /*width*/)
{
}

void
VkOptionMenu::setLabel(const char* str)
{
	Widget label = XmOptionLabelGadget(_baseWidget);
	XmString xmstr = XmStringCreateLocalized((char*)str);
	XtVaSetValues(label, XmNlabelString, xmstr, NULL);  
	XmStringFree(xmstr);
}

void
VkOptionMenu::build(Widget parent)
{
	Arg args[10];
	XmString xmstr;
	int i;

	string str = _name;
	str += "_pulldown";
	_pulldown =
		XmCreatePulldownMenu(parent, const_cast<char*>(str.c_str()), NULL, 0);

	xmstr = XmStringCreateLocalized(const_cast<char*>(""));
	XtSetArg(args[0], XmNsubMenuId, _pulldown);
	XtSetArg(args[1], XmNlabelString, xmstr);
  
	_baseWidget = XmCreateOptionMenu(parent, (char*)name(), args, 2);

	installDestroyHandler();

	for (i = 0; i < _elements.size(); i++)
		((VkMenuItem*)_elements[i])->build(_pulldown);

	XtManageChild(_baseWidget);
 
	XmStringFree(xmstr);
 
	_isBuilt = TRUE;
}

void
VkOptionMenu::show()
{
    // insure that CascadeButtonGadget initial visual is ok
    if(getIndex() < 0 && _elements.size() > 0) {
		XtVaSetValues(_baseWidget,
					  XmNmenuHistory, _elements[0]->baseWidget(),
					  NULL);
    }

    VkMenu::show();
}
