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
 * $Id: VkComponentList.h,v 1.7 2006/02/13 07:23:27 jostle Exp $
 *
 * This file contains my temporary workaround for the
 * missing VkComponentList class.  My work is probably not
 * what will be here forever, but for now, it works... :(
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKCOMPONENTLIST_H
#define VKCOMPONENTLIST_H

#include <vector>

#include <Vk/VkConfig.h>

class VkComponent;

class VkComponentList {

public:
    VkComponentList();
	virtual ~VkComponentList() {};
    
    virtual void add(VkComponent* c) { elements.push_back(c); }
    virtual void remove(VkComponent* c);
    virtual void removeFirst(VkComponent* c);
    virtual void removeLast(VkComponent* c);

    int size() const { return elements.size(); }

    VkComponent* operator[](int indx) const { return elements[indx]; }

	void insert(int pos, VkComponent* c)
		{ 
			elements.insert( (elements.begin( ) + pos), c ); 
		}
    
	void remove(int pos)
		{ 
			elements.erase( (elements.begin( ) + pos ) ); 
		}
    
private:
    std::vector<VkComponent*> elements;
    std::vector<VkComponent*>::iterator iter;
};

#endif /* VKCOMPONENTLIST_H */

