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

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: testVkWidgetList.cc,v 1.6 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkApp.h>
#include <Vk/VkWindow.h>
#include <Vk/VkSubMenu.h>
#include <Vk/VkWidgetList.h>
#include <iostream>
#include "Slider.h"

using namespace std;

void
printWidgetList(VkWidgetList& wl)
{
	for (int i = 0; i < wl.size(); ++i) {
		cout << wl[i] << ", ";
	}
	cout << endl;
}

void
testVkWidgetList(Widget, XtPointer cd, XtPointer)
{
	VkWindow* win = (VkWindow*)cd;
	Slider* s1 = new Slider("s1", win->mainWindowWidget());
	Slider* s2 = new Slider("s2", win->mainWindowWidget());
	Slider* s3 = new Slider("s3", win->mainWindowWidget());
	Slider* s4 = new Slider("s4", win->mainWindowWidget());
	Slider* s5 = new Slider("s5", win->mainWindowWidget());

	VkWidgetList cl;
	cl.add(s1);
	cl.add(s2);
	cl.add(s3);
	cl.add(s4);
	cl.add(s5);
	cout << "add(s1); add(s2); add(s3); add(s4); add(s5);" << endl;
	cout << "s1, s2, s3, s4, s5" << endl;
	printWidgetList(cl);

	cl.add(s2);
	cl.add(s3);
	cl.add(s3);
	cl.add(s4);
	cout << "add(s2); add(s3); add(s3); add(s4);" << endl;
	cout << "s1, s2, s3, s4, s5, s2, s3, s3, s4" << endl;
	printWidgetList(cl);


	cl.remove(s3);
	cout << "remove(s3);" << endl;
	cout << "s1, s2, s4, s5, s2, s4" << endl;
	printWidgetList(cl);

	cl.removeFirst();
	cout << "removeFirst();" << endl;
	cout << "s2, s4, s5, s2, s4" << endl;
	printWidgetList(cl);

	cl.removeLast();
	cout << "removeLast();" << endl;
	cout << "s2, s4, s5, s2" << endl;
	printWidgetList(cl);


	cout << "List size (4) " << cl.size() << endl;

	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
}
