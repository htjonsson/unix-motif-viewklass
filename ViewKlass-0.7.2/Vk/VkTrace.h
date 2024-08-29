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
#include <fstream>

#ifndef VKTRACE_H
#define VKTRACE_H


void VkTraceOpen(const char* filename);
void VkTrace(const char* msg);
void VkTrace2(const char* msg, const char* msg2);
void VkTracev(const char* msg, const char* format, ...);
void VkTraceDetail(const char* msg);
void VkTraceDetail2(const char* msg, const char* msg2);
void VkTraceDetailv(const char* msg, const char* format, ...);
void VkTraceMark(const char* msg);
void VkTraceMark2(const char* msg, const char* msg2);
void VkTraceMarkv(const char* msg, const char* format, ...);


//  extern ofstream* vkTraceOut;

//  extern time_t vkLastMark;

extern bool vkTraceEnable;
extern bool vkTraceDetailEnable;
extern bool vkTraceMessageEnable;
extern bool vkTraceMessageArgsEnable;

#endif /* VKTRACE_H */
