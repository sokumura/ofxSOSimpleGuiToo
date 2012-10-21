#pragma once

#include "ofxSimpleGuiControl.h"

#include "rangeSliderBase.h"


class rangeSliderInt : public rangeSliderBase<int> {
	
public:
	rangeSliderInt(string name, int &_valueS, int &_valueL, int min, int max) : rangeSliderBase<int>(name, _valueS, _valueL ,min, max) {
		controlType = "RangeSliderInt";
		//setIncrement(1);
	}

};
