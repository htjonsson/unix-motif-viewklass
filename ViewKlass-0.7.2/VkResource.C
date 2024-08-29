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
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

/**
 * 
 * VkResource.C
 *
 * This file contains the implementation of the non member function
 * VkGetResource.
 *
 * Chris Toshok
 * Copyright (C) 1994
 * The Hungry Programmers, Inc
 *
 **/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: VkResource.C,v 1.12 2009/03/21 11:44:34 jostle Exp $";

#include <cstring>

#include <Vk/VkApp.h>
#include <Vk/VkResource.h>

using namespace std;

char *
VkGetResource(const char *name, const char *className)
{
	return (char*)VkGetResource(theApplication->baseWidget(), name, className,
								XmRString, NULL);
}

XtPointer
VkGetResource(Widget w, const char *name, const char *className,
			  const char *desiredType, const char *defaultValue)
{
	XtPointer retVal = 0;
	char *result_type1;
	XrmValue result_value;
	result_value.size = 0;
	result_value.addr = 0;
	bool useDefault = false;

	// Make sure the caller provides a sensible widget
	if (w == 0) {
		// but do something sensible if they don't
		useDefault = true;
	} else {
		Widget current = w;

		// Build the fully qualified resource name
		string fullyQual = XtName(current);

		while (current != theApplication->baseWidget()) {
			fullyQual = "." + fullyQual;
			current = XtParent(current);
			fullyQual = XtName(current) + fullyQual;
		}
		fullyQual = "." + fullyQual;
		fullyQual = theApplication->applicationClassName() + fullyQual;
		string fullName = fullyQual;
		if(name[0] != '.' && name[0] != '*')
			fullName += ".";
		fullName += name;
		string fullClass = fullyQual;
		if(className[0] != '.' && className[0] != '*')
			fullClass += ".";
		fullClass += className;
		if (!XrmGetResource(XtDatabase(XtDisplayOfObject(w)),
							(char*)fullName.c_str(),
							(char*)fullClass.c_str(),
							&result_type1, &result_value)) {
			useDefault = true;
		}
	}
	
	if (useDefault && defaultValue != 0) {
		result_type1 = XmRString;
		result_value.size = strlen(defaultValue) + 1;
		result_value.addr = const_cast<char*>(defaultValue);
	}
	
	if (result_value.addr != 0) {
		XrmValue real_result;
		real_result.size = 0;
		real_result.addr = 0;
		
		if (XtConvertAndStore(w, (String)result_type1, &result_value,
							  (String)desiredType, &real_result)) {

  			if (strcmp(desiredType, XmRString) == 0) {
				// When getting a String we are returned the actual
				// pointer to the String, just cast and return. Also
				// the real_result.size is the length of the String
				// (including the terminating NULL) and so could match
				// any of the following tests.
  				retVal =
					reinterpret_cast<XtPointer>(real_result.addr);
  			} else if (real_result.size > sizeof(XtPointer)) {
				// Error : Can't return a type which is larger than
				// the declared return type of this function.
				XtAppWarning(
					theApplication->appContext(),
					"VkGetResource: Attempt to return a type"
					" which is larger than XtPointer.");
				retVal = 0;
			} else {
				// Check the size of the result and cast it
				// appropriately. I don't think it matters that some
				// of the types have equal sizes. The cast will just
				// place the correct number of bits into retVal.
				// e.g. If int and float have the same size
				// then a float desiredType will actually match in
				// the test for int and be assigned using the
				// (*(int*)real_result.addr) cast.
				if (real_result.size == sizeof(char)) {
					retVal = reinterpret_cast<XtPointer>
						(*(char*)real_result.addr);
				} else if (real_result.size == sizeof(short int)) {
					retVal = reinterpret_cast<XtPointer>
						(*(short int*)real_result.addr);
				} else if (real_result.size == sizeof(int)) {
					retVal = reinterpret_cast<XtPointer>
						(*(int*)real_result.addr);
				} else if (real_result.size == sizeof(long int)) {
					retVal = reinterpret_cast<XtPointer>
						(*(long int*)real_result.addr);
				} else if (real_result.size == sizeof(long long int)) {
					retVal = reinterpret_cast<XtPointer>
						(*(long long int*)real_result.addr);
				} else if (real_result.size == sizeof(float)) {
					// Can't reinterpret_cast a float or double to a void*
					// Use memcpy instead, assuming that the caller will
					// also have to use memcpy and, therefore, end up
					// with the right answer.
					// This code is unlikely to be executed in any case
					// as one of the previous conditions will have been
					// met i.e. sizeof(float) == sizeof(int) and
					// sizeof(double) > sizeof(XtPointer)
					memcpy(&retVal, &real_result.addr, sizeof(float));
				} else if (real_result.size == sizeof(double)) {
					memcpy(&retVal, &real_result.addr, sizeof(double));
				} else if (real_result.size == sizeof(long double)) {
					memcpy(&retVal, &real_result.addr, sizeof(long double));
				} else if (real_result.size == sizeof(void*)) {
					retVal = reinterpret_cast<XtPointer>
						(*(void**)real_result.addr);
				}				
			}
		}
	}
	return retVal;
}
