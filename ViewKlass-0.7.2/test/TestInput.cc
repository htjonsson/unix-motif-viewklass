/*****************************************************************
    TestInput - Test the VkInput class.

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
	= "$Id: TestInput.cc,v 1.5 2009/03/21 11:44:34 jostle Exp $";

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "TestInput.h"

TestInput::TestInput()
	: VkCallbackObject()
{
	mInput = new VkInput();

	FILE* fid = fopen("JuNkFiLe.txt", "a+");
	
	mFileNo = fileno(fid);

	mInput->addCallback(VkInput::inputCallback, this,
						   (VkCallbackMethod)&TestInput::inputAvailable);

}

TestInput::~TestInput()
{
	delete mInput;
}

void
TestInput::checkFile()
{
	mInput->attach(mFileNo, XtInputReadMask);
}
		
void
TestInput::inputAvailable(VkCallbackObject* obj,
						  void* clientData,
						  void* callData)
{
	VkInput* in = (VkInput*)callData;
	const int bufSize = 4096;
	char buf[bufSize];
	int n;
	while ((n = read(in->fd(), buf, bufSize)) > 0) {
		for (int i = 0; i < n; ++i) {
			putchar(buf[i]);
		}
	}
	in->remove();
}
