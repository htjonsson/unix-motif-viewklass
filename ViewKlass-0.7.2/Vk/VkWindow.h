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
 * $Id: VkWindow.h,v 1.5 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the VkWindow class.
 * This class differs from the VkSimpleWindow class in that you
 * can put menu bars into Windows, but not into SimpleWindows.
 * 
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 *
 **/

#ifndef VKWINDOW_H
#define VKWINDOW_H

#include <Vk/VkConfig.h>
#include <Vk/VkApp.h>
#include <Vk/VkSimpleWindow.h>
#include <Vk/VkMenuBar.h>

class VkWindow : public VkSimpleWindow {
  
public:
    VkWindow(const char* name,
			 ArgList args = NULL,
			 Cardinal argCount = 0);
    
    virtual ~VkWindow();
    
    virtual const char* className() { return "VkWindow"; }
    
    void setMenuBar(VkMenuBar* menuObj);
    void setMenuBar(VkMenuDesc* menuDesc);
    void setMenuBar(VkMenuDesc* menuDesc, XtPointer defaultClientData);
    virtual VkMenuBar* menu() const;
    
    VkSubMenu* addMenuPane(const char* name);
    VkSubMenu* addMenuPane(const char* name, VkMenuDesc* menudesc);
    
    VkRadioSubMenu* addRadioMenuPane(const char* name);
    VkRadioSubMenu* addRadioMenuPane(const char* name,
									 VkMenuDesc* menudesc);
    
    virtual void show();

	static VkMenuBar* getMenu(VkComponent* component);
	static VkWindow* getWindow(VkComponent* component);

private:
	VkMenuBar* _menuBar;
	Boolean _menuBarInstantiated;
};

#endif /* VKWINDOW_H */


