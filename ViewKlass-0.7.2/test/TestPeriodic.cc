/*****************************************************************
    TestPeriodic - Test the VkPeriodic class.

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

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: TestPeriodic.cc,v 1.7 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkCallbackObject.h>

#include "TestPeriodic.h"

TestPeriodic::TestPeriodic()
	: VkCallbackObject(),
	  mCount(0)
{
	mPeriodic = new VkPeriodic(1000);
	mPeriodic->addCallback(VkPeriodic::timerCallback, this,
						   (VkCallbackMethod)&TestPeriodic::ticked);

	mPeriodic->start();

	mProgress = new VkProgressDialog("testPeriodic");
	mProgress->post("Testing VkPeriodic\n1 Second per tick",
					"periodicHelpStr", (VkSimpleWindow*)0);
}

TestPeriodic::~TestPeriodic()
{
	delete mPeriodic;
	delete mProgress;
}

void
TestPeriodic::ticked(VkCallbackObject* obj,
					 void* clientData,
					 void* callData)
{
	if (mProgress->wasInterupted()) {
		mCount = 0;
		// cerr << "TestPeriodic::ticked() calling mPeriodic->stop()" << endl;
		mPeriodic->stop();
	} else {
		mCount = (mCount % 100) + 1;
		mProgress->setPercentDone(mCount);
	}
}
