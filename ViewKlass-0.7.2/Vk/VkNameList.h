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
 * $Id: VkNameList.h,v 1.7 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the definition for the VkNameList
 * class, which gives an interface to a list of strings.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKNAMELIST_H
#define VKNAMELIST_H

#include <vector>
#include <string>
#include <algorithm>

#include <Xm/Xm.h>
#include <Vk/VkConfig.h>

class VkNameList {
 public:
    VkNameList();
    VkNameList(const VkNameList& givenList);
    VkNameList(const char* name);

    virtual ~VkNameList();

    void add(const char* name);
    void add(const VkNameList& givenList);

	int getIndex(const char* name);

    void remove(const char* name);
	void remove(int index, int count=1);

    VkNameList& operator=(const VkNameList& givenList);

    void sort() { std::sort(_contents.begin(), _contents.end()); }
    void reverse() { std::reverse(_contents.begin(), _contents.end()); }

    void removeDuplicates();

    int size() { return _contents.size(); }

    int exists(const char* name);

    const char* operator[](int indx);
	const char* getString(int index);
    
    VkNameList operator[](char* subString);
	VkNameList*  getSubStrings(const char* subString);

    int operator==(const VkNameList& givenList);

    const char* mostCommonString();

    VkNameList* completeName(const char* name,
							 char* &completedName,
							 int& nMatching);

    operator char**();
	char** getStringTable();

    operator XmStringTable();
	XmStringTable getXmStringTable();
	static void freeXmStringTable(XmStringTable);

 private:
    std::vector <std::string> _contents;

};

#endif // VKNAMELIST_H
