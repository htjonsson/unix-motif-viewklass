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
 * $Id: VkHelpPane.h,v 1.7 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the class definition for the VkHelpPane class,
 * which allows the programmer to easily add help menu items to
 * the application.
 * 
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKHELPPANE_H
#define VKHELPPANE_H

#include <Xm/RowColumn.h>
#include <Xm/CascadeBG.h>
#include <Vk/VkConfig.h>
#include <Vk/VkSubMenu.h>

class VkHelpPane : public VkSubMenu {
 public:
    VkHelpPane(const char *name = "helpMenu",
			   VkMenuDesc *desc = NULL,
			   XtPointer defaultClientData = NULL);
    
    VkHelpPane(Widget parent,
			   const char *name = "helpMenu",
			   VkMenuDesc *desc = NULL,
			   XtPointer defaultClientData = NULL);
    
    virtual ~VkHelpPane();
    
    virtual const char *className() { return "VkHelpPane"; }
    
    void build(Widget parent);
  
 private:
    Cursor helpCursor;

    static const char* const defaultResourceSpec[];

    Widget isParentAShell();

    void showVersion();
    void clickForHelp();
    void overview();
    void showIndex();
    void keys();

    static void showVersionCallback(Widget w, XtPointer clientData,
									XtPointer callData);
    static void clickForHelpCallback(Widget w, XtPointer clientData,
									 XtPointer callData);
    static void overviewCallback(Widget w, XtPointer clientData,
								 XtPointer callData);
    static void indexCallback(Widget w, XtPointer clientData,
							  XtPointer callData);
    static void keysCallback(Widget w, XtPointer clientData,
							 XtPointer callData);

};

#endif // VKHELPPANE_H
