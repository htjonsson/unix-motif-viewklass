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
	= "$Id: VkCompletionField.C,v 1.6 2009/03/21 11:44:34 jostle Exp $";

#include <Xm/TextF.h>

#include <Vk/VkApp.h>
#include <Vk/VkResource.h>
#include <Vk/VkNameList.h>
#include <Vk/VkCompletionField.h>

using namespace std;

const char* const
VkCompletionField::_defaultResources[] = {
	"*marginHeight: 1",
	"*marginWidth: 2",
	NULL
};

VkCompletionField::VkCompletionField(const char *name, Widget parent)
	: VkComponent(name),
	  _currentMatchList(0),
	  _nameList(0)
{
	setDefaultResources(parent, _defaultResources);

	_baseWidget = XtVaCreateWidget(_name, xmTextFieldWidgetClass,
								   parent, NULL);
	installDestroyHandler();

	XtAddCallback(_baseWidget, XmNmodifyVerifyCallback, modifyCallback, this);
	XtAddCallback(_baseWidget, XmNactivateCallback, activateCallback, this);

	_nameList = new VkNameList();
	_currentMatchList = new VkNameList();
}

VkCompletionField::~VkCompletionField()
{
	delete _nameList;
	delete _currentMatchList;
}

const char*
VkCompletionField::getText()
{
	char* text;
	XtVaGetValues(_baseWidget, XmNvalue, &text, NULL);
	return text;
}

void
VkCompletionField::add(const char* name)
{
	_nameList->add(name);
}

void
VkCompletionField::clear()
{
	_nameList->remove(0, _nameList->size());
	_currentMatchList->remove(0, _currentMatchList->size());
}

void
VkCompletionField::expand(XmTextVerifyCallbackStruct* cbs)
{
	//**********************************
	// WARNING - The actual struct passed to this callback from
	// the activateCallback function is an XmAnyCallbackStruct.
	// It only gets an XmTextVerifyCallbackStruct from the
	// modifyCallback function.
	// An XmAnyCallbackStruct ONLY CONTAINS reason and event fields.
	
	// Sorry for the following clumsy construct but I want to make
	// it absolutely clear that the XmCR_ACTIVATE case needs to be
	// handled differently.
	bool expand = false;
	if (cbs->reason == XmCR_ACTIVATE) {
		expand = true;
	} else if (cbs->text && cbs->text->ptr && cbs->text->ptr[0] == ' ') {
		expand = true;
	}
	
	// Default behaviour is to attempt an expansion when
	// the user types a space or enter.
	// Override this method in a sub-class for different behaviour.

	if (expand) {
		char* newText;
		int nMatches;
		const char* getText;
		XtVaGetValues(_baseWidget, XmNvalue, &getText, NULL);
		string newString = getText;
		XtFree(const_cast<char*>(getText));
		
		if (cbs->reason != XmCR_ACTIVATE) {
			// Ignore spaces; they are only used to trigger expansion
			if (cbs->text->ptr[0] == ' ') cbs->text->ptr[0] = '\0'; 
			newString.erase(cbs->startPos, cbs->endPos - cbs->startPos);
			newString.insert(cbs->startPos, cbs->text->ptr);
		}

		delete _currentMatchList;
		_currentMatchList = _nameList->completeName(
			newString.c_str(), newText, nMatches);
		if (newText != 0) {
			XtVaSetValues(_baseWidget,
						  XmNvalue, newText,
						  XmNcursorPosition, strlen(newText),
						  NULL);
		}
		delete [] newText;
		// Tell the text field not to bother;
		// we've already set the value we want.
		cbs->doit = false;
	}
}

void
VkCompletionField::activate(XmTextVerifyCallbackStruct* cbs)
{
	//**********************************
	// WARNING - The actual struct passed to this callback
	// is an XmAnyCallbackStruct. ViewKit defines this method
	// as taking an XmTextVerifyCallbackStruct.
	// Don't believe them!
	
	// Override this method in a sub-class or use the enterCallback.
}

void
VkCompletionField::activateCallback(Widget w, XtPointer clientData,
									XtPointer callData)
{
	VkCompletionField* me = (VkCompletionField*)clientData;
	//**********************************
	// WARNING - The actual struct passed to this callback
	// is an XmAnyCallbackStruct. ViewKit defines the methods
	// activate() and expand() as taking an XmTextVerifyCallbackStruct
	// which has more fields.
	XmTextVerifyCallbackStruct* cbs =
		(XmTextVerifyCallbackStruct*)callData;

	me->expand(cbs);
	me->callCallbacks(enterCallback, cbs);
	me->activate(cbs);
}

void
VkCompletionField::modifyCallback(Widget w, XtPointer clientData,
								  XtPointer callData)
{
	VkCompletionField* me = (VkCompletionField*)clientData;        
	XmTextVerifyCallbackStruct* cbs =
		(XmTextVerifyCallbackStruct*)callData;

	me->expand(cbs);
}

const char* const
VkCompletionField::enterCallback = "VkCompletionField::enterCallback";
