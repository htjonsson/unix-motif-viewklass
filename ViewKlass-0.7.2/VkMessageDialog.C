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

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: VkMessageDialog.C,v 1.2 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkMessageDialog.h>
#include <Vk/VkApp.h>
#include <string.h>

VkMessageDialog::VkMessageDialog(const char *name)
	: VkDialogManager(name)
{
	_dialogShellTitle = NULL;
	_showOK = True;
	_showHelp = False;
	_showCancel = False;
}

Widget
VkMessageDialog::createDialog(Widget parent)
{
	return(XmCreateMessageDialog(parent, (char*)_name, NULL, 0));
}

VkMessageDialog* theMessageDialogInstance()
{
	static VkMessageDialog* instance = 0;
	if (instance == 0) {
		instance = new VkMessageDialog("Message");
	}
	return instance;
}
