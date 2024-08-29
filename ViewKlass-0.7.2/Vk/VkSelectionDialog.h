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
 * $Id: VkSelectionDialog.h,v 1.4 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for 
 * VkSelectionDialog class, my first attempt (even
 * successful) at extending the ViewKlass.  Why SGI
 * didn't put a SelectionDialog in theirs is beyond
 * me - toshok
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKSELECTIONDIALOG_H
#define VKSELECTIONDIALOG_H

#include <Vk/VkConfig.h>
#include <Vk/VkNameList.h>
#include <Vk/VkDialogManager.h>

class VkSelectionDialog : public VkDialogManager {
 public:
    VkSelectionDialog(const char *name);

    virtual ~VkSelectionDialog();

    virtual Widget createDialog(Widget parent);
    virtual const char *className() { return "VkSelectionDialog"; }

	void clearList();
	
    void addItem(const char *item, bool update = true);
	void setNumVisibleItems(const int numVisible) { _numVisible = numVisible; }
	void setListLabel(const char* label);

	int getNumSelected();
	unsigned int* getSelectedPositions();
	char* getSelection();

	Widget getNamedChild(const char* name);
	Widget getListWidget();
	
    int itemIndex(const char* item);

private:
	Widget _dialogBox;
	Widget _list;
	
    VkNameList* _items;

	int _numVisible;
	XmString _listLabelString;
};

extern VkSelectionDialog* theSelectionDialogInstance();
#define theSelectionDialog theSelectionDialogInstance()


#endif // VKSELECTIONDIALOG
