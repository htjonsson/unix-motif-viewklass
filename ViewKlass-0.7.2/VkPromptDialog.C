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
 * VkPromptDialog.C
 *
 * This file contains the class implementation for the VkPromptDialog
 * class.
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
	= "$Id: VkPromptDialog.C,v 1.9 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkPromptDialog.h>
#include <string.h>

VkPromptDialog::VkPromptDialog(const char *name)
	: VkDialogManager(name),
	  _text(0),
	  _dialogBox(0)
{
	_dialogShellTitle = NULL;
	_showOK = True;
	_showHelp = False;
	_showCancel = True;
}

VkPromptDialog::~VkPromptDialog()
{
		delete [] _text;
}

Widget
VkPromptDialog::createDialog(Widget parent)
{
	_dialogBox = XmCreatePromptDialog(parent, (char*)_name, NULL, 0);
	return _dialogBox;
}

const char*
VkPromptDialog::text()
{
	XmString xmstr;
	char *text;
	
	XtVaGetValues(_dialogBox, XmNtextString, &xmstr, NULL);
    XmStringGetLtoR(xmstr, XmFONTLIST_DEFAULT_TAG, &text);
	XmStringFree(xmstr);

	delete [] _text;
	_text = new char [strlen(text)+1];
	strcpy( _text, text);
	XtFree (text); /* must free text from XmStringGetLtoR() */

	return _text;
}

void
VkPromptDialog::setText(const char* text)
{
	XmString xmstr = XmStringCreateLocalized(const_cast<char*>(text));
	XtVaSetValues(_dialogBox, XmNtextString, &xmstr, NULL);
	XmStringFree(xmstr);

	delete [] _text;
	_text = new char [strlen(text)+1];
	strcpy(_text, text);
}

VkPromptDialog* thePromptDialogInstance()
{
	static VkPromptDialog* instance = 0;
	if (instance == 0) {
		instance = new VkPromptDialog("Prompt");
	}
	return instance;
}
