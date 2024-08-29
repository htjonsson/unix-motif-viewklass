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
 * This module by Ed Hanway (HanwayE@thmulti.com)
 **/

#ifndef VKPIXMAP_H
#define VKPIXMAP_H

#include <Vk/VkConfig.h>
#include <X11/xpm.h>
#include <X11/Intrinsic.h>

Pixmap VkCreateXPMPixmap(Widget w,
                         const char** xpmPixmapDesc,
                         const char** resources = NULL);

Pixmap VkCreateXPMPixmap(Widget w,
                         const char* xpmBufferOrFile,
                         const char** resources = NULL);

void VkSetHighlightingPixmap(Widget w,
                             const char** xpmPixmapDesc,
                             const char* resource = NULL);

void VkSetHighlightingPixmap(Widget w,
                             const char* xpmBufferOrFile,
                             const char* resource = NULL);

void VkSetHighlightingPixmap(Widget w,
                             const char** xpmPixmapDesc,
                             const char** xpmInsensitivePixmapDesc,
                             const char* resource = NULL);

void VkSetHighlightingPixmap(Widget w,
                             const char* xpmBufferOrFile,
                             const char* xpmInsensitiveBufferOrFile,
                             const char* resource = NULL);

#endif // VKPIXMAP_H
