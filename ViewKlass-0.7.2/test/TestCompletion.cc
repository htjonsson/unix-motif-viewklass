/*****************************************************************
    TestCompletion - Test the VkCompletion class.

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
	= "$Id: TestCompletion.cc,v 1.4 2009/03/21 11:44:34 jostle Exp $";

#include <Xm/Label.h>
#include <Xm/Form.h>

#include <Vk/VkCompletionField.h>

#include "TestCompletion.h"

const char* const TestCompletion::_defaultResources[] = {
	"*cfLabel.labelString: Completion Field",
	"*cfHelp.labelString: (Try Vk class names)",
	NULL,
};

TestCompletion::TestCompletion(const char* name, Widget parent)
	: VkComponent(name)
{
	setDefaultResources(parent, _defaultResources);
	
	_baseWidget = XtVaCreateWidget(
		name, xmFormWidgetClass, parent,
		NULL);

	installDestroyHandler();

	Widget cfLabel = XtVaCreateManagedWidget(
		"cfLabel", xmLabelWidgetClass, _baseWidget,
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_NONE,
		NULL);
		
	mCompField = new VkCompletionField("Completion", _baseWidget);
	XtVaSetValues(mCompField->baseWidget(),
				  XmNtopAttachment, XmATTACH_FORM,
				  XmNbottomAttachment, XmATTACH_FORM,
				  XmNleftAttachment, XmATTACH_WIDGET,
				  XmNleftWidget, cfLabel,
				  XmNrightAttachment, XmATTACH_NONE,
				  NULL);
	mCompField->show();
	
	XtVaCreateManagedWidget(
		"cfHelp", xmLabelWidgetClass, _baseWidget,
		XmNalignment, XmALIGNMENT_BEGINNING,
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, mCompField->baseWidget(),
		XmNrightAttachment, XmATTACH_FORM,
		NULL);
		
	mCompField->add("VkAction");
	mCompField->add("VkAlignmentGroup");
	mCompField->add("VkApp");
	mCompField->add("VkBackground");
	mCompField->add("VkBusyDialog");
	mCompField->add("VkCallbackList");
	mCompField->add("VkCallbackObject");
	mCompField->add("VkCheckBox");
	mCompField->add("VkCompletionField");
	mCompField->add("VkComponent");
	mCompField->add("VkComponentList");
	mCompField->add("VkCursorList");
	mCompField->add("VkDialogManager");
	mCompField->add("VkErrorDialog");
	mCompField->add("VkFatalErrorDialog");
	mCompField->add("VkFileSelectionDialog");
	mCompField->add("VkFormat");
	mCompField->add("VkGangedGroup");
	mCompField->add("VkGenericDialog");
	mCompField->add("VkHelpAPI");
	mCompField->add("VkHelpPane");
	mCompField->add("VkInfoDialog");
	mCompField->add("VkInput");
	mCompField->add("VkInterruptDialog");
	mCompField->add("VkMenuAction");
	mCompField->add("VkMenuActionObject");
	mCompField->add("VkMenuActionWidget");
	mCompField->add("VkMenuBar");
	mCompField->add("VkMenu");
	mCompField->add("VkMenuConfirmFirstAction");
	mCompField->add("VkMenuItem");
	mCompField->add("VkMenuLabel");
	mCompField->add("VkMenuSeparator");
	mCompField->add("VkMenuToggle");
	mCompField->add("VkMenuUndoManager");
	mCompField->add("VkModel");
	mCompField->add("VkNameList");
	mCompField->add("VkOptionMenu");
	mCompField->add("VkPeriodic");
	mCompField->add("VkPipe");
	mCompField->add("VkPopupMenu");
	mCompField->add("VkPrefCustom");
	mCompField->add("VkPrefDialog");
	mCompField->add("VkPrefEmpty");
	mCompField->add("VkPrefGroup");
	mCompField->add("VkPrefItem");
	mCompField->add("VkPrefLabel");
	mCompField->add("VkPrefList");
	mCompField->add("VkPrefOption");
	mCompField->add("VkPrefRadio");
	mCompField->add("VkPrefSeparator");
	mCompField->add("VkPrefText");
	mCompField->add("VkPrefToggle");
	mCompField->add("VkProgram");
	mCompField->add("VkProgressDialog");
	mCompField->add("VkPromptDialog");
	mCompField->add("VkQuestionDialog");
	mCompField->add("VkRadioBox");
	mCompField->add("VkRadioGroup");
	mCompField->add("VkRadioSubMenu");
	mCompField->add("VkRepeatButton");
	mCompField->add("VkResource");
	mCompField->add("VkSelectionDialog");
	mCompField->add("VkSimpleWindow");
	mCompField->add("VkSubMenu");
	mCompField->add("VkSubProcess");
	mCompField->add("VkTrace");
	mCompField->add("VkWarningDialog");
	mCompField->add("VkWidgetList");
	mCompField->add("VkWindow");
}

TestCompletion::~TestCompletion()
{
	delete mCompField;
}
