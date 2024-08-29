/*****************************************************************
    TestCompletion - Tests the VkCompletion class.

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
#ifndef TESTCOMPLETION_H
#define TESTCOMPLETION_H

#include <Vk/VkComponent.h>

class TestCompletion : public VkComponent
{
public:
	TestCompletion(const char* name, Widget parent);
	
	~TestCompletion();

	VkCompletionField* mCompField;
	
	static const char* const _defaultResources[];
	
	const char* className() { return "TestCompletion"; }
};

#endif // TESTCOMPLETION_H
