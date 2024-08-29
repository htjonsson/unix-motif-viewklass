/*****************************************************************
    TestWindow - Tests the VkWindow class.

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
#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <Vk/VkWindow.h>

class VkRadioGroup;

class TestWindow : public VkWindow
{
public:
	TestWindow(const char* name);
	
	~TestWindow();

	static void closeCallback(Widget, XtPointer, XtPointer);

	static void toggleCallback(Widget, XtPointer, XtPointer);

	VkRadioGroup* mRadioGroup;

	Widget tb1;
	Widget tb2;
	Widget tb3;
	Widget tb4;
	
};

#endif // TESTWINDOW_H
