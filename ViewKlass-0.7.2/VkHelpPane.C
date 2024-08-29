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
 * VkHelpPane.C
 *
 * This file contains the source code necessary for the implementation
 * of the VkHelpPane class.
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
	= "$Id: VkHelpPane.C,v 1.14 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>
#include <string>

using namespace std;

#include <Vk/VkHelpPane.h>
#include <Vk/VkHelpAPI.h>
#include <X11/cursorfont.h>

const char* const
VkHelpPane::defaultResourceSpec[] = {
	".labelString: Help",
	".mnemonic: H",
	"*helpOnContextMenuItem.labelString: Click for Help",
	"*helpOnContextMenuItem.mnemonic: C",
	"*helpOnContextMenuItem.accelerator: Shift<Key>F1",
	"*helpOnContextMenuItem.acceleratorText: S-F1",
	"*helpOverviewMenuItem.labelString: Overview",
	"*helpOverviewMenuItem.mnemonic: O",
	"*helpIndexMenuItem.labelString: Index",
	"*helpIndexMenuItem.mnemonic: I",
	"*helpKeysMenuItem.labelString: Keys & ShortCuts",
	"*helpKeysMenuItem.mnemonic: K",
	"*helpVersionMenuItem.labelString: Product Info",
	"*helpVersionMenuItem.mnemonic: P",
	NULL
};

VkHelpPane::VkHelpPane(const char *name,
					   VkMenuDesc *desc,
					   XtPointer defaultClientData)
	: VkSubMenu (name, desc, defaultClientData)
{
	createFromMenuDesc(desc, defaultClientData);
	
	addAction("helpOnContextMenuItem", clickForHelpCallback, this);
	addAction("helpOverviewMenuItem", overviewCallback, this);
	addSeparator("sep1");
	addAction("helpIndexMenuItem", indexCallback, this);
	addAction("helpKeysMenuItem", keysCallback, this);
	addSeparator("sep2");
	addAction("helpVersionMenuItem", showVersionCallback, this);
}

VkHelpPane::VkHelpPane(Widget parent,
					   const char *name,
					   VkMenuDesc *desc,
					   XtPointer defaultClientData)
	: VkSubMenu (parent, name, desc, defaultClientData)
{
	createFromMenuDesc(desc, defaultClientData);
	
	addAction("helpOnContextMenuItem", clickForHelpCallback, this);
	addAction("helpOverviewMenuItem", overviewCallback, this);
	addSeparator("sep1");
	addAction("helpIndexMenuItem", indexCallback, this);
	addAction("helpKeysMenuItem", keysCallback, this);
	addSeparator("sep2");
	addAction("helpVersionMenuItem", showVersionCallback, this);
  
	build(parent);
}

VkHelpPane::~VkHelpPane()
{
	//empty
}

void
VkHelpPane::build(Widget parent)
{
	Arg args[2];
	int i;

	setDefaultResources(parent, defaultResourceSpec);
  
	helpCursor = XCreateFontCursor(theApplication->display(),
								   XC_question_arrow);

	if (_tearOff) {
		XtSetArg(args[0], XmNtearOffModel, XmTEAR_OFF_ENABLED);
	} else {
		XtSetArg(args[0], XmNtearOffModel, XmTEAR_OFF_DISABLED);
	}
	_pulldown = XmCreatePulldownMenu(parent, (char *)_name, args, 1);

	XtSetArg(args[0], XmNsubMenuId, _pulldown);
	_baseWidget = XmCreateCascadeButtonGadget(parent, (char *)_name, args, 1);

	installDestroyHandler();

	XtManageChild(baseWidget());
  
	for (i = 0; i < _elements.size(); i++) {
		((VkMenuItem*)_elements[i])->build(_pulldown);
	}
	
	_isBuilt = TRUE;
}

void
VkHelpPane::showVersion()
{
    VkSimpleWindow *parent = VkSimpleWindow::getWindow(this);

    theApplication->busy();

    theApplication->aboutDialog()->setTitle(theApplication->name());

	string msg = (char*)VkGetResource(theApplication->baseWidget(),
									  "vkAppNameL10NString",
									  "VkAppNameL10NString",
									  XmRString,
									  "Application Name:");
	msg += " ";
	msg += theApplication->applicationClassName();
	
    if (theApplication->versionString()) {
		msg += "\n";
		msg += theApplication->versionString();
	}
	
	theApplication->aboutDialog()->post(msg.c_str(),parent);
	
    theApplication->notBusy();
}

void
VkHelpPane::showVersionCallback(Widget w, XtPointer clientData,
								XtPointer callData)
{
    VkHelpPane *obj = (VkHelpPane*)clientData;

    obj->showVersion();
}

void
VkHelpPane::clickForHelp()
{
    XEvent ev;
    Widget helpWidget =
		XmTrackingEvent(theApplication->mainWindow()->baseWidget(),
						helpCursor, False, &ev);

    if (helpWidget == NULL) return;

    Widget current = helpWidget;

    theApplication->busy();

    string fullyQual = XtName(current);
    
    do {
		fullyQual = "." + fullyQual;
		current = XtParent(current);
		fullyQual = XtName(current) + fullyQual;
    } while (current != theApplication->baseWidget());

    theApplication->notBusy();

    theApplication->helpMsg((char*)fullyQual.c_str(), NULL, NULL);
}

Widget
VkHelpPane::isParentAShell()
{
    Widget current = _baseWidget;

    theApplication->busy();

    while (!XtIsShell(current)) {
		current = XtParent(current);
	}

    theApplication->notBusy();

    if (XtIsSubclass(current, topLevelShellWidgetClass)) {
		return current;
    } else {
		return 0;
	}
}

void 
VkHelpPane::overview()
{
    Widget shell = isParentAShell();

    if (shell != 0) {
		string key = XtName(shell);
		key += ".overview";
		theApplication->helpMsg((key.c_str()),
								NULL, NULL);
    } else {
      theApplication->helpMsg(const_cast<char*>("overview"), NULL, NULL);
    }
}

void
VkHelpPane::showIndex()
{
    Widget shell = isParentAShell();
    
    if (shell != 0) {
		string key = XtName(shell);
		key += ".index";
		theApplication->helpIndexMsg(const_cast<char*>(key.c_str()),
									 NULL);
    } else {
      theApplication->helpIndexMsg(const_cast<char*>("index"), NULL);
    }
}

void
VkHelpPane::keys()
{
    Widget shell = isParentAShell();
    
    if (shell != 0) {
		string key = XtName(shell);
		key += ".keys";
		theApplication->helpMsg(const_cast<char*>(key.c_str()),
									 NULL, NULL);
    } else {
		theApplication->helpMsg("keys", NULL, NULL);
    }
}

void
VkHelpPane::clickForHelpCallback(Widget w, XtPointer clientData,
								 XtPointer callData)
{
    VkHelpPane *obj = (VkHelpPane*)clientData;

    obj->clickForHelp();
}

void
VkHelpPane::overviewCallback(Widget w, XtPointer clientData,
							 XtPointer callData)
{
    VkHelpPane *obj = (VkHelpPane*)clientData;

    obj->overview();    
}

void
VkHelpPane::indexCallback(Widget w, XtPointer clientData, XtPointer callData)
{
    VkHelpPane *obj = (VkHelpPane*)clientData;

    obj->showIndex();    
}

void
VkHelpPane::keysCallback(Widget w, XtPointer clientData, XtPointer callData)
{
    VkHelpPane *obj = (VkHelpPane*)clientData;

    obj->keys();
}
