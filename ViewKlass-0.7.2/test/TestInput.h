/*****************************************************************
    TestInput - Tests the VkInput class.

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
#ifndef TESTINPUT_H
#define TESTINPUT_H

#include <Vk/VkInput.h>

#include <Vk/VkProgressDialog.h>

class TestInput : VkCallbackObject
{
public:
	TestInput();
	
	~TestInput();

	void inputAvailable(VkCallbackObject* obj, void* clientData,
						void* callData);

	void checkFile();

private:

	VkInput* mInput;

	int mFileNo;

	// The textfield which displays the data read from the VkInput fd().
	Widget inputText;

	// The widget in which the data is typed.
	Widget typedText;
	
};

#endif // TESTINPUT_H
