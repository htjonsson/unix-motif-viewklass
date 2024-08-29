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
 * VkHelpAPI.C
 *
 * This file contains the implementation for
 * the ViewKlass help system.
 *
 * Chris Toshok
 * Copyright (C) 1994, 1995
 * The Hungry Programmers, Inc.
 *
 **/

#include <string>

using namespace std;

#include <Xm/TextF.h>
#include <Xm/MessageB.h>

#include <Vk/VkHelpAPI.h>
#include <Vk/VkApp.h>
#include <Vk/VkSimpleWindow.h>
#include <Vk/VkResource.h>
#include <Vk/VkInfoDialog.h>
#include <Vk/VkSelectionDialog.h>

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: VkHelpAPI.C,v 1.15 2009/03/21 11:44:34 jostle Exp $";

class HelpIndexDialog : public VkSelectionDialog
{
public:
	HelpIndexDialog(const char* in_key);
	virtual void post(Widget parent);
	virtual Widget createDialog(Widget parent);
	
    virtual void ok(Widget dialog, XtPointer callData);
    virtual void apply(Widget dialog, XtPointer callData);

	string _helpResName;
	string _indexKeyResName;
	vector<string> _indexKeys;
};

Widget
HelpIndexDialog::createDialog(Widget parent)
{
	Widget base = VkSelectionDialog::createDialog(parent);
	Widget text = XtNameToWidget(base, "Text");
	XmTextFieldSetEditable(text, False);
	return base;
}

void
HelpIndexDialog::post(Widget parent)
{
	string helpStr =
		(char*)VkGetResource(theApplication->baseWidget(),
							 (char*)_helpResName.c_str(),
							 (char*)_helpResName.c_str(),
							 XmRString,
							 "Select a topic.");

	string indexKeys =
		(char*)VkGetResource(theApplication->baseWidget(),
							 (char*)_indexKeyResName.c_str(),
							 (char*)_indexKeyResName.c_str(),
							 XmRString,
							 "");
	size_t start = 0;
	size_t pos = 0;
	pos = indexKeys.find(',', start);
	while (pos != string::npos) {
		_indexKeys.push_back(indexKeys.substr(start, pos - start));
		start = pos + 1;
		pos = indexKeys.find(',', start);
	}
	_indexKeys.push_back(indexKeys.substr(start, indexKeys.size() - start));
	
    Boolean helpMapMode =    // Cast to int to avoid compiler warning
		(long)VkGetResource(theApplication->baseWidget(),
								"helpAuthorMode",
								"HelpAuthorMode",
								XmRBoolean, "False");
    if (helpMapMode) {
		helpStr += "\n\n";
		helpStr += _helpResName;
    }

	VkDialogManager::post(helpStr.c_str(), parent);
}

void
HelpIndexDialog::ok(Widget dialog, XtPointer callData)
{
}

void
HelpIndexDialog::apply(Widget dialog, XtPointer callData)
{
	char* sel = getSelection();
	if (sel != 0) {
		int pos = itemIndex(sel);
		XtFree(sel);
		if (pos >= 0) {
			SGIHelpMsg((char*)(_indexKeys[pos].c_str()), NULL, NULL);
		}
	}
}

HelpIndexDialog::HelpIndexDialog(const char* in_key)
	: VkSelectionDialog("helpIndex")
{
	_showOK = false;
	_showApply = true;
	_showCancel = true;
	_showHelp = false;
	
	_helpResName = theApplication->applicationClassName();
	if (in_key) {
		_helpResName += ".";
		_helpResName += in_key;
	}

	_indexKeyResName = _helpResName + ".indexKeys";
	_helpResName += ".helpText";

}

static void
postHelpDialog(const char* in_key)
{
    static VkInfoDialog* dialog = 0;
	static Widget parent = 0;

	if (!dialog) {
		dialog = new VkInfoDialog("help");
		dialog->setTitle("Help");

		if (theApplication->mainWindow() &&
			theApplication->mainWindow()->baseWidget()) {
			parent = theApplication->mainWindow()->baseWidget();
		} else {
			parent = theApplication->baseWidget();
		}
	}

	string keyStr = theApplication->applicationClassName();
	if (in_key) {
		keyStr += ".";
		keyStr += in_key;
	}
	keyStr += ".helpText";

	string helpStr =
		(char*)VkGetResource(theApplication->baseWidget(),
							 (char*)keyStr.c_str(), (char*)keyStr.c_str(),
							 XmRString,
							 "Sorry, no help available on this topic");

    Boolean helpMapMode =    // Cast to int to avoid compiler warning
		(long)VkGetResource(theApplication->baseWidget(),
						   "helpAuthorMode",
						   "HelpAuthorMode",
						   XmRBoolean, "False");
    if (helpMapMode) {
		keyStr += "\n\n";
		helpStr = keyStr + helpStr;
    }

	dialog->post(helpStr.c_str(), parent);
}

static void
postIndexDialog(const char* in_key)
{
    static HelpIndexDialog* indexDialog = 0;
	static Widget parent = 0;

	if (!indexDialog) {
		indexDialog = new HelpIndexDialog(in_key);
		indexDialog->setTitle("Help Index");

		if (theApplication->mainWindow() &&
			theApplication->mainWindow()->baseWidget()) {
			parent = theApplication->mainWindow()->baseWidget();
		} else {
			parent = theApplication->baseWidget();
		}
	}

	indexDialog->post(parent);

}

int
SGIHelpInit(Display* display, const char* appClass, const char* /*reserved*/)
{
	// I wonder what should be done in here!
	// Probably nothing for the built-in help functions.
    return 1;
}

int
SGIHelpMsg(const char* in_key, const char* /*in_book*/, const char* /*reserved*/)
{
    postHelpDialog(in_key);
    return 1;
}

int
SGIHelpIndexMsg(const char* in_key, const char* /*reserved*/)
{
    postIndexDialog(in_key);
    return 1;
}
