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
 * $Id: VkMenuBar.h,v 1.5 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the 
 * VkMenuBar class.  This class allows the user to
 * assign menu bars to VkWindows that make up
 * his/her interface.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKMENUBAR_H
#define VKMENUBAR_H

#include <Xm/RowColumn.h>
#include <Vk/VkConfig.h>
#include <Vk/VkMenu.h>

class VkSubMenu;
class VkWindow;
class VkHelpPane;

class VkMenuBar : public VkMenu {
public:
	VkMenuBar(Boolean showHelpPane = True);
	VkMenuBar(const char* name,
			  Boolean showHelpPane = True);
	VkMenuBar(VkMenuDesc* menuDesc,
			  XtPointer defaultClientData = NULL,
			  Boolean showHelpPane = True);
	VkMenuBar(const char* name,
			  VkMenuDesc* menuDesc,
			  XtPointer defaultClientData = NULL,
			  Boolean showHelpPane = True);
	
	virtual ~VkMenuBar();
    
	void showHelpPane(Boolean showit = True);
	
	VkHelpPane* helpPane() const { return _helpPane; }

	VkMenuItemType menuType() { return BAR; }

	Boolean isContainer() { return True; }

	virtual const char* className() { return "VkMenuBar"; }
  
	void build(Widget parent);

protected:

	Boolean _showHelpPane;
	VkHelpPane* _helpPane;
  
};

#endif // VKMENUBAR_H
