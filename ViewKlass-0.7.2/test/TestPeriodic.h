/*****************************************************************
    TestPeriodic - Tests the VkPeriodic class.

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
#ifndef TESTPERIODIC_H
#define TESTPERIODIC_H

#include <Vk/VkPeriodic.h>

#include <Vk/VkProgressDialog.h>

class TestPeriodic : public VkCallbackObject
{
public:
	TestPeriodic();
	
	~TestPeriodic();

	void ticked(VkCallbackObject* obj, void* clientData, void* callData);

	VkProgressDialog* mProgress;

	VkPeriodic* mPeriodic;
	int mCount;
};

#endif // TESTPERIODIC_H
