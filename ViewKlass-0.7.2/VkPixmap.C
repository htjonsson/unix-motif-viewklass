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
 * This module by Ed Hanway (HanwayE@thmulti.com)
 **/

// headers for stat function
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

using namespace std;

#include <Vk/VkPixmap.h>
#include <Xm/Label.h>
#include <Vk/VkResource.h>

void
BuildXpmAttributes(Widget w,
                   XpmAttributes* attributes,
                   XpmColorSymbol* syms,
                   const char* const* resources,
                   int numResources)
{
    // Get the standard colours from the widget.
    Pixel fg, bg, ts, bs;
    XtVaGetValues(w, XmNforeground, &fg,
                  XmNbackground, &bg,
                  XmNtopShadowColor, &ts,
                  XmNbottomShadowColor, &bs,
                  NULL);

    // Set the standard colours first.
    syms[0].name = const_cast<char*>("background");
    syms[0].value = NULL;
    syms[0].pixel = bg;

    syms[1].name = const_cast<char*>("foreground");
    syms[1].value = NULL;
    syms[1].pixel = fg;

    syms[2].name = const_cast<char*>("topShadowColor");
    syms[2].value = NULL;
    syms[2].pixel = ts;

    syms[3].name = const_cast<char*>("bottomShadowColor");
    syms[3].value = NULL;
    syms[3].pixel = bs;

    // Now set the extra colours from their resource values.
    int numSet = 0;
    for (int r = 0; r < numResources; ++r) {
        // First test whether the resource has been set at all
        // by trying to retrieve it as a String. If this returns
        // zero (the default) then it has not been set.
        // Note that we can't use the retrieved Pixel for this test
        // as it is quite likely that zero will be the value which
        // has been set for the resource.
        char* test = (char*)VkGetResource(w, resources[r],
                                          XmCForeground, XmRString, 0);
        // If the resource has been set add a colour symbol to the
        // xpm attributes. Otherwise it will remain the colour
        // defined in the xpm file.
        if (test != 0) {
            syms[4 + numSet].name = const_cast<char*>(resources[r]);
            syms[4 + numSet].value = NULL;
            // If the resource has been set to an invalid colour
            // X will issue a warning and VkGetResource will return zero.
            syms[4 + numSet].pixel =
                (Pixel)VkGetResource(w, resources[r],
                                     XmCForeground, XmRPixel,
                                     "unused");
            ++numSet;
        }
    }       

    attributes->colorsymbols = syms;
    attributes->numsymbols = 4 + numSet;
    attributes->valuemask = XpmColorSymbols;

}

Pixmap
VkCreateXPMPixmap(Widget w,
                  const char** xpmPixmapDesc,
                  const char** resources)
{
    if(!XtIsWidget(w)) {
        cerr << "VkCreateXPMPixmap: Widget required (not gadget)" << endl;
        return 0;
    }
    
    // Count the extra resource set colours.
    int numResources = 0;
    if (resources != 0) {
        while (resources[numResources] != NULL) {
            numResources++;
        }
    }
    
    // Create the colour symbol array.
    XpmColorSymbol* syms = new XpmColorSymbol[4 + numResources];

    XpmAttributes attributes;

    BuildXpmAttributes(w, &attributes, syms, resources, numResources);

    Pixmap pixmap = 0;
    XpmCreatePixmapFromData(XtDisplay(w), XRootWindowOfScreen(XtScreen(w)),
                            const_cast<char**>(xpmPixmapDesc),
                            &pixmap, NULL, &attributes);

    delete [] syms;
    
    return pixmap;
}

Pixmap
VkCreateXPMPixmap(Widget w,
                  const char* xpmBufferOrFile,
                  const char** resources)
{
    if(!XtIsWidget(w)) {
        cerr << "VkCreateXPMPixmap: Widget required (not gadget)" << endl;
        return 0;
    }
    
    // Count the extra resource set colours.
    int numResources = 0;
    if (resources != 0) {
        while (resources[numResources] != NULL) {
            numResources++;
        }
    }
    
    // Create the colour symbol array.
    XpmColorSymbol* syms = new XpmColorSymbol[4 + numResources];

    XpmAttributes attributes;

    BuildXpmAttributes(w, &attributes, syms, resources, numResources);

    // Check if we have a valid filename
    struct stat filestat;
    int status = stat(xpmBufferOrFile, &filestat);
    
    Pixmap pixmap = 0;
    if (status == 0) {
        status = XpmReadFileToPixmap(XtDisplay(w),
                                     XRootWindowOfScreen(XtScreen(w)),
                                     const_cast<char*>(xpmBufferOrFile),
                                     &pixmap, NULL, &attributes);
    } else {
        // must not have been a valid filename
        status = XpmCreatePixmapFromBuffer(XtDisplay(w),
                                           XRootWindowOfScreen(XtScreen(w)),
                                           const_cast<char*>(xpmBufferOrFile),
                                           &pixmap, NULL, &attributes);
    }
    
    delete [] syms;
    
    return pixmap;
}

void
VkSetHighlightingPixmap(Widget w,
                        const char** xpmPixmapDesc,
                        const char* resource)
{
    Pixmap p = VkCreateXPMPixmap(w, xpmPixmapDesc);
    if (p) {
        XtVaSetValues(w, XmNlabelType, XmPIXMAP, XmNlabelPixmap, p, NULL);
    }
}

void
VkSetHighlightingPixmap(Widget w,
                        const char* xpmBufferOrFile,
                        const char* resource)
{
    Pixmap p = VkCreateXPMPixmap(w, xpmBufferOrFile);
    if (p) {
        XtVaSetValues(w, XmNlabelType, XmPIXMAP, XmNlabelPixmap, p, NULL);
    } 
}

void
VkSetHighlightingPixmap(Widget w,
                        const char** xpmPixmapDesc,
                        const char** xpmInsensitivePixmapDesc,
                        const char* resource)
{
    Pixmap p = VkCreateXPMPixmap(w, xpmPixmapDesc);
    if (p) {
        XtVaSetValues(w, XmNlabelType, XmPIXMAP, XmNlabelPixmap, p, NULL);
    } 
    Pixmap pi = VkCreateXPMPixmap(w, xpmInsensitivePixmapDesc);
    if (pi) {
        XtVaSetValues(w,
                      XmNlabelType, XmPIXMAP,
                      XmNlabelInsensitivePixmap, pi,
                      NULL);
    } 
}

void
VkSetHighlightingPixmap(Widget w,
                        const char* xpmBufferOrFile,
                        const char* xpmInsensitiveBufferOrFile,
                        const char* resource)
{
    Pixmap p = VkCreateXPMPixmap(w, xpmBufferOrFile);
    if (p) {
        XtVaSetValues(w, XmNlabelType, XmPIXMAP, XmNlabelPixmap, p, NULL);
    } 
    Pixmap pi = VkCreateXPMPixmap(w, xpmInsensitiveBufferOrFile);
    if (pi) {
        XtVaSetValues(w,
                      XmNlabelType, XmPIXMAP,
                      XmNlabelInsensitivePixmap, pi,
                      NULL);
    } 
}
