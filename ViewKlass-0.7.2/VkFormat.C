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
 * VkFormat.C
 *
 * This file contains the implementation for
 * The VkFormat function, which is mainly just
 * a souped up sprintf which gives you the ability
 * to use viewkit things in the format string.
 *
 * Also, my first function _ever_ to use stdargs.  neat.
 *
 * Chris Toshok
 * Copyright (C) 1994, 1995
 * The Hungry Programmers, Inc.
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: VkFormat.C,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <cstdlib>

#include <Vk/VkFormat.h>
#include <Vk/VkApp.h>
#include <stdarg.h>
#include <stdio.h>

using namespace std;

extern "C" {

	const char *
	VkFormat (const char *fmt, ...)
	{
		va_list ap;
		static char *ret_value;

		if (!ret_value) {
			ret_value = (char*)malloc(BUFSIZ * sizeof(char));
		}
		ret_value[0] = 0;

		const char *less_than;
		const char *old_less_than;
		char temp[BUFSIZ];

		temp[0] = 0;

		va_start(ap, fmt);

		old_less_than = &(fmt[0]);
		less_than = &(fmt[0]);
	
		while ((less_than = strchr(old_less_than, (int)'<'))) {
			strncat(temp, old_less_than, (less_than - old_less_than));

			if (!strncmp(less_than, "<application>", strlen("<application>"))){
				strcat(temp, theApplication->applicationClassName());
				old_less_than = less_than + strlen("<application>");
			} else {
				strcat(temp, "<");
				old_less_than = less_than + 1;
			}
		}

		strcat(temp, old_less_than);
		vsprintf(ret_value, temp, ap);
		va_end(ap);

		return ret_value;
	}

};

