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
 * VkWindow.C
 *
 * This file contains the implementation for the VkWindow class,
 * which forms a derived class from VkSimpleWindow, adding menubar
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
= "$Id: VkWindow.C,v 1.11 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkWindow.h>

VkWindow::VkWindow(const char* name,
				   ArgList args,
				   Cardinal argCount)
	: VkSimpleWindow(name, args, argCount)
{
    _menuBar = NULL;
    _menuBarInstantiated = false;
}

VkWindow::~VkWindow()
{
    delete _menuBar;
}

void
VkWindow::show()
{
    if (!_menuBarInstantiated && _menuBar) {
		_menuBar->show(mainWindowWidget());
		_menuBarInstantiated = true;
    }
    VkSimpleWindow::show();
}

void
VkWindow::setMenuBar(VkMenuBar* menuObj)
{
    _menuBar = menuObj;
}

void
VkWindow::setMenuBar(VkMenuDesc* menuDesc)
{
    if (_menuBar == NULL) {
		_menuBar = new VkMenuBar(menuDesc);
	}
}

void
VkWindow::setMenuBar(VkMenuDesc* menuDesc, XtPointer defaultClientData)
{
    if (_menuBar == NULL) {
		_menuBar = new VkMenuBar(menuDesc, defaultClientData);
	}
}

VkMenuBar* 
VkWindow::menu() const
{
    return _menuBar;
}

VkSubMenu* 
VkWindow::addMenuPane(const char* name)
{
    if (_menuBar == NULL) { // Create a new one
		_menuBar = new VkMenuBar();
	}

    return (_menuBar->addSubmenu(name));
}

VkSubMenu* 
VkWindow::addMenuPane(const char* name,
					  VkMenuDesc* menudesc)
{

    if (!_menuBar) { // Create a new one
		_menuBar = new VkMenuBar();
	}
	
    return (_menuBar->addSubmenu(name, menudesc, NULL));
}

VkWindow*
VkWindow::getWindow(VkComponent* component)
{
	// Find component's shell parent
    Widget current = component->baseWidget();

	if (current == 0) return 0;

    while (!XtIsShell(current)) {
		current = XtParent(current);
	}
    if (XtIsSubclass(current, applicationShellWidgetClass)) {
		// Find the app's window which matches
		VkComponentList cl = *(theApplication->winList());
		for (int i = 0; i < cl.size(); ++i) {
			if (cl[i]->baseWidget() == current) {
				try {
  					VkWindow* win = dynamic_cast<VkWindow*>(cl[i]);
					return win;
				} catch(exception e) {
					// dynamic_cast will throw an exception if the object
					// is not a VkWindow or subclass
					cerr << "VkWindow::getWindow - " << e.what() << endl;
					return 0;
				}
			}
		}
		// No matching window found
		return 0;
    } else {
		return 0;
	}
}

VkMenuBar*
VkWindow::getMenu(VkComponent* component)
{
	VkWindow* win = getWindow(component);
	if (win) {
		// Get the window's menu bar object
		return win->menu();
	} else {
		return 0;
	}
}

