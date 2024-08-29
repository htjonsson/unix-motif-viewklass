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
 * VkNameList.C
 *
 * This file contains the implementation for the VkNameList
 * class, which gives a programmatic interface to a list of
 * strings
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: VkNameList.C,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <map>
#include <string>

using namespace std;

#include <Vk/VkNameList.h>

VkNameList::VkNameList()
{
}

VkNameList::VkNameList(const VkNameList& givenList)
{
	_contents = givenList._contents;
}

VkNameList::VkNameList(const char* name)
{
	_contents.push_back(name);
}

VkNameList::~VkNameList()
{
}

void
VkNameList::add(const char* name)
{
	_contents.push_back(name);
}

void
VkNameList::add(const VkNameList &givenList)
{
	vector<string>::const_iterator from = givenList._contents.begin();
	vector<string>::const_iterator to   = givenList._contents.end();

	while (from != to) _contents.push_back(*from++);
}

int
VkNameList::getIndex(const char* name)
{
	vector<string>::iterator from = _contents.begin();
	vector<string>::iterator to   = _contents.end();

	int result = -1;
	int i = 0;
	while (from != to) {
		if (*from == name) {
			result = i;
			break;
		}
		++i;
		++from;
	}
	return result;
}

void
VkNameList::remove(const char* name)
{
	_contents.erase(std::remove(_contents.begin(), _contents.end(), name),
				   _contents.end());
}

void
VkNameList::remove(int index, int count)
{
	_contents.erase(_contents.begin() + index,
					_contents.begin() + index + count);
}

VkNameList& 
VkNameList::operator=(const VkNameList &givenList)
{
	_contents = givenList._contents;
	return *this;
}

void
VkNameList::removeDuplicates()
{
	// name list must be sorted first
	std::sort(_contents.begin(), _contents.end());
	_contents.erase(std::unique(_contents.begin(), _contents.end()),
				   _contents.end());
}

int
VkNameList::exists(const char* name)
{
	if (std::find(_contents.begin(), _contents.end(), name)
		== _contents.end()) {
		return 0;
	} else {
		return 1;
	}
}

const char*
VkNameList::operator[](int indx)
{
	return getString(indx);
}

const char*
VkNameList::getString(int indx)
{
	string res = _contents[indx];
	char* ret = new char[res.size() + 1];
	strcpy(ret, res.c_str());
	return ret;
}

int
VkNameList::operator==(const VkNameList& givenList)
{
	if (_contents == givenList._contents) {
		return 1;
	} else {
		return 0;
	}
}

const char*
VkNameList::mostCommonString()
{
	std::map<string, int> m;
	std::pair<string, int> p;
	vector<string>::iterator from = _contents.begin();
	vector<string>::iterator to   = _contents.end();
	std::map<string, int>::iterator piter;

	while (from != to) {
		piter = m.find(*from);
		if (piter == m.end()) {
			m.insert(make_pair(*from, 1));
		} else {
			++((*piter).second);
		}
		++from;
	}

	string res;
	int maxCount = 0;
	for (piter = m.begin(); piter != m.end(); piter++) {
		if ((*piter).second > maxCount) {
			res = (*piter).first;
			maxCount = (*piter).second;
		}
	}

	char* ret = new char[res.size() + 1];
	strcpy(ret, res.c_str());
	return ret;
}

VkNameList*
VkNameList::completeName(const char* name,
						 char*& completedName,
						 int& nMatching)
{
	VkNameList* nlp = getSubStrings(name);

	// Shortcut if no matches
	if (nlp->size() == 0) {
		completedName = 0;
		nMatching = 0;
		delete nlp;
		return 0;
	}

	nlp->removeDuplicates();
	nMatching = nlp->size();
	char* firstString = new char[sizeof(nlp->getString(0))];
    strcpy(firstString, nlp->getString(0));

	// Shortcut if only one match
	if (nlp->size() == 1) {
		completedName = new char[strlen(firstString) + 1];
		strcpy(completedName, firstString);
		delete [] firstString;
		return nlp;
	}

	int firstLen = strlen(firstString);
	int commonLength = 0;
	// for each character in the first string (including the nul terminator)
	for (int i = 0; i < firstLen + 1; ++i) {
		// and for each other string
		for (int j = 1; j < nMatching; ++j) {
			// if any character in this position does not match
			// the first string then we've found the common prefix.
			const char* str = nlp->getString(j);
			if (str[i] != firstString[i]) {
				commonLength = i - 1;
				delete [] str;
				break;
			}
			delete [] str;
		}
		if (commonLength > 0) break;
	}
	// truncate the first string and use it as the value of completedName.
	firstString[commonLength + 1] = 0;
	completedName = new char[strlen(firstString) + 1];
	strcpy(completedName, firstString);
	delete [] firstString;

	return nlp;
}

VkNameList
VkNameList::operator[](char* subString)
{
	return *(getSubStrings(subString));
}

VkNameList*
VkNameList::getSubStrings(const char* subString)
{
	VkNameList* nl = new VkNameList();
	vector<string>::iterator from = _contents.begin();
	vector<string>::iterator to   = _contents.end();

	int len = strlen(subString);
	while(from != to) {
		if(!strncmp(subString, (*from).c_str(), len)) {
			nl->add((*from).c_str());
		}
		from++;
	}
	return nl;
}


char**
VkNameList::getStringTable()
{
	int numElements = _contents.size();
	char** value = new char*[numElements + 1];

	for (int i=0; i < numElements; i++) {
		value[i] = const_cast<char*>(_contents[i].c_str());
	}
	value[numElements] = NULL;
	
	return value;
}

VkNameList::operator char**()
{
	return getStringTable();
}

XmStringTable
VkNameList::getXmStringTable()
{
	int numElements = _contents.size();
	XmStringTable value = new XmString[numElements + 1];

	for (int i = 0; i < numElements; ++i) {
		value[i] =
			XmStringCreateLocalized(const_cast<char*>(_contents[i].c_str()));
	}
	value[numElements] = NULL;
	
	return value;
}

VkNameList::operator XmStringTable()
{
	return getXmStringTable();
}

void
VkNameList::freeXmStringTable(XmStringTable t)
{
	int i = 0;
	while (t && t[i] != 0) {
		XmStringFree(t[i++]);
	}
	delete [] t;
}

