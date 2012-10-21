#pragma once

#include "ofxSimpleGuiControl.h"

#include "ofxSimpleGuiValueMonitorBase.h"


class ofxSimpleGuiValueMonitorFloat : public ofxSimpleGuiValueMonitorBase<float> {
	
public:
	ofxSimpleGuiValueMonitorFloat(string name, float &value) : ofxSimpleGuiValueMonitorBase<float>(name, value) {
		controlType = "ValueMonitorFloat";
	}
};
