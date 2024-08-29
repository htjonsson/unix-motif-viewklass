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
 * VkGenericDialog.C
 *
 * This file contains the class implementation
 * for VkGenericDialog boxes, which form
 * the base, abstract class from which programmers
 * can extend, providing necessary dialog
 * functionality.
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
	= "$Id: VkGenericDialog.C,v 1.9 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkGenericDialog.h>

using namespace std;


VkGenericDialog::VkGenericDialog(const char *name)
	: VkDialogManager(name)
{
}

Widget
VkGenericDialog::createDialog(Widget parent)
{
  XmString okLabel = XmStringCreateLocalized(const_cast<char*>("Ok"));
  XmString cancelLabel = XmStringCreateLocalized(const_cast<char*>("Cancel"));
  XmString applyLabel = XmStringCreateLocalized(const_cast<char*>("Apply"));
  XmString helpLabel = XmStringCreateLocalized(const_cast<char*>("Help"));

    Arg args[4]; 
    int n = 0;

    XtSetArg(args[n],XmNokLabelString, okLabel); n++;
    XtSetArg(args[n],XmNcancelLabelString, cancelLabel); n++;
    XtSetArg(args[n],XmNapplyLabelString, applyLabel); n++;
    XtSetArg(args[n],XmNhelpLabelString, helpLabel); n++;

	// The VkGenericDialog man page suggests that it creates
	// an XmTemplateDialog but we actually need to use
	// a Prompt dialog to get an Apply button available.
	// In particular the VkPrefDialog, which is derived from
	// VkGenericDialog, must have an Apply button.
    Widget dialogBox = XmCreatePromptDialog(parent,
											(char *)_name,
											args,n);
    XmStringFree(okLabel);
    XmStringFree(cancelLabel);
    XmStringFree(applyLabel);
    XmStringFree(helpLabel);

	// By default get rid of the Prompt text field and its label.
    Widget w = XtNameToWidget(dialogBox, "Selection");
	XtUnmanageChild(w);
    w = XtNameToWidget(dialogBox, "Text");
	XtUnmanageChild(w);
	
    return dialogBox;
}
