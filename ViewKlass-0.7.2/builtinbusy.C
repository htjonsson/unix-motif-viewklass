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
 * builtinbusy.C
 *
 * This file contains the implementation of the built-in busy cursor
 *
 * Chris Toshok
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
= "$Id: builtinbusy.C,v 1.10 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/builtinbusy.h>

using namespace std;

BuiltInBusyCursor::BuiltInBusyCursor() : VkCursorList (NUMCURSORS)
{
	xcolors[0].pixel =
		(Pixel) VkGetResource(theApplication->baseWidget(),
							  "busyCursorForeground",
							  XmCForeground,
							  XmRPixel,
							  "Black");

	xcolors[1].pixel =
		(Pixel) VkGetResource(theApplication->baseWidget(),
							  "busyCursorBackground",
							  XmCBackground,
							  XmRPixel,
							  "White");

	XQueryColors(theApplication->display(),
				 DefaultColormapOfScreen(DefaultScreenOfDisplay(
					 theApplication->display())),
				 xcolors, 2);
}

void
BuiltInBusyCursor::createCursor(int indx)
{
	Pixmap pixmap = 0, maskPixmap = 0;

	Display *dpy = theApplication->display();

	pixmap = XCreateBitmapFromData(dpy,
								   DefaultRootWindow(dpy),
								   (const char*)clock_bits[indx*2],
								   CURSOR_WIDTH, CURSOR_HEIGHT);

	maskPixmap = XCreateBitmapFromData(dpy,
									   DefaultRootWindow(dpy),
									   (const char*)clock_bits[indx*2+1],
									   CURSOR_WIDTH, CURSOR_HEIGHT);

	_cursorList[indx] = XCreatePixmapCursor(dpy, pixmap, maskPixmap,
                                            &(xcolors[0]), &(xcolors[1]),
                                            0,0);

	if (pixmap)	XFreePixmap(dpy, pixmap);
	if (maskPixmap)	XFreePixmap(dpy, maskPixmap);
}

