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

//
// Slider.cc
//
static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: Slider.cc,v 1.12 2009/03/21 11:44:34 jostle Exp $";

#include <cstdlib>
#include <stdio.h>

#include <Vk/VkAction.h>

#include "Slider.h"

using namespace std;

const char* const Slider::_defaultResources[] = {
	"*background : #b0c4dc",
	"*shadowThickness : 1",
	"*highlightThickness : 1",
	"*label.labelString : Scale Label",
	NULL
};

Slider::Slider(const char *name, Widget parent):
	VkComponent(name),
	_min(0),
	_max(100),
	_value(0)
{
	// Load class-default resources for this object before creating base widget
	setDefaultResources(parent, _defaultResources );

	_baseWidget = XtVaCreateWidget(_name,
								   xmFormWidgetClass,
								   parent, NULL);
	installDestroyHandler();


	_label = XtVaCreateManagedWidget("label", xmLabelWidgetClass,
									 _baseWidget,
									 XmNleftAttachment, XmATTACH_FORM,
									 XmNtopAttachment, XmATTACH_FORM,
									 XmNbottomAttachment, XmATTACH_NONE,
									 NULL);

	_textf = XtVaCreateManagedWidget("textf", xmTextFieldWidgetClass,
									 _baseWidget,
									 XmNrightAttachment, XmATTACH_FORM,
									 XmNtopAttachment, XmATTACH_FORM,
									 XmNbottomAttachment, XmATTACH_NONE,
									 XmNhighlightThickness, 0,
									 XmNcolumns, 3,
									 XmNmarginWidth, 1,
									 XmNmarginHeight, 1,
									 XmNcursorPositionVisible, False,
									 NULL);
	XtAddCallback(_textf, XmNactivateCallback, textChangedCb, this);

	Widget inc_dec =
		XtVaCreateManagedWidget("up_down_form", xmFormWidgetClass,
								_baseWidget,
								XmNleftAttachment, XmATTACH_NONE,
								XmNrightAttachment, XmATTACH_WIDGET,
								XmNrightWidget, _textf,
								XmNtopAttachment, XmATTACH_FORM,
								XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
								XmNbottomWidget, _textf,
								NULL);

	_inc = new VkRepeatButton("inc", inc_dec, RB_arrowButton);
	XtVaSetValues(_inc->baseWidget(),
				  XmNarrowDirection, XmARROW_UP,
				  XmNshadowThickness, 0,
				  XmNmarginWidth, 0,
				  XmNmarginHeight, 0,
				  XmNhighlightThickness, 0,
				  XmNrightAttachment, XmATTACH_FORM,
				  XmNtopAttachment, XmATTACH_FORM,
				  XmNbottomAttachment, XmATTACH_POSITION,
				  XmNbottomPosition, 49,
				  NULL);
	_inc->addCallback(VkRepeatButton::buttonCallback, this,
					  (VkCallbackMethod)&Slider::increment);

	_dec = new VkRepeatButton("dec", inc_dec, RB_arrowButton);
	XtVaSetValues(_dec->baseWidget(),
				  XmNarrowDirection, XmARROW_DOWN,
				  XmNshadowThickness, 0,
				  XmNmarginWidth, 0,
				  XmNmarginHeight, 0,
				  XmNhighlightThickness, 0,
				  XmNrightAttachment, XmATTACH_FORM,
				  XmNtopAttachment, XmATTACH_WIDGET,
				  XmNtopWidget, _inc->baseWidget(),
				  XmNbottomAttachment, XmATTACH_FORM,
				  NULL);
	_dec->addCallback(VkRepeatButton::buttonCallback, this,
					  (VkCallbackMethod)&Slider::decrement);

	_scale = XtVaCreateManagedWidget("scale", xmScaleWidgetClass,
									 _baseWidget,
									 XmNorientation, XmHORIZONTAL,
									 XmNleftAttachment, XmATTACH_WIDGET,
									 XmNleftWidget, _label,
									 XmNrightAttachment, XmATTACH_WIDGET,
									 XmNrightWidget, inc_dec,
									 XmNtopAttachment, XmATTACH_FORM,
									 XmNbottomAttachment, XmATTACH_NONE,
									 NULL);
#if XmVERSION >= 2
	XtVaSetValues(_scale,
				  XmNsliderMark, XmTHUMB_MARK,
				  XmNshowArrows, XmEACH_SIDE,
				  NULL);
#endif
  
	XtAddCallback(_scale, XmNvalueChangedCallback, scaleChangedCb, this);
	XtAddCallback(_scale, XmNdragCallback, scaleChangedCb, this);

	// Create an undoable action
	mAction = new SliderAction("Slider Change", this);
}

Slider::~Slider()
{
	delete _dec;
	delete _inc;
	delete mAction;
}

void
Slider::setValue(int value, bool undoable)
{
	// Need to set up the initial Undo value.	
	static bool initialised = false;
	
	// Constrain setting to the valid range
	value = std::max(value, _min);
	value = std::min(value, _max);
  
	XtVaSetValues(_scale, XmNvalue, value, NULL);
	char textVal[32];
	sprintf(textVal, "%d", value);
	XtVaSetValues(_textf, XmNvalue, textVal, NULL);

	_value = value;

	if (!initialised) {
		mAction->doit();
		initialised = true;
	} else if (undoable) {
		mAction->execute();
	}
}


int
Slider::getValue()
{
	return _value;
}

void
Slider::setLabel(const char* label)
{
	XmString lab = XmStringCreateLocalized(const_cast<char*>(label));
	XtVaSetValues(_label, XmNlabelString, lab, NULL);
	XmStringFree(lab);
}

void
Slider::setRange(int min, int max)
{
	int curr = getValue();
	if (curr < min) curr = min;
	if (curr > max) curr = max;

	XtVaSetValues(_scale,
				  XmNvalue, curr,
				  XmNminimum, min,
				  XmNmaximum, max,
				  NULL);
	_min = min;
	_max = max;
}

void
Slider::scaleChangedCb(Widget w, XtPointer clientData, XtPointer call_data)
{
	int newVal = ((XmScaleCallbackStruct*)call_data)->value;
	int reason = ((XmScaleCallbackStruct*)call_data)->reason;
	Slider* me = (Slider*)clientData;

	// No undo for a DRAG callback
	me->scaleChanged(newVal, reason == XmCR_VALUE_CHANGED);
}

void
Slider::scaleChanged(int value, bool undoable)
{
	setValue(value, undoable);
}

void
Slider::textChangedCb(Widget w, XtPointer clientData, XtPointer call_data)
{
	char* newValChar;
	XtVaGetValues(w, XmNvalue, &newValChar, NULL);
	Slider* me = (Slider*)clientData;

	me->textChanged(atoi(newValChar));
	XtFree(newValChar);
}

void
Slider::textChanged(int value)
{
	setValue(value, true);
}

ostream& operator<<(ostream& os, Slider& me)
{
	os << "Slider : " << me._name << " Value = " << me.getValue() << endl;
	return os;
}

void
Slider::increment(VkCallbackObject* obj,
				  void* clientData,
				  void* callData)
{
	setValue(_value + 1, false);
}

void
Slider::decrement(VkCallbackObject* obj,
				  void* clientData,
				  void* callData)
{
	setValue(_value - 1, false);
}

