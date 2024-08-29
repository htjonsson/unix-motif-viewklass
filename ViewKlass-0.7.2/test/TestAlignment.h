/*****************************************************************
    TestAlignment - Tests the VkAlignment class.

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
#ifndef TESTALIGNMENT_H
#define TESTALIGNMENT_H

#include <Vk/VkAlignmentGroup.h>

class TestAlignment : public VkComponent
{
public:
	TestAlignment(const char* name, Widget parent);
	
	~TestAlignment();

	static void normalOptionCallback(Widget w, XtPointer clientData,
									 XtPointer callData);
	static void topOptionCallback(Widget w, XtPointer clientData,
								  XtPointer callData);
	static void bottomOptionCallback(Widget w, XtPointer clientData,
									 XtPointer callData);
	static void leftOptionCallback(Widget w, XtPointer clientData,
								   XtPointer callData);
	static void rightOptionCallback(Widget w, XtPointer clientData,
									XtPointer callData);
	static void widthOptionCallback(Widget w, XtPointer clientData,
									XtPointer callData);
	static void heightOptionCallback(Widget w, XtPointer clientData,
									 XtPointer callData);
	static void horizOptionCallback(Widget w, XtPointer clientData,
									XtPointer callData);
	static void vertOptionCallback(Widget w, XtPointer clientData,
								   XtPointer callData);
	static void printOptionCallback(Widget w, XtPointer clientData,
								   XtPointer callData);


	VkAlignmentGroup* mTopAlign;
	VkAlignmentGroup* mBottomAlign;
	VkAlignmentGroup* mLeftAlign;
	VkAlignmentGroup* mRightAlign;
	VkAlignmentGroup* mOptionMenuAlign;

	VkOptionMenu* mOptionMenu;
	
	const char* className() { return "TestAlignment"; }
};

#endif // TESTALIGNMENT_H
