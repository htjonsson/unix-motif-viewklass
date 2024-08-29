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
	= "$Id: VkTrace.C,v 1.6 2009/03/21 11:44:34 jostle Exp $";

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include <Vk/VkTrace.h>

using namespace std;

ofstream* vkTraceOut = 0;

time_t vkLastMark = 0;

bool vkTraceEnable = false;
bool vkTraceDetailEnable = false;
bool vkTraceMessageEnable = false;
bool vkTraceMessageArgsEnable = false;

void
VkTraceOpen(const char* filename)
{
	// NOTE : The following may cause a memory leak. As there
	// is no VkTraceClose function documented in the SGI man pages,
	// there is no way to delete this ofstream.
	vkTraceOut = new ofstream(filename);
	
	time_t now;
	time(&now);
	vkLastMark = now;
}

void
VkTrace(const char* msg)
{
	if (vkTraceEnable) {
		time_t now;
		time(&now);
		char* timeStr = ctime(&now);
		timeStr[strlen(timeStr) - 1] = '\0';
		*vkTraceOut << timeStr << " : " << msg << endl;
	}
}

void
VkTrace2(const char* msg, const char* msg2)
{
	if (vkTraceEnable) {
		time_t now;
		time(&now);
		char* timeStr = ctime(&now);
		timeStr[strlen(timeStr) - 1] = '\0';
		*vkTraceOut << timeStr << " : " << msg << " - " << msg2 << endl;
	}
}

void
VkTracev(const char* msg, const char* format, ...)
{
	if (vkTraceEnable) {
		time_t now;
		time(&now);
		char* timeStr = ctime(&now);
		timeStr[strlen(timeStr) - 1] = '\0';

		va_list ap;
		char temp[BUFSIZ];
		temp[0] = 0;
		va_start(ap, format);
		vsprintf(temp, format, ap);
		va_end(ap);

		*vkTraceOut << timeStr << " : "
					<< msg << " - " << temp << endl;
	}
}

void
VkTraceDetail(const char* msg)
{
	if (vkTraceDetailEnable) {
		*vkTraceOut << msg << endl;
	}
}

void
VkTraceDetail2(const char* msg, const char* msg2)
{
	if (vkTraceDetailEnable) {
		*vkTraceOut << msg << " - " << msg2 << endl;
	}
}

void
VkTraceDetailv(const char* msg, const char* format, ...)
{
	if (vkTraceDetailEnable) {

		va_list ap;
		char temp[BUFSIZ];
		temp[0] = 0;
		va_start(ap, format);
		vsprintf(temp, format, ap);
		va_end(ap);

		*vkTraceOut << msg << " - " << temp << endl;
	}
}

void
VkTraceMark(const char* msg)
{
	if (vkTraceEnable) {
		time_t now;
		time(&now);
		char* timeStr = ctime(&now);
		timeStr[strlen(timeStr) - 1] = '\0';
		time_t elapsed = now - vkLastMark;
		vkLastMark = now;
		*vkTraceOut << timeStr << " (" << elapsed << "s)" << " : "
					<< msg << endl;
	}
}

void
VkTraceMark2(const char* msg, const char* msg2)
{
	if (vkTraceEnable) {
		time_t now;
		time(&now);
		char* timeStr = ctime(&now);
		timeStr[strlen(timeStr) - 1] = '\0';
		time_t elapsed = now - vkLastMark;
		vkLastMark = now;
		*vkTraceOut << elapsed << " > " << timeStr << " : "
					<< msg << " - " << msg2 << endl;
	}
}

void
VkTraceMarkv(const char* msg, const char* format, ...)
{
	if (vkTraceEnable) {
		time_t now;
		time(&now);
		char* timeStr = ctime(&now);
		timeStr[strlen(timeStr) - 1] = '\0';
		time_t elapsed = now - vkLastMark;
		vkLastMark = now;

		va_list ap;
		char temp[BUFSIZ];
		temp[0] = 0;
		va_start(ap, format);
		vsprintf(temp, format, ap);
		va_end(ap);

		*vkTraceOut << timeStr << " (" << elapsed << "s)" << " : "
					<< msg << " - " << temp << endl;
	}
}

