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
 * VkApp.C
 * 
 * This file contains the implementation for the VkApp
 * class.
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
	= "$Id: VkApp.C,v 1.24 2009/03/21 11:44:34 jostle Exp $";

#include <cstdlib>
#include <iostream>

using namespace std;

#include <Vk/VkApp.h>
#include <Vk/builtinbusy.h>
#include <Vk/VkCallbackObject.h>
#include <Vk/VkInfoDialog.h>
#include <Vk/VkHelpAPI.h>

#include <X11/cursorfont.h>
#include <assert.h>
#include <string.h>

/////////////////////////////////////////////////////////////
// Need these for the low-level widget access in showCursor
// and dumpWidgetTree.
//
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>

VkApp *theApplication = NULL;

const char* const VkApp::_defaultResources[] = {
	"-*iconic:					False",
	"-*debugResources:			False",
	"-*traceApplication:		False",
	"-*busyCursorForeground:	White",
	"-*busyCursorBackground:	Black",
	"-*normalCursorForeground:	White",
	"-*normalCursorBackground:	Black",
	"-*debugXtMode:				False",
	"-*silenceWarnings:			False",
	NULL,
};

String* VkApp::_fallbacks = 0;

const char* 
VkApp::ViewKlassReleaseString = "ViewKlass Release 0.7.2";

const int
VkApp::ViewKlassMinorRelease = 7;

const int 
VkApp::ViewKlassMajorRelease = 0;


VkApp::VkApp(const char* appClassName,
			 int *argc,
			 char* *argv,
			 XrmOptionDescRec *options,
			 int numOptions)
	: VkComponent (appClassName),
	  _applicationArgc(0),
	  _applicationArgv(0),
	  _appClassName(0),
	  _mainWindow(0),
	  _versionString(0),
	  _busyDepth(0),
	  _busyDialog(theBusyDialog),
	  _aboutDialog(theInfoDialog),
	  _currentCursor(None),
	  _cursorType(NotAnimated),
	  _startupIconified(false),
	  _dumpResourceFile(false),
	  _traceApplication(false)
{
	theApplication = this;

	_appClassName = new char[strlen(appClassName) + 1];
	strcpy(_appClassName, appClassName);

	_applicationArgc = *argc;
	_applicationArgv = new char*[_applicationArgc];

	for (int i = 0; i < _applicationArgc; i++) {
		_applicationArgv[i] = new char[strlen(argv[i]) + 1];
		strcpy(_applicationArgv[i], argv[i]);
	}

	////////
	// XtVaOpenApplication is now the preferred method
	// for initialising the application.
	// It calls XtToolkitInitialize, XtCreateApplicationContext,
	// XtOpenDisplay, XtAppCreateShell and XtAppSetFallbackResources
	//
	_baseWidget = XtVaOpenApplication(&_theApp,
									  appClassName,
									  options,
									  numOptions,
									  argc,
									  argv,
									  _fallbacks,
									  applicationShellWidgetClass,
									  XtNmappedWhenManaged, False,
									  NULL);

	// Needs to be realized to be used as the parent of dialogs.
	XtRealizeWidget(_baseWidget);
	
	installDestroyHandler();
	
	_theDisplay = XtDisplay(_baseWidget);

	_busyCursor = XCreateFontCursor(_theDisplay, XC_watch);

	// Initialise the help system
	helpInit(_appClassName, NULL);
	
	// The application base widget is centred on the screen
	Dimension baseWidth;
	Dimension baseHeight;

    XtVaGetValues(_baseWidget,
				  XtNheight, &baseHeight,
				  XtNwidth, &baseWidth,
				  NULL);

	Dimension dispWidth = DisplayWidth(_theDisplay, 0);
	Dimension dispHeight = DisplayHeight(_theDisplay, 0);
	
    Position x = dispWidth / 2  - baseWidth / 2;
    Position y = dispHeight / 2 - baseHeight / 2;
	XtVaSetValues(_baseWidget, XmNx, x, XmNy, y,
				  NULL);

	setDefaultResources(baseWidget(),_defaultResources);

	_startupIconified =
			(long)VkGetResource(baseWidget(),
							   "iconic", "Iconic",
							   XmRBoolean, "False");
	_dumpResourceFile =
			(long)VkGetResource(baseWidget(),
							   "debugResources", "DebugResources",
							   XmRBoolean, "False");
	_traceApplication =
			(long)VkGetResource(baseWidget(),
								   "traceApplication", "TraceApplication",
								   XmRBoolean, "False");
	
}

VkApp::~VkApp()
{
	delete []_appClassName;
	for (int i = 0; i < _applicationArgc; i++) {
		delete []_applicationArgv[i];
	}
	delete []_applicationArgv;
	delete []_versionString;
}

int
VkApp::parseCommandLine(XrmOptionDescRec *options,
						Cardinal numOptions)
{
	XrmDatabase line_db = NULL;
	char* rms = XResourceManagerString(_theDisplay);
	XrmDatabase display_db = XrmGetStringDatabase(rms);

	XrmParseCommand(&line_db, options, numOptions, _name,
					&_applicationArgc, _applicationArgv);

	XrmCombineDatabase(display_db, &line_db, True);
	XrmSetDatabase(_theDisplay, line_db);

	return _applicationArgc;
}

void
VkApp::setFallbacks(char** fallbacks)
{
	// Sets fallbacks as the specification_list needed to call
	// XtAppSetFallbackResources(3X).  setFallbacks() must be called before
	// the application constructs its VkApp object, because the VkApp
	// constructor does call XtAppSetFallbackResources(3X), passing it the
	// specification_list.

	_fallbacks = fallbacks;
}

void
VkApp::handleRawEvent(XEvent *event)
{
	for (int i = _winList.size() - 1; i >= 0; i--) {
		if (_winList[i] != NULL) {
			((VkSimpleWindow*)_winList[i])->handleRawEvent(event);
		}
	}
}

void
VkApp::handlePendingEvents()
{
	XEvent ev;

	while (XtAppPending(_theApp)) {
		XtAppNextEvent(_theApp, &ev);
		if(!XtDispatchEvent(&ev))
			handleRawEvent(&ev);
	}
}

void
VkApp::run()
{
	run_first();
	for (;;) { /* we needn't return */
		runOneEvent();
	}
}

void VkApp::run(Boolean(*appEventHandler)(XEvent &))
{
	run_first();
	for (;;) { /* we needn't return */
		runOneEvent(appEventHandler);
	}
}

void
VkApp::run_first()
{
	if (_dumpResourceFile) {
		XrmPutFileDatabase(XrmGetDatabase (_theDisplay),
						   "/usr/tmp/start_resources.db");
	}
	if (_currentCursor != None) {
		showCursor(_currentCursor);
	}
}

void
VkApp::runOneEvent(Boolean(*appEventHandler)(XEvent &))
{
	XEvent event;
	XtAppNextEvent(_theApp, &event);
	if(!XtDispatchEvent(&event)) {
		handleRawEvent(&event);
	}
}	

void
VkApp::terminate(int status)
{
	exit(status);
}

void
VkApp::setVersionString(const char* versionInfo)
{
	_versionString = new char[strlen(versionInfo) + 1];
	strcpy(_versionString, versionInfo);
}

void
VkApp::setBusyDialog(VkBusyDialog* newDialog)
{
	if (newDialog) {
		_busyDialog = newDialog;
	} else {
		_busyDialog = theBusyDialog;
	}
}

void
VkApp::busy(const char* msg,
			VkSimpleWindow* window)
{
	_busyDepth++;

	showCursor(busyCursor());

	if (msg != NULL) {
		// Check if the message string names a resource ...
		const char* resourceMsg = VkGetResource(msg, "BusyMessage");
		// and if so use the value of the resource as the message.
		if (resourceMsg != 0) {
			msg = resourceMsg;
		}

		if (window == NULL) {
			_busyDialog->post(msg);
		} else {
			_busyDialog->post(msg, NULL, NULL, NULL, NULL, NULL, window);
		}
	}
	handlePendingEvents();
}

void
VkApp::veryBusy(const char* msg,
				VkSimpleWindow* window)
{
	busy(msg, window);
}

void
VkApp::progressing(const char* msg)
{
	if (_cursorType == Animated) {
		showCursor(_busyCursorList->next());
	}
	if (msg != NULL) {
		_busyDialog->post(msg);
	}
}

void
VkApp::notBusy()
{
	if (_busyDepth) { // We were busy to begin with
		_busyDepth--;
	}

	if (_busyDepth == 0) {
		setNormalCursor(None);
		XEvent event;
		while (XCheckMaskEvent(_theDisplay,
							   ButtonPressMask | ButtonReleaseMask | 
							   ButtonMotionMask | PointerMotionMask | 
							   KeyPressMask, &event))
		{
			// do nothing 
			// Just discard all user input to
			// avoid type-ahead while busy.
		}
		_busyDialog->unpostAll();
	}
}

void
VkApp::setBusyCursor(VkCursorList* animatedCursor)
{
	_busyCursorList = animatedCursor;
	_cursorType = Animated;
}
 
void
VkApp::setBusyCursor(Cursor c)
{
	_busyCursor = c;
	_cursorType = NotAnimated;
}

Cursor
VkApp::busyCursor()
{
	if (_cursorType == Animated) {
		return _busyCursorList->current();
	}
	return _busyCursor;
}

void
VkApp::setNormalCursor(Cursor c)
{
	_currentCursor = c;
	showCursor(None);
}

void
VkApp::showCursor(Cursor c)
{
	if (c == None) {
		c = _currentCursor;
	}

	for (int i = 0; i < _winList.size(); ++i) {
		assert (_winList[i] != NULL);
		VkSimpleWindow* sw = (VkSimpleWindow*)_winList[i];
		Widget w = XtParent(sw->mainWindowWidget());
		if (XtIsRealized(w)) {
			XDefineCursor(_theDisplay, XtWindow(w), c);
			unsigned int numPopups = 0;
			WidgetList popups = 0;
			numPopups = w->core.num_popups;
			popups = w->core.popup_list;
			for (unsigned int j = 0; j < numPopups; ++j) {
				XDefineCursor(_theDisplay, XtWindow(popups[j]), c);
			}
		}
		// Dialogs which are 'centred on screen' are posted as children
		// of the application's base widget so set their cursor too.
		w = _baseWidget;
		unsigned int numPopups = 0;
		WidgetList popups = 0;
		numPopups = w->core.num_popups;
		popups = w->core.popup_list;
		for (unsigned int j = 0; j < numPopups; ++j) {
			XDefineCursor(_theDisplay, XtWindow(popups[j]), c);
		}
	}
	XFlush(_theDisplay);
}

void
VkApp::show()
{
	for (int i = 0; i < _winList.size(); i++) {
		assert (_winList[i] != NULL);
		_winList[i]->show();
	}
}

void
VkApp::hide()
{
	for (int i = 0; i < _winList.size(); i++) {
		assert (_winList[i] != NULL);
		_winList[i]->hide();
	}
}

void
VkApp::iconify()
{
	for (int i = 0; i < _winList.size(); i++) {
		assert (_winList[i] != NULL);
		((VkSimpleWindow*)_winList[i])->iconify();
	}
}

void
VkApp::open()
{
	for (int i=0; i< _winList.size(); i++) {
		assert (_winList[i] != NULL);
		((VkSimpleWindow*)_winList[i])->open();
	}
}

void
VkApp::raise()
{
	for (int i=0; i< _winList.size(); i++) {
		assert (_winList[i] != NULL);
		((VkSimpleWindow*)_winList[i])->raise();
	}
}

void
VkApp::lower()
{
	for (int i=0; i< _winList.size(); i++) {
		assert (_winList[i] != NULL);
		((VkSimpleWindow*)_winList[i])->lower();
	}
}

const char* 
VkApp::name() const
{
	char* slash = strrchr(argv(0), (int)'/');

	if (slash == NULL) {
		return argv(0);
	} else {
		return (++slash);
	}
}

const char*
VkApp::shellGeometry() const
{
	return NULL; // For Now
}

void
VkApp::quitYourself()
{
	assert (_mainWindow != NULL);

	if (_dumpResourceFile) {
		XrmPutFileDatabase(XrmGetDatabase (_theDisplay),
						   "/usr/tmp/final_resources.db");
	}

	int i;
	int all_deleted = TRUE;

	for (i = _winList.size() - 1 ; i >= 0; i--) {
		if (_winList[i] == _mainWindow)	continue;
		if (_winList[i]->okToQuit()) {
			assert (_winList[i] != NULL);
			delete _winList[i];
		} else {
			all_deleted = FALSE;
		}
	}
	if (_mainWindow->okToQuit()) {
		delete _mainWindow;
		_winList.remove(_mainWindow);
	} else {
		all_deleted = FALSE;
	}
	
	if (all_deleted) {
		terminate();
	}
}

void
VkApp::registerWindow(VkSimpleWindow* win)
{
	assert(win != NULL);

	if (_mainWindow == NULL) {
		setMainWindow(win);
	}
	_winList.add(win);
}

void
VkApp::unregisterWindow(VkSimpleWindow* win)
{
	assert(win != NULL);

	int mainWindowDeleted = False;

	if (_mainWindow == win) {
		mainWindowDeleted = True;
		if (_traceApplication) {
			cerr << "Main window deleted,\n whatever shall we do?" << endl;
		}
	}

	if (win->okToQuit()) {
		_winList.remove(win);

		if (_winList.size() == 0) {
			if (_traceApplication) {
				cerr << "no other windows, exiting..." << endl;
			}
			terminate();
		}
	}

	if (mainWindowDeleted) {
		if (_traceApplication) {
			cerr << "choosing another one" << endl;
		}
		_mainWindow = (VkSimpleWindow*)_winList[0];
	}
}

// Help support
int
VkApp::helpInit(const char* client, const char* sep)
{
	static HelpInitArgs calldata;
	if (hasCallbacks(VkApp::helpInitCallback)) {
		calldata.client = client;
		calldata.sep = sep;
		callCallbacks(VkApp::helpInitCallback, &calldata);
	} else {
		SGIHelpInit(display(), applicationClassName(), "");
	}
	return 1;
}

int
VkApp::helpMsg(const char* key, const char* book, const char* userData)
{
	static HelpMsgArgs calldata;
	if (hasCallbacks(VkApp::helpMsgCallback)) {
		calldata.key = key;
		calldata.book = book;
		calldata.userData = userData;
		callCallbacks(VkApp::helpMsgCallback, &calldata);
	} else {
	    SGIHelpMsg(key, book, "");
	}
	return 1;
}

int
VkApp::helpIndexMsg(const char* key, const char* book)
{
	static HelpIndexMsgArgs calldata;
	if (hasCallbacks(VkApp::helpIndexMsgCallback)) {
		calldata.key = key;
		calldata.book = book;
		callCallbacks(VkApp::helpIndexMsgCallback, &calldata);
	} else {
	    SGIHelpIndexMsg(key, book);
	}
	return 1;
}

const char* const VkApp::helpInitCallback = "VkApp::helpInitCallback";
const char* const VkApp::helpMsgCallback = "VkApp::helpMsgCallback";
const char* const VkApp::helpIndexMsgCallback = "VkApp::helpIndexMsgCallback";

//
// Print a textual version of the widget tree to cout.
//
// Requires the include of X11/IntrinsicP.h and X11/CoreP.h
//

void
VkApp::dumpWidgetTree(Widget w)
{
	// The default is to dump the complete widget tree.
	if (w == 0) {
		w = _baseWidget;
	}
	
	static int nesting = 0;

	// Print out the starting point
	if (nesting == 0) {
		cout << "Widget Tree for : " << endl
			 << applicationClassName() << "*"
			 << XtName(w) << " (" << w << ") ["
			 << XtClass(w)->core_class.class_name
			 << "]" << endl;
	}
	
	unsigned int numKids = 0;
	WidgetList kids = 0;
	if (XtIsComposite(w)) {
		XtVaGetValues(w, XmNnumChildren, &numKids, XmNchildren, &kids, NULL);
	}
	
	unsigned int numPopups = 0;
	WidgetList popups = 0;
	if (XtIsWidget(w)) {
		numPopups = w->core.num_popups;
		popups = w->core.popup_list;
	}

	unsigned int totalKids = numKids + numPopups;
	for (unsigned int i = 0; i < totalKids; ++i) {
		for (int n = 0; n < nesting; ++n) {
			cout << "|  " ;
		}
		Widget next;
		const char* prefix; // Indicates the type of child; normal or popup
		if (i < numKids) {
			next = kids[i];
			prefix = "+- ";
		} else {
			next = popups[i - numKids];
			prefix = "^- ";
		}
		cout << prefix << XtName(next) << " ("
			 << next << ") ["
			 << XtClass(next)->core_class.class_name
			 << "]" << endl;

		// Don't recurse unless this is a widget
		if (XtIsWidget(next)) {
			nesting++;
			dumpWidgetTree(next);
			nesting--;
		}
	}
}

