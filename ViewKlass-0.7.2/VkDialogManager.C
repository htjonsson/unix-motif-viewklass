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
 * VkDialogManager.C
 *
 * This file implements the base, abstract class
 * from which all other VkDialogs are derived.
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
	= "$Id: VkDialogManager.C,v 1.24 2009/03/21 11:44:34 jostle Exp $";

#include <iostream>

using namespace std;

#include <Vk/VkDialogManager.h>
#include <Vk/VkApp.h>
#include <Vk/VkHelpAPI.h>

#include <Xm/AtomMgr.h>
#include <Xm/Protocols.h>

const char* const VkDialogManager::_defaultResources[] = {
	".marginWidth : 4",
	".marginHeight : 4",
	"*XmPushButtonGadget*marginWidth : 1",
	"*XmPushButtonGadget*marginHeight : 1",
	NULL,
};

VkDialogManager::VkDialogManager(const char* name)
	: VkComponent(name),
	  _allowMultipleDialogs(True),
	  _dialogShellTitle(0),
	  _currentHelpString(0),
	  _showOK(True),
	  _showCancel(False),
	  _showApply(False),
	  _showHelp(True),
	  _action(CANCEL),
	  _done_with_event_loop(True),
	  _centered(False),
	  _okLabel(0),
	  _cancelLabel(0),
	  _applyLabel(0)
{
	// Nothing further
}

VkDialogManager::~VkDialogManager()
{
	delete []_currentHelpString;
	_currentHelpString = 0;
	delete []_dialogShellTitle;
	_dialogShellTitle = 0;
	delete []_currentHelpString;
	_currentHelpString = 0;
	delete _okLabel;
	_okLabel = 0;
	delete _cancelLabel;
	_cancelLabel = 0;
	delete _applyLabel;
	_applyLabel = 0;

	
	// Destroy all cached dialog widgets
    for (unsigned int i = 0; i < _dialogs.size(); i++) {
		// The VkComponent destructor will destroy _baseWidget.
		if (_dialogs[i] != _baseWidget) {
			XtDestroyWidget(_dialogs[i]);
			_dialogs[i] = 0;
		}
	}
}

int
VkDialogManager::cachedDialogFor(Widget parent)
{
    for (unsigned int i = 0; i < _dialogs.size(); i++) {
		if (parent == _parents[i] && !XtIsManaged(_dialogs[i])) {
			return 1;
		}
    }
    return 0;
}

Widget
VkDialogManager::getDialog(Widget parent)
{
    for (unsigned int i = 0; i < _dialogs.size(); i++) {
		if (parent == _parents[i] && !XtIsManaged(_dialogs[i])) {
			return _dialogs[i];
		}
	}
	// This can't ever happen (oh yeah?) and should cause the app to crash
	return (Widget)0;
}

void
VkDialogManager::addDialog(Widget parent, Widget dialog)
{
    _parents.push_back(parent);
    _dialogs.push_back(dialog);
}

Widget
VkDialogManager::prepost(const char* msg,
						 XtCallbackProc okCB,
						 XtCallbackProc cancelCB,
						 XtCallbackProc applyCB,
						 XtPointer clientData,
						 const char* helpString,
						 VkSimpleWindow* parent)
{
    Widget w; /* used when managing/unmanaging individual buttons */
    Widget box;
    XmString xmstr;

	////////////////////////////
	//
	// Setting the Parent Widget
	//
	// if posted with 'usable' _parentWidget
	//  parentWidget = _parentWidget
	// else if posted with 'usable' VkSimpleWindow* parent
	//  parentWidget = parent->baseWidget();
	// else if _centered
	//  parentWidget = theApplication->baseWidget();
	// else if theApplication->mainWindow() is 'usable'
	//  parentWidget = theApplication->mainWindow();
	// else
	//  parentWidget = theApplication->baseWidget();
	//
	// where 'usable' means 'visible and not iconified'
	// according to the ViewKit documentation.
	// (for a widgetParent I'll assume visible means managed)

	Widget parentWidget = 0;
	if (_parentWidget) {
		// Only use Shell widgets as parents
		parentWidget = _parentWidget;
		while(!XtIsShell(parentWidget)) {
			parentWidget = XtParent(parentWidget);
		}
		Boolean iconic = False;
		if (XtIsTopLevelShell(parentWidget)) {
			XtVaGetValues(parentWidget, XtNiconic, &iconic, NULL);
		}
		if (iconic || !XtIsManaged(parentWidget)) {
			int state = theApplication->mainWindow()->getVisualState();
			if (state == NormalState) {
				parentWidget = theApplication->mainWindow()->baseWidget();
			} else {
				parentWidget = theApplication->baseWidget();
			}
		}			
	} else if (parent) {
		int state = parent->getVisualState();
		if (state == NormalState) {
			parentWidget = parent->baseWidget();
		} else {
			parentWidget = theApplication->baseWidget();
		}
	} else if (_centered) {
		parentWidget = theApplication->baseWidget();
	} else if (theApplication->mainWindow()) {
		int state = theApplication->mainWindow()->getVisualState();
		if (state == NormalState) {
			parentWidget = theApplication->mainWindow()->baseWidget();
		} else {
			parentWidget = theApplication->baseWidget();
		}
	} else {
		parentWidget = theApplication->baseWidget();
	}

	
	setDefaultResources(parentWidget, _defaultResources);

	if (_allowMultipleDialogs) {
		if (cachedDialogFor(parentWidget)) {
			box = getDialog(parentWidget);
		} else {
			box = createDialog(parentWidget);
			addDialog(parentWidget, box);
		}
	} else {
		if (!_parents.empty()) {
			box = _dialogs[0];
		} else {
			box = createDialog(parentWidget);
			addDialog(parentWidget, box);
		}
	}

    _baseWidget = XtParent(box); // the dialog shell
	installDestroyHandler();

    w = XtNameToWidget(box, "OK");
    if (w) {
		// From the ViewKit Programmers Guide -
		// Note: The arguments that you provide apply only to the dialog posted
		// by the current call to post(),postModal(), and postBlocked(); they
		// have no effect on subsequent dialogs. For example, if you provide an
		// apply callback function to a call to post(), it is used only for the
		// dialog posted by that call. If you want to use that callback for
		// subsequent dialogs, you must provide it as an argument every time
		// you post a dialog.

		XtRemoveAllCallbacks(box, XmNokCallback);

		// Manage the Ok button if an OkCallback has been set
		// or if the user has told us to show it.
		if (_showOK || okCB) {
			XtManageChild(w);
			// Add a user supplied callback.
			if (okCB) {
				XtAddCallback(box, XmNokCallback, okCB, clientData);
			}
			// And put back our standard callback
			XtAddCallback(box, XmNokCallback, dialogBoxOK, this);
		} else {
			if (XtIsManaged(w)) {
				XtUnmanageChild(w);
			}
		}
    }

    if (_okLabel) {
        xmstr = XmStringCreateLocalized(const_cast<char*>(_okLabel->c_str()));
        XtVaSetValues(box, XmNokLabelString, xmstr, NULL);
        delete(_okLabel);
        _okLabel = NULL;
		XmStringFree(xmstr);
    } else {
		XmString xmstr = (XmString)VkGetResource(
			box, "okLabelString", "XmString", "XmString", "OK");
		XtVaSetValues(box, XmNokLabelString, xmstr, NULL);
	}

    w = XtNameToWidget(box, "Cancel");
    if (w) {
		// See Ok button comments above-^
		XtRemoveAllCallbacks(box, XmNcancelCallback);

		if (_showCancel || cancelCB) {
			XtManageChild(w);
			if (cancelCB) {
				XtAddCallback(box, XmNcancelCallback, cancelCB, clientData);
			}
			XtAddCallback(box, XmNcancelCallback, dialogBoxCANCEL, this);
		} else {
			if (XtIsManaged(w)) {
				XtUnmanageChild(w);
			}
		}
    }

    if (_cancelLabel) {
        xmstr = XmStringCreateLocalized(
			const_cast<char*>(_cancelLabel->c_str()));
        XtVaSetValues(box, XmNcancelLabelString, xmstr, NULL);
		delete(_cancelLabel);
		_cancelLabel = NULL;
		XmStringFree(xmstr);
    } else {
		XmString xmstr = (XmString)VkGetResource(
			box, "cancelLabelString", "XmString", "XmString", "Cancel");
		XtVaSetValues(box, XmNcancelLabelString, xmstr, NULL);
	}

    if (XtIsSubclass(box, xmSelectionBoxWidgetClass)) {
		w = XtNameToWidget(box, "Apply");
		if (w) {
			// See Ok button comments above-^
			XtRemoveAllCallbacks(box, XmNapplyCallback);

			if (_showApply || applyCB) {
				XtManageChild(w);
				if (applyCB) {
					XtAddCallback(box, XmNapplyCallback, applyCB, clientData);
				}
				XtAddCallback(box, XmNapplyCallback, dialogBoxAPPLY, this);
			} else {
				if (XtIsManaged(w)) {
					XtUnmanageChild(w);
				}
			}
		}

		if (_applyLabel) {
			xmstr = XmStringCreateLocalized(
				const_cast<char*>(_applyLabel->c_str()));
			XtVaSetValues(box, XmNapplyLabelString, xmstr, NULL);
			delete(_applyLabel);
			_applyLabel = NULL;
			XmStringFree(xmstr);
		} else {
			XmString xmstr = (XmString)VkGetResource(
				box, "applyLabelString", "XmString", "XmString", "Apply");
			XtVaSetValues(box, XmNapplyLabelString, xmstr, NULL);
		}
	}

    w = XtNameToWidget(box, "Help");
    if (w) {
		if (_currentHelpString) {
			delete [] _currentHelpString;
			_currentHelpString = 0;
		}

		// See Ok button comments above-^
		XtRemoveAllCallbacks(box, XmNhelpCallback);

		if (helpString) {
			_currentHelpString = new char[strlen(helpString) + 1];
			strcpy(_currentHelpString, helpString);
			XtManageChild(w);
			XtAddCallback(box, XmNhelpCallback, dialogBoxHELP, this);
		} else {
 			if (XtIsManaged(w)) {
				XtUnmanageChild(w);
			}
		}
	}

    if (_dialogShellTitle) {
		char* title = (char*)VkGetResource(_baseWidget,
										   _dialogShellTitle,
										   _dialogShellTitle,
										   XmRString,
										   _dialogShellTitle);
		XtVaSetValues(_baseWidget, XtNtitle, title, NULL);
    }
	
    if (msg) {
  		XmString xmstr =
			(XmString)VkGetResource(_baseWidget, msg, msg, XmRXmString, msg);
		if (xmstr) {
			XtVaSetValues(box, XmNmessageString, xmstr,
						  XmNselectionLabelString, xmstr,
						  NULL);
        }
    }

    return box;
}

const char* const
VkDialogManager::prepostCallback = "VkDialogManager::prepostCallback";

Widget
VkDialogManager::post(const char* msg,
					  XtCallbackProc okCB,
					  XtCallbackProc cancelCB,
					  XtCallbackProc applyCB,
					  XtPointer clientData,
					  const char* helpString,
					  VkSimpleWindow* parent,
					  Widget parentWidget)
{
    _parentWidget = parentWidget;
    Widget dialogBox = prepost(msg,
							   okCB,
							   cancelCB,
							   applyCB,
							   clientData,
							   helpString,
							   parent);

    /*... there's nothing more to do but manage and return it :)*/

    XtVaSetValues(dialogBox,
				  XmNdialogStyle, XmDIALOG_MODELESS,
				  NULL);

    XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, False,
				  NULL);

    callCallbacks(VkDialogManager::prepostCallback, (void*)dialogBox);

    XtManageChild(dialogBox);

    setupWindowManagerProperties(dialogBox);

	XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, True,
				  NULL);

    XtManageChild(dialogBox);

	// Required for LessTif; their bug or mine? 
	XtManageChild(_baseWidget);

    XmUpdateDisplay(_baseWidget);

    return dialogBox;
}


Widget
VkDialogManager::postModal(const char* msg,
						   XtCallbackProc okCB,
						   XtCallbackProc cancelCB,
						   XtCallbackProc applyCB,
						   XtPointer clientData,
						   const char* helpString,
						   VkSimpleWindow* parent,
						   Widget parentWidget)
{
    _parentWidget = parentWidget;
    Widget dialogBox = prepost(msg,
							   okCB,
							   cancelCB,
							   applyCB,
							   clientData,
							   helpString,
							   parent);

    /*... we set the dialogStyle and manage/return it */

    XtVaSetValues(dialogBox,
				  XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
				  NULL);

    XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, False,
				  NULL);

    callCallbacks(VkDialogManager::prepostCallback, (void*)dialogBox);

    XtManageChild(dialogBox);

	// Required for LessTif; their bug or mine? 
    XtManageChild(_baseWidget);

    setupWindowManagerProperties(dialogBox);

    XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, True,
				  NULL);

    XmUpdateDisplay(_baseWidget);

    return dialogBox;
}

Widget
VkDialogManager::postBlocked(const char* msg,
							 XtCallbackProc okCB,
							 XtCallbackProc cancelCB,
							 XtCallbackProc applyCB,
							 XtPointer clientData,
							 const char* helpString,
							 VkSimpleWindow* parent,
							 Widget parentWidget)
{
    _parentWidget = parentWidget;
    Widget dialogBox = prepost(msg,
							   okCB,
							   cancelCB,
							   applyCB,
							   clientData,
							   helpString,
							   parent);

    /*... we set up our own event loop, and don't return
      until the user presses one of the buttons.  When
      we do return, the value is the widget id. The
      dialog box is again DIALOG_FULL_APPLICATION_MODAL */


    XtVaSetValues(dialogBox,
				  XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
				  NULL);

    _done_with_event_loop = False;

    XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, False,
				  NULL);

    callCallbacks(VkDialogManager::prepostCallback, (void*)dialogBox);

    XtManageChild(dialogBox);

    XtManageChild(_baseWidget);

    setupWindowManagerProperties(dialogBox);

    XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, True,
				  NULL);

    XmUpdateDisplay(_baseWidget);

    while (!_done_with_event_loop) {
		XtAppProcessEvent(theApplication->appContext(), XtIMAll);
	}
	
    return(dialogBox);
}

VkDialogManager::VkDialogReason
VkDialogManager::postAndWait(const char* msg,
							 Boolean ok,
							 Boolean cancel,
							 Boolean apply,
							 const char* helpString,
							 VkSimpleWindow* parent,
							 Widget parentWidget)
{
    _parentWidget = parentWidget;
    Widget dialogBox = prepost(msg,
							   NULL,
							   NULL,
							   NULL,
							   NULL,
							   helpString,
							   parent);

    /*... we set up our own event loop, and don't return
      until the user presses one of the buttons.  When
      we do return, the value is of type VkDialogReason.
      The dialog box is again DIALOG_FULL_APPLICATION_MODAL */

    XtVaSetValues(dialogBox,
				  XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
				  NULL);

    _done_with_event_loop = False;

    XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, False,
				  NULL);

    callCallbacks(VkDialogManager::prepostCallback, (void*)dialogBox);

    XtManageChild(dialogBox);

    XtManageChild(_baseWidget);
	
    setupWindowManagerProperties(dialogBox);

    XtVaSetValues(_baseWidget,
				  XtNmappedWhenManaged, True,
				  NULL);

    XmUpdateDisplay(_baseWidget);

    while (!_done_with_event_loop) {
		XtAppProcessEvent(theApplication->appContext(), XtIMAll);
	}
	
    return _action;
}

void
VkDialogManager::centerOnScreen(Boolean flag)
{
    _centered = flag;
}

void
VkDialogManager::setTitle(const char* nextTitle)
{
	// Check if the string names a resource ...
	char* resourceTitle = VkGetResource(nextTitle, "Title");
	// and if so use the value of the resource as the title.
	if (resourceTitle != 0) {
		nextTitle = resourceTitle;
	}
	delete [] _dialogShellTitle;
	_dialogShellTitle = new char[strlen(nextTitle) + 1];
    strcpy(_dialogShellTitle, nextTitle);
}

void
VkDialogManager::setButtonLabels(const char* okLabel,
                                 const char* cancelLabel,
                                 const char* applyLabel)
{
	Widget top = theApplication->baseWidget();
	
    if (okLabel) {
		char* okString = (char*)VkGetResource(
			top, okLabel, "String", "String", okLabel);
			
		delete _okLabel;
		_okLabel = new string(okString);
	}
	
    if (cancelLabel) {
		char* cancelString = (char*)VkGetResource(
			top, cancelLabel, "String", "String", cancelLabel);
		delete _cancelLabel;
		_cancelLabel = new string(cancelString);
	}
	
    if (applyLabel) {
		char* applyString = (char*)VkGetResource(
			top, applyLabel, "String", "String", applyLabel);
		delete _applyLabel;
		_applyLabel = new string(applyString);
	}
}

Widget
VkDialogManager::lastPosted()
{
    for (int i = _dialogs.size() - 1; i >= 0; i--) {
		if (XtIsManaged(_dialogs[i])) {
			return _dialogs[i];
		}
	}
    return NULL;
}

void
VkDialogManager::unpost()
{
	if (theApplication->traceApplication()) {
		cout << "VkDialogManager::unpost() : There are " << _dialogs.size()
			 << " dialogs currently cached\n" << endl;
	}

    if (lastPosted()) {
		unpost(lastPosted());
	}
}

void
VkDialogManager::unpostAll()
{
    for (unsigned int i = 0; i < _dialogs.size(); i++) {
		unpost(_dialogs[i]);
	}
}

void
VkDialogManager::unpost(Widget w)
{
	if (XtIsTopLevelShell(XtParent(w))) {
		if (XtIsManaged(XtParent(w))) {
			XtUnmanageChild(XtParent(w));
		}
	} else {
		XtUnmanageChild(w);
	}
}

void
VkDialogManager::dialogBoxOK(Widget dialog,
							 XtPointer clientData,
							 XtPointer callData)
{
    VkDialogManager* obj = (VkDialogManager*)clientData;

    /* if we were in our own event loop, quit it */
    obj->_action = VkDialogManager::OK;
    obj->_done_with_event_loop = True;

    obj->ok(dialog, callData);
}

void
VkDialogManager::dialogBoxCANCEL(Widget dialog,
								 XtPointer clientData,
								 XtPointer callData)
{
    VkDialogManager* obj = (VkDialogManager*)clientData;
    /* if we were in our own event loop, quit it */
    obj->_action = VkDialogManager::CANCEL;
    obj->_done_with_event_loop = True;

    obj->cancel(dialog, callData);
}

void
VkDialogManager::dialogBoxAPPLY(Widget dialog,
								XtPointer clientData,
								XtPointer callData)
{
    VkDialogManager* obj = (VkDialogManager*)clientData;
    obj->apply(dialog, callData);
}

void
VkDialogManager::dialogBoxHELP(Widget dialog,
							   XtPointer clientData,
							   XtPointer callData)
{
    VkDialogManager* obj = (VkDialogManager*)clientData;
    obj->help(dialog, callData);
}

void
VkDialogManager::help(Widget dialog, XtPointer clientData)
{
	theApplication->helpMsg(_currentHelpString, NULL, NULL);
}


void
VkDialogManager::setupWindowManagerProperties(Widget dialog)
{
	Widget shell = XtParent(dialog);

	Atom WM_DELETE_WINDOW;
	Atom WM_QUIT_APP;

	WM_DELETE_WINDOW = XmInternAtom(theApplication->display(),
									const_cast<char*>("WM_DELETE_WINDOW"),
                                    False);
	
	WM_QUIT_APP = XmInternAtom(theApplication->display(),
							   const_cast<char*>("_WM_QUIT_APP"), True);

	XmAddWMProtocolCallback(shell, WM_DELETE_WINDOW, handle_wm, this);
}

void
VkDialogManager::handle_wm(Widget w, XtPointer clientData, XtPointer callData)
{
	// The widget parameter is the Shell.
	// We need to pass the MessageBox widget to unpost.
	WidgetList children;
	int numChildren;

	if (XtIsShell(w)) { // Best to be sure.
		XtVaGetValues(w, XmNnumChildren, &numChildren,
					  XmNchildren, &children,
					  NULL);
		if (numChildren == 1) { // Best to be sure.
			VkDialogManager* obj = (VkDialogManager*)clientData;
			obj->unpost(children[0]);
		}
	}
}
