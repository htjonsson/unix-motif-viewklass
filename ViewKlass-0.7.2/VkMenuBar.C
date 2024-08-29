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
 * VkMenuBar.C
 *
 * This file contains the class implementation for the VkMenuBar class,
 * derived from VkMenu, allowing menu bars in VkWindows.
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
	= "$Id: VkMenuBar.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkMenuBar.h>
#include <Vk/VkHelpPane.h>

using namespace std;

VkMenuBar::VkMenuBar(Boolean showHelpPane)
	: VkMenu("menuBar"),
	  _showHelpPane(showHelpPane)
{
}

VkMenuBar::VkMenuBar(const char* name, Boolean showHelpPane)
	: VkMenu(name),
	  _showHelpPane(showHelpPane)
{
}

VkMenuBar::VkMenuBar(VkMenuDesc* menuDesc, 
					 XtPointer defaultClientData,
					 Boolean showHelpPane)
	: VkMenu("menuBar"),
	  _showHelpPane(showHelpPane)
{
	_defaultClientData = defaultClientData;
	createFromMenuDesc(menuDesc, defaultClientData);
}

VkMenuBar::VkMenuBar(const char* name,
					 VkMenuDesc* menuDesc,
					 XtPointer defaultClientData,
					 Boolean showHelpPane)
	: VkMenu(name),
	  _showHelpPane(showHelpPane)
{
	_defaultClientData = defaultClientData;
	createFromMenuDesc(menuDesc, defaultClientData);
}

VkMenuBar::~VkMenuBar()
{
}

void
VkMenuBar::build(Widget parent)
{
	_baseWidget = XmCreateMenuBar(parent, (char*)name(), NULL, 0);

	installDestroyHandler();

	XtManageChild(baseWidget());
  
	for (int i = 0; i < _elements.size(); i++) {
		((VkMenuItem*)_elements[i])->build(baseWidget());
	}
	
	Widget helpWidget = NULL;
	if (_showHelpPane) {
		_helpPane = new VkHelpPane;
		_helpPane->build(baseWidget());
		helpWidget = _helpPane->baseWidget();
	} else {
		_helpPane = NULL;
	}
	XtVaSetValues(_baseWidget, XmNmenuHelpWidget, helpWidget, NULL);
  
	XtSetSensitive(_baseWidget, _sensitive);

	_isBuilt = TRUE;
}

void
VkMenuBar::showHelpPane(Boolean showit)
{
	// Ignore unless there is an actual change
	if (_showHelpPane != showit) {
		_showHelpPane = showit;
		
		// If the menubar has not yet been built then just set
		// _showHelpPane appropriately and let build() do the rest of
		// the work.
		if (_isBuilt) {
			if (_showHelpPane) {
				// Create and instantiate a new help pane only if we don't
				// already have one.
				if (!_helpPane) {
					_helpPane = new VkHelpPane;
					_helpPane->build(baseWidget());
				} else {
					// Just manage the existing help pane.
					XtManageChild(_helpPane->baseWidget());
				}
				// Tell the menu bar where to find its help menu pane.
				XtVaSetValues(_baseWidget,
							  XmNmenuHelpWidget, _helpPane->baseWidget(),
							  NULL);
			} else {
				// Unmanage the existing help pane.
				if (_helpPane) {
					XtUnmanageChild(_helpPane->baseWidget());
				}
				// Tell the menu bar that it dosen't have a help menu
				XtVaSetValues(_baseWidget, XmNmenuHelpWidget, NULL, NULL);
			}
		}
	}
}
