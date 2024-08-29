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
 * $Id: VkApp.h,v 1.12 2009/03/21 11:44:34 jostle Exp $
 * This file contains the class definition for the
 * VkApp Application Class.  This class must 
 * be instantiated exactly once in any given application.  
 * Results will be screwy if you don't follow this simple rule.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc
 * All Rights Reserved
 *
 **/

#ifndef VKAPP_H
#define VKAPP_H

#include <Xm/Xm.h>
#include <Vk/VkConfig.h>
#include <Vk/VkComponent.h>
#include <Vk/VkSimpleWindow.h>
#include <Vk/VkComponentList.h>
#include <Vk/VkCursorList.h>
#include <Vk/VkBusyDialog.h>
#include <Vk/VkInterruptDialog.h>
#include <Vk/VkProgressDialog.h>

typedef enum {Animated, NotAnimated} VkCursorType;

class VkApp : public VkComponent {
	friend class VkSimpleWindow;
public:
    VkApp (const char* appClassName,
		   int* argc,
		   char** argv,
		   XrmOptionDescRec* options = NULL,
		   int numOptions = 0);
	// NYI
//      VkApp (char* appClassName,
//  		   int* argc,
//  		   char** argv,
//  		   ArgList argList,
//  		   Cardinal argCount,
//  		   void (*preRealizeFunction)(Widget w),
//  		   XrmOptionDescRec* options = NULL,
//  		   int numOptions = 0);

	virtual ~VkApp();
	
    virtual void run();
	void run(Boolean(*appEventHandler)(XEvent &));
	void runOneEvent(Boolean(*appEventHandler)(XEvent &) = NULL);
	void run_first();
	
    virtual void handleRawEvent(XEvent* event);
    virtual void handlePendingEvents();
	// NYI
//  	XtInputMask handleOnePendingEvent(
//  		Boolean(*appEventHandler)(XEvent &) = NULL);

	virtual void quitYourself();
    virtual void terminate(int status = 0);
  
	void setMainWindow(VkSimpleWindow* window) { _mainWindow = window; }
	VkSimpleWindow* mainWindow() const { return _mainWindow; }
  
    virtual void show();
    virtual void hide();
    virtual void iconify();
    virtual void open();
    virtual void raise();
    virtual void lower();

	void startupIconified(const Boolean flag) { _startupIconified = flag; }

    void setNormalCursor(Cursor c);
	virtual Cursor normalCursor() { return _currentCursor; }
    void setBusyCursor(Cursor c);
    void setBusyCursor(VkCursorList* animatedCursor);
    virtual Cursor busyCursor();
    void showCursor(Cursor c);

    virtual void busy(const char* msg = NULL,
					  VkSimpleWindow* window = NULL);
    virtual void veryBusy(const char* msg = NULL,
						  VkSimpleWindow* window = NULL);
	virtual void progressing(const char* msg = NULL);
	virtual void notBusy();
    void setBusyDialog(VkBusyDialog* dialog);

    void setVersionString(const char* versionInfo);
	const char* versionString() const { return _versionString; }

	void setAboutDialog(VkDialogManager* dialog) { _aboutDialog = dialog; }
    VkDialogManager* aboutDialog() { return _aboutDialog; };

	// NYI void setStartupDialog(VkDialogManager* dialog);

    // Application Data Access Functions

    const char* name() const;
	const char* applicationClassName() const { return _appClassName; }
    virtual const char* className() { return "VkApp"; }
    XtAppContext appContext() const { return _theApp; }
	Display* display() const { return _theDisplay; }
    const char* shellGeometry() const;
	int argc() const { return _applicationArgc; }
	char** argv() const { return _applicationArgv; }
	char* argv(int indx) const { return _applicationArgv[indx]; }
	Boolean startupIconified() const { return _startupIconified; }
	Boolean traceApplication() { return _traceApplication; }

    void registerWindow(VkSimpleWindow* win);
    void unregisterWindow(VkSimpleWindow* win);

  	static void setFallbacks(char**);

    static const char* ViewKlassReleaseString;
    static const int ViewKlassMajorRelease;
    static const int ViewKlassMinorRelease;

	// Help support
	int helpInit(const char* client, const char* sep);
	struct HelpInitArgs {
		const char* client;
		const char* sep;
	};
	int helpMsg(const char* key, const char* book, const char* userData);
	struct HelpMsgArgs {
		const char* key;
		const char* book;
		const char* userData;
	};
	int helpIndexMsg(const char* key, const char* book);
	struct HelpIndexMsgArgs {
		const char* key;
		const char* book;
	};
	static const char* const helpInitCallback;
	static const char* const helpMsgCallback;
	static const char* const helpIndexMsgCallback;

	// NYI SGI Help support
//  	void useSGIHelp();
//  	static void sgiHelpInit(VkCallbackObject* caller,
//  							void* clientData,
//  							void* callData);
//  	static void sgiHelpMsg(VkCallbackObject* caller,
//  						   void* clientData,
//  						   void* callData);
//  	static void sgiHelpIndexMsg(VkCallbackObject* caller,
//  								void* clientData,
//  								void* callData);

	// Not defined in the man page but needed to implement
	// VkSimpleWindow getWindow(VkComponent*) and
	// VkWindow getWindow(VkComponent*) and getMenu(VkComponent*)
	VkComponentList* winList() { return &_winList; }

	// Seems like a useful little debugging tool
	void dumpWidgetTree(Widget w = 0);
	
protected:
    int parseCommandLine(XrmOptionDescRec* options,
						 Cardinal numOptions);

	// NYI
//  	virtual void afterRealizeHook();

    VkComponentList _winList;

private:
    int _applicationArgc;
    char** _applicationArgv;

    XtAppContext _theApp;
    Display* _theDisplay;
    char* _appClassName;
    VkSimpleWindow* _mainWindow;
    char* _versionString;
	
    int _busyDepth;
    Cursor _busyCursor;
    VkBusyDialog* _busyDialog;

    VkDialogManager* _aboutDialog;

	Cursor _currentCursor;
	VkCursorType _cursorType;
    VkCursorList* _busyCursorList;

    Boolean _startupIconified;
    Boolean _dumpResourceFile;
    Boolean _traceApplication;

    static const char* const _defaultResources[];
    static XtResource _resourceList[];

	static char** _fallbacks;
};

extern VkApp* theApplication;

#endif /* VKAPP_H */
