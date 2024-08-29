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

#ifndef SLIDER_H
#define SLIDER_H

#include <Vk/VkComponent.h>
#include <Vk/VkRepeatButton.h>
#include <Vk/VkAction.h>
#include <Xm/Scale.h>
#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

#include <iostream>

class SliderAction;

class Slider : public VkComponent {
public:
	Slider(const char *name, Widget parent);

	virtual ~Slider();

	void setValue(int value, bool undoable = true);

	int getValue();

	void setLabel(const char*);

	void setRange(int min, int max);

	virtual const char* className() { return "Slider";}

	friend std::ostream& operator<<(std::ostream& os, Slider& me);

private:
	static const char* const _defaultResources[];

	Widget _scale;
	Widget _textf;
	Widget _label;

	int _min;
	int _max;
public:
	int _value;

	VkRepeatButton* _inc;
	VkRepeatButton* _dec;
	virtual void increment(VkCallbackObject* obj,
						   void* clientData,
						   void* callData);
	virtual void decrement(VkCallbackObject* obj,
						   void* clientData,
						   void* callData);
  
	static void scaleChangedCb(Widget w, XtPointer client_data,
							   XtPointer call_data);
	void scaleChanged(int value, bool undoable);

	static void textChangedCb(Widget w, XtPointer client_data,
							  XtPointer call_data);
	void textChanged(int value);

	SliderAction* mAction;
};


class SliderAction : public VkAction
{
public:
	SliderAction(const char* name, Slider* slider)
		: VkAction(name),
		  mSlider(slider)
		{}

	void doit() {
		mUndoValues.push_back(mSlider->_value);
	}

	void undoit() {
		mUndoValues.pop_back();
		mSlider->setValue(mUndoValues.back(), false);
	}

	Slider* mSlider;
	std::vector<int> mUndoValues;
};

#endif // SLIDER_H
