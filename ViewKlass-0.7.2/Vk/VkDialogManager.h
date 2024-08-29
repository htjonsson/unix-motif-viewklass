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
 * $Id: VkDialogManager.h,v 1.15 2009/03/21 11:44:34 jostle Exp $
 *
 * This file contains the C++ class definition for the abstract class
 * of dialog managers, from which all other dialog managers are
 * derived.  The user shood have no need to make use of this class,
 * except to derive new instances of dialog from it.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKDIALOGMANAGER_H
#define VKDIALOGMANAGER_H

#include <string>

#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/SelectioB.h>
#include <Xm/DialogS.h>
#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>
#include <Vk/VkResource.h>
#include <Vk/VkSimpleWindow.h>

class VkDialogManager : public VkComponent {
public:
    typedef enum {OK, APPLY, CANCEL} VkDialogReason;

	virtual ~VkDialogManager();

    // posting non-modal dialogs.

    virtual Widget post(const char *msg = NULL,
						XtCallbackProc okCB = NULL,
						XtCallbackProc cancelCB = NULL,
						XtCallbackProc applyCB = NULL,
						XtPointer clientData = NULL,
						const char *helpString = NULL,
						VkSimpleWindow *parent = NULL,
						Widget parentWidget = NULL);

    Widget post(const char *msg,
				VkSimpleWindow *parent)
			{ return post(msg, NULL, NULL, NULL,
						  NULL, NULL, parent, NULL); }
	
    Widget post(const char *msg,
				const char *helpString,
				VkSimpleWindow *parent = NULL)
			{ return post(msg, NULL, NULL, NULL,
						  NULL, helpString, parent, NULL); }
	
    Widget post(const char *msg,
				XtCallbackProc okCB,
				XtPointer clientData,
				VkSimpleWindow *parent = NULL)
			{ return post(msg, okCB, NULL, NULL,
						  clientData, NULL, parent, NULL); }
	
    Widget post(const char *msg,
				XtCallbackProc okCB,
				XtPointer clientData,
				const char *helpString,
				VkSimpleWindow *parent = NULL)
			{ return post(msg, okCB, NULL, NULL,
						  clientData, helpString, parent, NULL); }
	
    Widget post(const char *msg,
				XtCallbackProc okCB,
				XtCallbackProc cancelCB,
				XtPointer clientData,
				char *helpString,
				VkSimpleWindow *parent = NULL)
			{ return post(msg, okCB, cancelCB, NULL,
						  clientData, helpString, parent, NULL); }
	
    Widget post(const char *msg,
				XtCallbackProc okCB,
				XtCallbackProc cancelCB,
				XtCallbackProc applyCB,
				XtPointer clientData,
				VkSimpleWindow *parent = NULL)
			{ return post(msg, okCB, cancelCB, applyCB,
						  clientData, NULL, parent, NULL); }

    Widget post(const char *msg,
				 Widget parent)
			{ return post(msg, NULL, NULL, NULL,
						  NULL, NULL, NULL, parent); }

    Widget post(const char *msg,
				 const char *helpString,
				 Widget parent)
			{ return post(msg, NULL, NULL, NULL,
						  NULL, helpString, NULL, parent); }

    Widget post(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 Widget parent)
			{ return post(msg, okCB, NULL, NULL,
						  clientData, NULL, NULL, parent); }

    Widget post(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 const char *helpString,
				 Widget parent)
			{ return post(msg, okCB, NULL, NULL,
						  clientData, helpString, NULL, parent); }

    Widget post(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 Widget parent)
			{ return post(msg, okCB, cancelCB, NULL,
						  clientData, NULL, NULL, parent); }

    Widget post(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 char *helpString,
				 Widget parent)
			{ return post(msg, okCB, cancelCB, NULL,
						  clientData, helpString, NULL, parent); }

    Widget post(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtCallbackProc applyCB,
				 XtPointer clientData,
				 Widget parent)
			{ return post(msg, okCB, cancelCB, applyCB,
						  clientData, NULL, NULL, parent); }

    // posting modal dialogs

    virtual Widget postModal(const char *msg = NULL,
							 XtCallbackProc okCB = NULL,
							 XtCallbackProc cancelCB = NULL,
							 XtCallbackProc applyCB = NULL,
							 XtPointer clientData = NULL,
							 const char *helpString = NULL,
							 VkSimpleWindow *parent = NULL,
							 Widget parentWidget = NULL);

    Widget postModal(const char *msg,
				 VkSimpleWindow *parent)
			{ return postModal(msg, NULL, NULL, NULL,
						  NULL, NULL, parent, NULL); }

    Widget postModal(const char *msg,
				 const char *helpString,
				 VkSimpleWindow *parent = NULL)
			{ return postModal(msg, NULL, NULL, NULL,
						  NULL, helpString, parent, NULL); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 VkSimpleWindow *parent = NULL)
			{ return postModal(msg, okCB, NULL, NULL,
						  clientData, NULL, parent, NULL); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 const char *helpString,
				 VkSimpleWindow *parent = NULL)
			{ return postModal(msg, okCB, NULL, NULL,
						  clientData, helpString, parent, NULL); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 char *helpString,
				 VkSimpleWindow *parent = NULL)
			{ return postModal(msg, okCB, cancelCB, NULL,
						  clientData, helpString, parent, NULL); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtCallbackProc applyCB,
				 XtPointer clientData,
				 VkSimpleWindow *parent = NULL)
			{ return postModal(msg, okCB, cancelCB, applyCB,
						  clientData, NULL, parent, NULL); }

    Widget postModal(const char *msg,
				 Widget parent)
			{ return postModal(msg, NULL, NULL, NULL,
						  NULL, NULL, NULL, parent); }

    Widget postModal(const char *msg,
				 const char *helpString,
				 Widget parent)
			{ return postModal(msg, NULL, NULL, NULL,
						  NULL, helpString, NULL, parent); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 Widget parent)
			{ return postModal(msg, okCB, NULL, NULL,
						  clientData, NULL, NULL, parent); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 const char *helpString,
				 Widget parent)
			{ return postModal(msg, okCB, NULL, NULL,
						  clientData, helpString, NULL, parent); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 Widget parent)
			{ return postModal(msg, okCB, cancelCB, NULL,
						  clientData, NULL, NULL, parent); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 char *helpString,
				 Widget parent)
			{ return postModal(msg, okCB, cancelCB, NULL,
						  clientData, helpString, NULL, parent); }

    Widget postModal(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtCallbackProc applyCB,
				 XtPointer clientData,
				 Widget parent)
			{ return postModal(msg, okCB, cancelCB, applyCB,
						  clientData, NULL, NULL, parent); }


    virtual Widget postBlocked(const char *msg = NULL,
							   XtCallbackProc okCB = NULL,
							   XtCallbackProc cancelCB = NULL,
							   XtCallbackProc applyCB = NULL,
							   XtPointer clientData = NULL,
							   const char *helpString = NULL,
							   VkSimpleWindow *parent = NULL,
							   Widget parentWidget = NULL);

    Widget postBlocked(const char *msg,
				 VkSimpleWindow *parent)
			{ return postBlocked(msg, NULL, NULL, NULL,
						  NULL, NULL, parent, NULL); }

    Widget postBlocked(const char *msg,
				 const char *helpString,
				 VkSimpleWindow *parent = NULL)
			{ return postBlocked(msg, NULL, NULL, NULL,
						  NULL, helpString, parent, NULL); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 VkSimpleWindow *parent = NULL)
			{ return postBlocked(msg, okCB, NULL, NULL,
						  clientData, NULL, parent, NULL); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 const char *helpString,
				 VkSimpleWindow *parent = NULL)
			{ return postBlocked(msg, okCB, NULL, NULL,
						  clientData, helpString, parent, NULL); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 char *helpString,
				 VkSimpleWindow *parent = NULL)
			{ return postBlocked(msg, okCB, cancelCB, NULL,
						  clientData, helpString, parent, NULL); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtCallbackProc applyCB,
				 XtPointer clientData,
				 VkSimpleWindow *parent = NULL)
			{ return postBlocked(msg, okCB, cancelCB, applyCB,
						  clientData, NULL, parent, NULL); }

    Widget postBlocked(const char *msg,
				 Widget parent)
			{ return postBlocked(msg, NULL, NULL, NULL,
						  NULL, NULL, NULL, parent); }

    Widget postBlocked(const char *msg,
				 const char *helpString,
				 Widget parent)
			{ return postBlocked(msg, NULL, NULL, NULL,
						  NULL, helpString, NULL, parent); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 Widget parent)
			{ return postBlocked(msg, okCB, NULL, NULL,
						  clientData, NULL, NULL, parent); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtPointer clientData,
				 const char *helpString,
				 Widget parent)
			{ return postBlocked(msg, okCB, NULL, NULL,
						  clientData, helpString, NULL, parent); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 Widget parent)
			{ return postBlocked(msg, okCB, cancelCB, NULL,
						  clientData, NULL, NULL, parent); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtPointer clientData,
				 char *helpString,
				 Widget parent)
			{ return postBlocked(msg, okCB, cancelCB, NULL,
						  clientData, helpString, NULL, parent); }

    Widget postBlocked(const char *msg,
				 XtCallbackProc okCB,
				 XtCallbackProc cancelCB,
				 XtCallbackProc applyCB,
				 XtPointer clientData,
				 Widget parent)
			{ return postBlocked(msg, okCB, cancelCB, applyCB,
						  clientData, NULL, NULL, parent); }


    virtual VkDialogReason postAndWait(const char *msg = NULL,
									   Boolean ok = TRUE,
									   Boolean cancel = TRUE,
									   Boolean apply = FALSE,
									   const char *helpString = NULL,
									   VkSimpleWindow *parent = NULL,
									   Widget parentWidget = NULL);

    VkDialogReason postAndWait(const char *msg,
								VkSimpleWindow *parent)
			{ return postAndWait(msg, TRUE, TRUE, FALSE,
						  NULL, parent, NULL); }

    VkDialogReason postAndWait(const char *msg,
								const char *helpString,
								VkSimpleWindow *parent = NULL)
			{ return postAndWait(msg, TRUE, TRUE, FALSE,
						  NULL, parent, NULL); }

    VkDialogReason postAndWait(const char *msg,
								Widget parent)
			{ return postAndWait(msg, TRUE, TRUE, FALSE,
						  NULL, NULL, parent); }

    VkDialogReason postAndWait(const char *msg,
								const char *helpString,
								Widget parent)
			{ return postAndWait(msg, TRUE, TRUE, FALSE,
						  NULL, NULL, parent); }


    virtual const char *className() = 0;

    void setTitle(const char *nextTitle = NULL);
    void setButtonLabels(const char *okLabel = NULL,
                         const char *cancelLabel = NULL,
                         const char *applyLabel = NULL);

    void centerOnScreen(Boolean flag);

	// NYI
//  	void enableCancelButton(Boolean enable)

    Widget lastPosted();

    void unpost();
    void unpost(Widget w);
    void unpostAll();

	// NYI Visual settings
//  	static void useOverlayDialogs(const Boolean flag);
//  	void setArgs(ArgList list, Cardinal argCnt);
//  	void setVisual(VkVisual *v);

protected:
    virtual Widget prepost(const char *msg,
						   XtCallbackProc okCB = NULL,
						   XtCallbackProc cancelCB = NULL,
						   XtCallbackProc applyCB = NULL,
						   XtPointer clientData = NULL,
						   const char *helpString = NULL,
						   VkSimpleWindow *parent = NULL);
    
    Widget prepost(const char *msg,
				   const char *helpString,
				   VkSimpleWindow *parent)
		{ return prepost(msg, NULL, NULL, NULL, NULL, helpString, parent); }

	// Invoked just before a dialog is displayed
	// callData contains the dialog widget
	static const char* const prepostCallback;

    Boolean _allowMultipleDialogs;
    // NYI Boolean _minimizeMultipleDialogs;

    // The constructor is protected simply because it is _never_
	// called by anything other than a subclass
    VkDialogManager(const char *name);

    // This method must be overloaded in subclasses
	// to create the actual dialog box
    virtual Widget createDialog(Widget parent) = 0;

    virtual void ok(Widget dialog, XtPointer) { unpost(dialog); }
    virtual void cancel(Widget dialog, XtPointer) { unpost(dialog); }
    virtual void apply(Widget dialog, XtPointer) { /* do nothing */ }
    virtual void help(Widget dialog, XtPointer);

    String  _dialogShellTitle;
	String  _currentHelpString;
    Boolean _showOK;
    Boolean _showCancel;
    Boolean _showApply;
    Boolean _showHelp;
	
    VkDialogReason _action;

private:
    /* stuff needed for our own event loop */
    Boolean _done_with_event_loop;

    /* stuff for managing the list of dialogs */
    Widget getDialog(Widget parent);
    int cachedDialogFor(Widget parent);
    void addDialog(Widget parent, Widget dialog);

    std::vector<Widget> _dialogs;
    std::vector<Widget> _parents;

    Widget _parentWidget;
	Boolean _centered;

    /* callback functions for when buttons get pressed */
    static void dialogBoxOK(Widget w, XtPointer clientData,
							XtPointer callData);
    static void dialogBoxCANCEL(Widget w, XtPointer clientData,
								XtPointer callData);
    static void dialogBoxAPPLY(Widget w, XtPointer clientData,
							   XtPointer callData);
    static void dialogBoxHELP(Widget w, XtPointer clientData,
							  XtPointer callData);

    void setupWindowManagerProperties(Widget dialog);
    static void handle_wm(Widget w, XtPointer clientData, XtPointer callData);

    std::string* _okLabel;
	std::string* _cancelLabel;
	std::string* _applyLabel;

	static const char* const _defaultResources[];
};


#endif /* VKDIALOGMANAGER_H */
