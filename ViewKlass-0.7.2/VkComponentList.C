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
 * VkComponentList.h
 *
 * This file contains the implementation for my workaround
 * for the missing VkComponentList class.  I can find no
 * hardcopy documentation for this class, so until I have access
 * to the man pages, I can only use this :(
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
= "$Id: VkComponentList.C,v 1.5 2009/03/21 11:44:34 jostle Exp $";

#include <algorithm>
#include <iterator>

using namespace std;

#include <Vk/VkComponent.h>
#include <Vk/VkComponentList.h>


VkComponentList::VkComponentList()
{
}

void
VkComponentList::remove(VkComponent* c)
{
	elements.erase(std::remove(elements.begin(), elements.end(), c),
				   elements.end());
}

void
VkComponentList::removeFirst(VkComponent* c)
{
	iter = std::find(elements.begin(), elements.end(), c);
	if (iter != elements.end()) {
		elements.erase(iter);
	}
}

void
VkComponentList::removeLast(VkComponent* c)
{
  	vector<VkComponent*>::reverse_iterator riter =
		std::find(elements.rbegin(), elements.rend(), c);

	if (riter != elements.rend()) {
		elements.erase(riter.base());
	}
}




