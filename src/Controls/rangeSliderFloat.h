#pragma once

#include "ofxSimpleGuiControl.h"

#include "rangeSliderBase.h"


class rangeSliderFloat : public rangeSliderBase<float> {
	
public:
	rangeSliderFloat(string name, float &_valueS, float &_valueL, float min, float max) : rangeSliderBase<float>(name, _valueS, _valueL, min, max) {
		controlType = "RangeSliderFloat";
	}
};
