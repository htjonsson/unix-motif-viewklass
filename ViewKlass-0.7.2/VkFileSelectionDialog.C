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
 * VkFileSelectionDialog.C
 *
 * This file contains the class implementation for the
 * VkFileSelectionDialog class.
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
= "$Id: VkFileSelectionDialog.C,v 1.11 2009/03/21 11:44:34 jostle Exp $";

#include <string>
#include <iostream>

using namespace std;

#include <Vk/VkFileSelectionDialog.h>
#include <Vk/VkApp.h>

VkFileSelectionDialog::VkFileSelectionDialog(const char *name)
	: VkDialogManager(name),
	  _directory(0),
	  _pattern(0),
	  _selection(0),
	  _filename(0),
	  _dialogBox(0)
{
	_showOK = True;
	_showCancel = True;
	_showApply = True;

    _dialogShellTitle = NULL;
}

Widget
VkFileSelectionDialog::createDialog(Widget parent)
{
    Arg args[5];
    int n =0;
	XmString dirXmstr = 0;
	XmString patXmstr = 0;
	XmString selXmstr = 0;

    XtSetArg(args[n], XmNdefaultButton, XmDIALOG_APPLY_BUTTON); n++;
    if (_directory) {
		dirXmstr = XmStringCreateLocalized(_directory);
		XtSetArg(args[n], XmNdirectory, dirXmstr); n++;
    }
    if (_pattern) {
		patXmstr = XmStringCreateLocalized(_pattern);
		XtSetArg(args[n], XmNpattern, patXmstr); n++;
    }
    if (_selection) {
		selXmstr = XmStringCreateLocalized(_selection);
		XtSetArg(args[n], XmNdirSpec, selXmstr); n++;
    }

    _dialogBox =
		XmCreateFileSelectionDialog(parent, (char*)_name, args, n);

	if (dirXmstr) XmStringFree(dirXmstr);
	if (patXmstr) XmStringFree(patXmstr);
	if (selXmstr) XmStringFree(selXmstr);

    return _dialogBox;
}

void
VkFileSelectionDialog::setDirectory(const char *directory)
{
    delete []_directory;
    _directory = new char[strlen(directory) + 1];
	strcpy(_directory, directory);
	
    if (_dialogBox) {
		XmString xmstr = XmStringCreateLocalized(_directory);
		XtVaSetValues(_dialogBox, XmNdirectory, xmstr, NULL);
		XmStringFree(xmstr);
    }
}

void
VkFileSelectionDialog::setFilterPattern(const char *pattern)
{
    delete []_pattern;
    _pattern = new char[strlen(pattern) + 1];
	strcpy(_pattern, pattern);

    if (_dialogBox) {
		XmString xmstr = XmStringCreateLocalized(_pattern);
		XtVaSetValues(_dialogBox, XmNpattern, xmstr, NULL);
		XmFileSelectionDoSearch(_dialogBox, xmstr);
		XmStringFree(xmstr);
    }
}

void
VkFileSelectionDialog::setSelection(const char *selection)
{
    delete []_selection;
    _selection = new char[strlen(selection) + 1];
	strcpy(_selection, selection);

    if (_dialogBox) {
		XmString xmstr = XmStringCreateLocalized(_selection);
		XtVaSetValues(_dialogBox, XmNdirSpec, xmstr, NULL);
		XmStringFree(xmstr);
    }
}

const char *
VkFileSelectionDialog::fileName()
{
    return _filename;
}

void
VkFileSelectionDialog::ok(Widget w, XtPointer callData)
{
    char *filename;

    XmFileSelectionBoxCallbackStruct *cb
		= (XmFileSelectionBoxCallbackStruct*)callData;

    XmStringGetLtoR(cb->value, XmFONTLIST_DEFAULT_TAG, &filename);
    delete []_filename;
    _filename = new char[strlen(filename) + 1];
	strcpy(_filename, filename);

	XtFree(filename);

	VkDialogManager::ok(w, callData);
}

VkFileSelectionDialog* theFileSelectionDialogInstance()
{
	static VkFileSelectionDialog* instance = 0;
	if (instance == 0) {
		instance = new VkFileSelectionDialog("FileSelection");
	}
	return instance;
}
