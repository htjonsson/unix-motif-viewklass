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
 * $Id: VkSimpleWindow.h,v 1.5 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class definition for the VkSimpleWindow class.
 * This class is used for simple window stuff (I guess :)).
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKSIMPLEWINDOW_H
#define VKSIMPLEWINDOW_H

#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>
#include <Xm/MainW.h>

class VkSimpleWindow : public VkComponent {

	friend class VkApp;
	
public:
    VkSimpleWindow(const char *name,
		   ArgList args = NULL,
		   Cardinal argCount = 0);

    virtual ~VkSimpleWindow();

    virtual const char *className() { return "VkSimpleWindow"; }
  
    void addView(Widget w);
    void addView(VkComponent *component);
    void removeView();

    virtual void show();
    virtual void hide();
    virtual void iconify();
    virtual void open();
    virtual void raise();
    virtual void lower();

// Window Data Access  Functions

    Boolean visible() const;
    Boolean iconic() const;

    virtual Widget mainWindowWidget() const;
    virtual Widget viewWidget() const;
	// NYI virtual operator Widget() const;

	// Returns IconicState, NormalState,
	//   WithdrawnIconicState or WithdrawnNormalState
	// IconicState and NormalState are #defined in Xutil.h
	// WithdrawnIconicState and WithdrawnNormalState are #defined below
	int getVisualState();
#define WithdrawnIconicState (IconicState & 0x80)
#define WithdrawnNormalState (NormalState & 0x80)

	static VkSimpleWindow* getWindow(VkComponent* component);

// Window Manager Stuff

    void setTitle(const char *newTitle);
    const char *getTitle();
    void setIconName(const char *newTitle);
	// NYI void setClassHint(const char *className);

// This doesn't exist in SGI's vk, but it was easy.
    void setIconPixmap(Pixmap pix);

// Properties and Shell Resources

protected:

	typedef enum {OPEN, CLOSED, ICON_UNKNOWN} IconState;
	typedef enum {VISIBLE, HIDDEN, VISIBLE_UNKNOWN} VisibleState;
	typedef enum {RAISED, LOWERED, STACKING_UNKNOWN} StackingState;

    virtual void setUpWindowProperties();
    virtual void stateChanged(IconState newState);
    virtual void handleWMDeleteMessage();
    virtual void handleWMQuitMessage();
    virtual void handleRawEvent(XEvent *event);
    virtual void afterRealizeHook();

    virtual Widget setUpInterface(Widget) { return (Widget)NULL; };

    Widget _currentView;
    IconState _iconState;
    VisibleState _visibleState;
    StackingState _stackingState;

    Widget _mainWindowWidget;

private:
    char *_windowTitle;
    char *_iconName;

    static void wm_delete_window(Widget w, XtPointer clientData,
								 XtPointer callData);
    static void wm_quit_app(Widget w, XtPointer clientData,
							XtPointer callData);
    static void change_state_handler(Widget w, XtPointer clientData,
									 XEvent *event, Boolean *);

    void changeState(XEvent *event);
};

#endif /* VKSIMPLEWINDOW_H */

