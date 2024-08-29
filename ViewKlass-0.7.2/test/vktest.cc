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

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: vktest.cc,v 1.22 2009/03/21 11:44:34 jostle Exp $";

#include <unistd.h>
#include <iostream>
#include <sstream>

#include <Xm/Frame.h>
#include <Xm/List.h>

#include <Vk/VkApp.h>
#include <Vk/VkWindow.h>
#include <Vk/VkSubMenu.h>
#include <Vk/VkMenuUndoManager.h>
#include <Vk/VkCompletionField.h>
#include <Vk/VkPrefGroup.h>
#include <Vk/VkPrefText.h>

#include <Vk/VkSelectionDialog.h>
#include <Vk/VkFileSelectionDialog.h>
#include <Vk/VkPromptDialog.h>
#include <Vk/VkErrorDialog.h>
#include <Vk/VkFatalErrorDialog.h>
#include <Vk/VkInfoDialog.h>
#include <Vk/VkMessageDialog.h>
#include <Vk/VkQuestionDialog.h>
#include <Vk/VkWarningDialog.h>

#include <Vk/VkPixmap.h>

#include <Vk/builtinbusy.h>

#include "TestPrefDialog.h"
#include "TestPeriodic.h"
#include "TestInput.h"
#include "TestAlignment.h"
#include "TestCompletion.h"
#include "TestWindow.h"
#include "Slider.h"

#include "vklogo32.xpm"

void testVkWidgetList(Widget, XtPointer, XtPointer);
void testVkNameList(Widget, XtPointer, XtPointer);
void testVkComponentList(Widget, XtPointer, XtPointer);

Widget theList;
Widget centreWidget;

void
testVkAlignmentGroup(Widget w, XtPointer parentW, XtPointer)
{
	static TestAlignment* ta = 0;
	delete ta;
	ta = new TestAlignment("testAlignment", (Widget)parentW);
	ta->show();
}

void
testVkBusy(Widget w, XtPointer, XtPointer)
{
	theApplication->busy();

	for (int i = 0; i < 100; ++i) {
		XmUpdateDisplay(w);
		usleep(100000);
		theApplication->progressing();
	}
	theApplication->notBusy();
}

void
testVkBusyDialog(Widget w, XtPointer, XtPointer)
{
	theApplication->busy("Wait a bit.");

	for (int i = 0; i < 100; ++i) {
		XmUpdateDisplay(w);
		usleep(100000);
		theApplication->progressing();
	}
	theApplication->notBusy();
}

void
testVkInterruptDialog(Widget, XtPointer, XtPointer)
{
	theApplication->setBusyDialog(theInterruptDialog);
	theApplication->busy("waitMessage");
	for (int i = 0; i < 100; ++i) {
		usleep(100000);
		if (theInterruptDialog->wasInterupted()) {
			break;
		}
		theApplication->progressing();
	}
	theApplication->notBusy();
	theApplication->setBusyDialog(0);
}


void
testVkProgressDialog(Widget, XtPointer, XtPointer)
{
	theApplication->setBusyDialog(theProgressDialog);
	theProgressDialog->setTitle("progressing");
	theApplication->busy("Wait a bit.");
	for (int i = 0; i < 100; ++i) {
		usleep(100000);
		if (theProgressDialog->wasInterupted()) {
			break;
		}
		theProgressDialog->setPercentDone(i);
		theApplication->progressing();
	}
	theApplication->notBusy();
	theApplication->setBusyDialog(0);
}

// The global Preferences dialog.
TestPrefDialog* ptd = 0;

void
deleteVkPrefDialog(Widget, XtPointer, XtPointer)
{
		delete ptd;
}

void
testVkPrefDialog(Widget, XtPointer, XtPointer)
{
	ptd = new TestPrefDialog("testPrefDialog");

	ptd->centerOnScreen(true);
	ptd->post("TestPrefDialog");

	ptd->setOptionValue(3);
}

void
testVkSelectionDialog(Widget, XtPointer, XtPointer)
{
//	theSelectionDialog->clearList();
	theSelectionDialog->setTitle("Select Something");
	theSelectionDialog->addItem("Item 1");
	theSelectionDialog->addItem("Item 2");
	theSelectionDialog->addItem("Item 3");
	theSelectionDialog->addItem("Item 4");
	theSelectionDialog->addItem("Item 5");
	theSelectionDialog->setNumVisibleItems(4);
	theSelectionDialog->setListLabel("List Label");
	theSelectionDialog->post("selectMe");
	theSelectionDialog->addItem("Item 6");
	theSelectionDialog->addItem("Item 7");
	theSelectionDialog->addItem("Item 8");
	theSelectionDialog->addItem("Item 9", true);
	theSelectionDialog->setListLabel("New List Label");
}

void
testVkPromptDialog(Widget, XtPointer, XtPointer)
{
	thePromptDialog->setTitle("Enter Something");
	thePromptDialog->post("promptMessage");
}

void
testVkErrorDialog(Widget, XtPointer, XtPointer)
{
	theErrorDialog->setTitle("There's a Problem");
	theErrorDialog->postBlocked("The Error Dialog");
}

void
testVkFatalErrorDialog(Widget, XtPointer, XtPointer)
{
	theFatalErrorDialog->setTitle("Oops!");
	theFatalErrorDialog->setButtonLabels("Oh Dear!");
	theFatalErrorDialog->post("The Fatal Error Dialog\n"
							  "The application will now exit!");
}

void
testVkInfoDialog(Widget w, XtPointer, XtPointer)
{
	theInfoDialog->setTitle("FYI");
	// Centre the dialog over a widget
	theInfoDialog->post("The Info Dialog", centreWidget);
}

void
testVkMessageDialog(Widget w, XtPointer, XtPointer)
{
	theMessageDialog->setTitle("Bottle");
	theMessageDialog->post("The Message Dialog");
}

void
testVkQuestionDialog(Widget, XtPointer, XtPointer)
{
	theQuestionDialog->setTitle("What?");
	theQuestionDialog->setButtonLabels("Yeah", "Nope");
	theQuestionDialog->post("The Question Dialog");
}

void
testVkWarningDialog(Widget, XtPointer, XtPointer)
{
	theWarningDialog->setTitle("Watch Out");
	theWarningDialog->postModal("The Warning Dialog");
}

void
testVkFileSelectionDialog(Widget, XtPointer, XtPointer)
{
	theFileSelectionDialog->setFilterPattern("*"); // test for bug 589942
	theFileSelectionDialog->setTitle("Pick a File");
	if (theFileSelectionDialog->postAndWait( ) == VkDialogManager::OK) {
		cout << "File name " << theFileSelectionDialog->fileName() << endl;
	}

	theFileSelectionDialog->setTitle("Any File");
	theFileSelectionDialog->setDirectory("/home/");
	if (theFileSelectionDialog->postAndWait( ) == VkDialogManager::OK) {
		cout << "File name " << theFileSelectionDialog->fileName() << endl;
	}
	
	theFileSelectionDialog->setTitle("That contains an 'a'");
	theFileSelectionDialog->setFilterPattern("*a*");
	if (theFileSelectionDialog->postAndWait( ) == VkDialogManager::OK) {
		cout << "File name " << theFileSelectionDialog->fileName() << endl;
	}
	
	theFileSelectionDialog->setTitle("or maybe ls");
	theFileSelectionDialog->setSelection("/bin/ls");
	if (theFileSelectionDialog->postAndWait( ) == VkDialogManager::OK) {
		cout << "File name " << theFileSelectionDialog->fileName() << endl;
	}
}

void
testVkPeriodic(Widget, XtPointer, XtPointer)
{
	static TestPeriodic* tp = 0;

	if (tp) delete(tp);

	tp = new TestPeriodic();
}

void
testVkInput(Widget, XtPointer, XtPointer)
{
	static TestInput* ti = 0;

	if (!ti) {
		ti = new TestInput();
	}
	ti->checkFile();
}

void
testVkWindow(Widget, XtPointer, XtPointer)
{
	static TestWindow* tw = 0;
	delete(tw); tw = new TestWindow("aTestWindow");

	tw->show();

	tw->menu()->showHelpPane();
}

void
setUndoMultilevel(Widget, XtPointer, XtPointer cd)
{
	Boolean multi = ((XmToggleButtonCallbackStruct*)cd)->set;
	theUndoManager->multiLevel(multi);
	cout << "Multi-level undo is " << (multi ? "on" : "off") << endl;
}

void
testUndoOne(Widget, XtPointer, XtPointer)
{
	cout << "Doing something undoable" << endl;
}

void
undoChangeOne(Widget, XtPointer, XtPointer)
{
	cout << "Undoing something undoable" << endl;
}

void
testUndoTwo(Widget, XtPointer, XtPointer)
{
	cout << "Doing another undoable thing" << endl;
}

void
undoChangeTwo(Widget, XtPointer, XtPointer)
{
	cout << "Undoing another undoable thing" << endl;
}

void
testUndoThree(Widget, XtPointer, XtPointer)
{
	cout << "Doing a final undoable thing" << endl;
}

void
undoChangeThree(Widget, XtPointer, XtPointer)
{
	cout << "Undoing a final undoable thing" << endl;
}

void
resetUndo(Widget, XtPointer, XtPointer)
{
	cout << "Resetting the undo stack" << endl;
	theUndoManager->reset();
}

void
quitCallback(Widget, XtPointer, XtPointer)
{
	Boolean dumpTree = (long)VkGetResource(theApplication->baseWidget(),
										  "dumpWidgetTree", "DumpWidgetTree",
										  XmRBoolean, "False");
	if (dumpTree) {
		theApplication->dumpWidgetTree();
	}
	
	theApplication->quitYourself();
}

bool
versionCheck()
{
	const int CURRENT_VERSION = 70;
	int version = (long)VkGetResource(theApplication->baseWidget(),
									 "versionCheck", "Version",
									 XmRInt, "0");
	if (version != CURRENT_VERSION) {
		stringstream msg;
		msg << "Resource File Version Check failed." << "\n"
			<< "Found version " << version << "\n"
			<< "Current version is "
			<< CURRENT_VERSION << ".\n"
			<< "Please copy the resource file (Vktest) to $HOME"
			<< ends;
		theWarningDialog->setButtonLabels("Continue", "Quit");
		theWarningDialog->centerOnScreen(true);
		return (theWarningDialog->postAndWait(msg.str().c_str())
				== VkDialogManager::OK);
	}
	return true;
}

int
main(int argc, char** argv)
{
	const char* const defaultResources[] = {
		"+*background : grey80",
		"*fontList : -*-helvetica-medium-r-*-*-*-120-*-*-*-*-*-*",
		"*menuBar*fontList : -*-helvetica-bold-o-*-*-*-120-*-*-*-*-*-*",
		"*XmLabel*fontList : -*-helvetica-bold-r-*-*-*-120-*-*-*-*-*-*",
		"*XmLabelGadget*fontList : -*-helvetica-bold-r-*-*-*-120-*-*-*-*-*-*",
		"*XmText.marginWidth : 2",
		"*XmText.marginHeight : 2",
		"*XmTextField.marginWidth : 2",
		"*XmTextField.marginHeight : 1",
		"*highlightThickness : 1",
		"*shadowThickness : 1",
		"*XmSeparator.shadowThickness : 2",
		"*XmSeparatorGadget.shadowThickness : 2",
		"*XmForm.shadowThickness : 0",
		"*XmToggleButton.shadowThickness : 0",
		"*XmToggleButton.detailShadowThickness : 1",
		"*XmToggleButtonGadget.shadowThickness : 0",
		"*XmToggleButtonGadget.detailShadowThickness : 1",
		"*edit.labelString: Edit",
		"*edit.mnemonic: E",
		"*Undo.labelString: Undo",
		"*Undo.mnemonic: U",
		"*Undo.accelerator: Ctrl<Key>z",
		"*Undo.acceleratorText: ^Z",
		"*application.labelString: Application",
		"*application.mnemonic: A",
		"*lists.labelString: Lists",
		"*lists.mnemonic: L",
		"*busy.labelString: Busy",
		"*busy.mnemonic: B",
		"*dialogs.labelString: Dialogs",
		"*dialogs.mnemonic: D",
		"*preferences.labelString: Preferences",
		"*preferences.mnemonic: P",
		"*alignment.labelString: Alignment",
		"*alignment.mnemonic: i",
		NULL,
	};

	VkApp* app = new VkApp("Vktest", &argc, argv);

	app->setDefaultResources(app->baseWidget(), defaultResources);
	app->setVersionString("Vktest 0.7.2");

	VkWindow* win = new VkWindow("VkTestHarness");

	win->setTitle("titleResource");
	win->setIconName("iconNameResource");

	VkSubMenu* appPane = win->addMenuPane("application");
	VkSubMenu* editPane = win->addMenuPane("edit");
	VkSubMenu* listPane = win->addMenuPane("lists");
	VkSubMenu* busyPane = win->addMenuPane("busy");
	VkSubMenu* dlgPane = win->addMenuPane("dialogs");
	VkSubMenu* prefPane = win->addMenuPane("preferences");
	VkSubMenu* alignPane = win->addMenuPane("alignment");

	win->menu()->showHelpPane();

	appPane->showTearOff(False);
	listPane->showTearOff(True);
	busyPane->showTearOff(True);
	dlgPane->showTearOff(True);
	prefPane->showTearOff(True);

	appPane->addActionWidget("VkPeriodic", testVkPeriodic, win);
	appPane->addActionWidget("VkInput", testVkInput, win);
	appPane->addActionWidget("VkWindow", testVkWindow, win);
	appPane->addSeparator();
	appPane->addConfirmFirstAction("Quit", quitCallback, NULL);

	editPane->add(theUndoManager);
	editPane->addSeparator();
	editPane->addAction("First Change",  testUndoOne,   undoChangeOne,   win);
	editPane->addAction("Second Change", testUndoTwo,   undoChangeTwo,   win);
	editPane->addAction("Third Change",  testUndoThree, undoChangeThree, win);
	editPane->addToggle("MultiLevel Undo",  setUndoMultilevel, win, 1);
	editPane->addAction("Reset",  resetUndo, win);
	
	listPane->addAction("VkComponentList", testVkComponentList, win);
	listPane->addAction("VkNameList", testVkNameList, win);
	listPane->addAction("VkWidgetList", testVkWidgetList, win);

	busyPane->addAction("VkBusy", testVkBusy, win);
	busyPane->addAction("VkBusyDialog", testVkBusyDialog, win);
	busyPane->addAction("VkInterruptDialog", testVkInterruptDialog, win);
	busyPane->addAction("VkProgressDialog", testVkProgressDialog, win);

	dlgPane->addAction("VkSelectionDialog", testVkSelectionDialog, win);
	dlgPane->addAction("VkPromptDialog", testVkPromptDialog, win);
	dlgPane->addAction("VkFileSelectionDialog",testVkFileSelectionDialog, win);
	dlgPane->addAction("VkErrorDialog", testVkErrorDialog, win);
	dlgPane->addAction("VkFatalErrorDialog", testVkFatalErrorDialog, win);
	dlgPane->addAction("VkInfoDialog", testVkInfoDialog, win);
	dlgPane->addAction("VkMessageDialog", testVkMessageDialog, win);
	dlgPane->addAction("VkQuestionDialog", testVkQuestionDialog, win);
	dlgPane->addAction("VkWarningDialog", testVkWarningDialog, win);

	prefPane->addAction("VkPrefDialog", testVkPrefDialog, win);
	prefPane->addAction("Delete VkPrefDialog", deleteVkPrefDialog, win);

	cout << "ViewKlassReleaseString " << app->ViewKlassReleaseString << endl; 

	Widget form = XtVaCreateManagedWidget(
		"form", xmFormWidgetClass,
		win->mainWindowWidget(),
		NULL);

	Slider* slider = new Slider("slider1", form);
	XtVaSetValues(slider->baseWidget(),
				  XmNtopAttachment, XmATTACH_FORM,
				  XmNleftAttachment, XmATTACH_FORM,
				  XmNrightAttachment, XmATTACH_FORM,
				  NULL);

	slider->setLabel("Offset");
	slider->setRange(43, 197);
	// The first setValue is not undoable; there was no previous value!
	slider->setValue(130, false);
	cout << *slider << endl;

	slider->show();

	Arg args[16];
	int n = 0;
	XtSetArg(args[n], XmNscrollVertical, True); n++;
	XtSetArg(args[n], XmNscrollHorizontal, False); n++;
	XtSetArg(args[n], XmNlistSizePolicy, XmRESIZE_IF_POSSIBLE); n++;
	XtSetArg(args[n], XmNvisibleItemCount, 4); n++;
	theList = XmCreateScrolledList(form, const_cast<char*>("TheList"), args, n);
	XtVaSetValues(XtParent(theList),
				  XmNtopAttachment, XmATTACH_WIDGET,
				  XmNtopWidget, slider->baseWidget(),
				  XmNleftAttachment, XmATTACH_FORM,
				  XmNrightAttachment, XmATTACH_NONE,
				  XmNbottomAttachment, XmATTACH_FORM,
				  NULL);
	XtManageChild(theList);

	Widget dataPixmap = XtVaCreateManagedWidget(
		"vklogo", xmLabelWidgetClass, form,
		XmNlabelType, XmPIXMAP,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, slider->baseWidget(),
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, XtParent(theList),
		XmNrightAttachment, XmATTACH_NONE,
		XmNbottomAttachment, XmATTACH_NONE,
		NULL);
		
	Pixmap pmd = VkCreateXPMPixmap(dataPixmap, vklogo32, NULL);
	XtVaSetValues(dataPixmap, XmNlabelPixmap, pmd, NULL);

	// For testing dialog placement
	centreWidget = dataPixmap;
	
	TestCompletion* cf = new TestCompletion("TestCompletion", form);
	XtVaSetValues(cf->baseWidget(),
				  XmNtopAttachment, XmATTACH_WIDGET,
				  XmNtopWidget, slider->baseWidget(),
				  XmNleftAttachment, XmATTACH_WIDGET,
				  XmNleftWidget, dataPixmap,
				  XmNrightAttachment, XmATTACH_NONE,
				  XmNbottomAttachment, XmATTACH_NONE,
				  NULL);
	cf->show();

	Widget filePixmap = XtVaCreateManagedWidget(
		"jostlelogo", xmLabelWidgetClass, form,
		XmNlabelType, XmPIXMAP,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, slider->baseWidget(),
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, cf->baseWidget(),
		XmNrightAttachment, XmATTACH_NONE,
		XmNbottomAttachment, XmATTACH_NONE,
		NULL);
    
	const char* pixmap_colours[] = {"ExtraHighlight",
       "HorizLine",
       "VertLine",
       NULL};

	Pixmap pmf =
		VkCreateXPMPixmap(filePixmap, "jostlelogo.xpm", pixmap_colours);
	
	XtVaSetValues(filePixmap, XmNlabelPixmap, pmf, NULL);
		
	
	Widget frame = XtVaCreateManagedWidget(
		"frame", xmFrameWidgetClass, form,
		XmNheight, 240,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, filePixmap,
		XmNtopOffset, 4,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, XtParent(theList),
		XmNrightAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_FORM,
		NULL);

	alignPane->addAction("VkAlignmentGroup", testVkAlignmentGroup, frame);

	win->addView(form);
	win->show();

	VkMenuItem* mi = prefPane->findNamedItem("VkPrefDialog");
	mi->setLabel("aPreferenceDialog");

	if (!versionCheck()) {
		exit(1);
	}

	app->setBusyCursor(new BuiltInBusyCursor());
	app->run();

	return 0;
}

