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
 * VkCursorList.C
 *
 * This file contains the implementation of the class VkCursorList.  This
 * class makes it easier to add an animated cursor to your applications.
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
	= "$Id: VkCursorList.C,v 1.7 2009/03/21 11:44:34 jostle Exp $";


#include <Vk/VkApp.h>
#include <Vk/VkCursorList.h>

using namespace std;

VkCursorList::VkCursorList(int numCursors)
	: _numCursors(numCursors),
	  _currentIndex(0)
{
	_cursorList = new Cursor[_numCursors];

	for (int i = 0; i < _numCursors; ++i) {
		_cursorList[i] = None;
	}
}

VkCursorList::~VkCursorList()
{
	for (int i = 0; i < _numCursors; ++i) {
		XFreeCursor(theApplication->display(), _cursorList[i]);
	}
	delete [] _cursorList;
}

Cursor
VkCursorList::next()
{
	_currentIndex = (_currentIndex + 1) % _numCursors;
	if (_cursorList[_currentIndex] == None) {
		createCursor(_currentIndex);
	}
	return _cursorList[_currentIndex];
}

Cursor
VkCursorList::current()
{
	if (_cursorList[_currentIndex] == None) {
		createCursor(_currentIndex);
	}
	return _cursorList[_currentIndex];
}

void
VkCursorList::reset()
{
	_currentIndex = 0;
}
