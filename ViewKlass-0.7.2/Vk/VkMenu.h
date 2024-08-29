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
 * $Id: VkMenu.h,v 1.8 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the c++ class definition for the
 * abstract class VkMenu.  This class forms the basis
 * for many of the menus that can be instantiated in
 * user applications, and offers an array of generic
 * operations allowed in all of its subclasses.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMENU_H
#define VKMENU_H

#include <Vk/VkConfig.h>
#include <Vk/VkComponentList.h>
#include <Vk/VkMenuItem.h>

class VkWindow;
class VkMenuAction;
class VkMenuActionWidget;
class VkMenuConfirmFirstAction;
class VkMenuLabel;
class VkMenuSeparator;
class VkMenuToggle;
class VkSubMenu;
class VkRadioSubMenu;

typedef struct VkMenuDesc VkMenuDesc;

struct VkMenuDesc {
	VkMenuItemType menuType;
	const char* name;
	XtCallbackProc callback;
	VkMenuDesc* submenu;
	XtPointer clientData;
	XtCallbackProc undoCallback;
};

class VkMenu : public VkMenuItem {  // ABSTRACT CLASS

	friend class VkMenuItem;
	friend class VkSubMenu;

public:
	VkMenu(const char* name);

	virtual ~VkMenu();
  
	void add(VkMenuItem* item, int position = -1);
  
	VkMenuAction* addAction(const char* name,
							XtCallbackProc actionCallback = NULL,
							XtPointer clientData = NULL,
							int position = -1);

	VkMenuAction* addAction(const char* name,
							XtCallbackProc actionCallback,
							XtCallbackProc undoCallback,
							XtPointer clientData,
							int position = -1);

	VkMenuActionWidget* addActionWidget(const char* name,
										XtCallbackProc actionCallback = NULL,
										XtPointer clientData = NULL,
										int position = -1);
	VkMenuActionWidget* addActionWidget(const char* name,
										XtCallbackProc actionCallback,
										XtCallbackProc undoCallback,
										XtPointer clientData,
										int position = -1);
	
	VkMenuConfirmFirstAction* addConfirmFirstAction(
		const char* name,
		XtCallbackProc actionCallback = NULL,
		XtPointer clientData = NULL,
		int position = -1);
  
	VkMenuToggle* addToggle(const char* name,
							XtCallbackProc actionCallback = NULL,
							XtPointer clientData = NULL,
							int state = -1,
							int position = -1);
  
	VkMenuToggle* addToggle(const char* name,
							XtCallbackProc actionCallback = NULL,
							XtCallbackProc undoCallback = NULL,
							XtPointer clientData = NULL,
							int state = -1,
							int position = -1);
  
	VkMenuLabel* addLabel(const char* name,
						  int position  = -1);
  
	VkMenuSeparator* addSeparator(int position = -1);
  
	VkMenuSeparator* addSeparator(const char* name, int position = -1);
  
	VkSubMenu* addSubmenu(VkSubMenu* submenu, int position = -1);
  
	VkSubMenu* addSubmenu(const char* name, int position = -1);
  
	VkSubMenu* addSubmenu(const char* name,
						  VkMenuDesc* menuDesc,
						  XtPointer defaultClientData = NULL,
						  int position = -1);
  
	VkRadioSubMenu* addRadioSubmenu(VkRadioSubMenu* submenu,
									int position = -1);
  
	VkRadioSubMenu* addRadioSubmenu(const char* name,
									int position = -1);
  
	VkRadioSubMenu* addRadioSubmenu(const char* name,
									VkMenuDesc* menuDesc,
									XtPointer defaultClientData = NULL,
									int position = -1);
  
	VkMenuItem* findNamedItem(const char* name,
							  Boolean caseless = FALSE);
  
	// It would be good to have versions of the following
	// four methods (de)activate, remove and replace which
	// take VkMenuItem, Widget or position arguments.
	
	VkMenuItem* activateItem(const char* name);
  
	VkMenuItem* deactivateItem(const char* name);
  
	VkMenuItem* removeItem(const char* name);
  
	VkMenuItem* replace(const char* name, VkMenuItem* newItem);
  
	int numItems() const;
  
	int getItemPosition(VkMenuItem* item);
	int getItemPosition(const char* name);
	int getItemPosition(Widget w);
  
	VkMenuItem* operator[] (int indx) const;

	virtual const char* className() { return "VkMenu"; }

////////////////////////////////////////////////////////////////
// NYI
//  	static void useOverlayMenus(const Boolean flag);
//  	static void useWorkProcs(Boolean flag);
	
//  	// ViewKlass 2.1 Only
//  	VkScreen* getScreen();

protected:
	virtual void createFromMenuDesc(VkMenuDesc* desc,
									XtPointer defaultClientData = NULL);
	
	XtPointer _defaultClientData;

	VkComponentList _elements;
};

#endif // VKMENU_H

