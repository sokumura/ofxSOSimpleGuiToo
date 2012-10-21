#pragma once

#include "ofxSimpleGuiControl.h"

#include "ofxSimpleGuiValueMonitorBase.h"


class ofxSimpleGuiValueMonitorInt : public ofxSimpleGuiValueMonitorBase<int> {
	
public:
	ofxSimpleGuiValueMonitorInt(string name, int &value) : ofxSimpleGuiValueMonitorBase<int>(name, value) {
		controlType = "ValueMonitorInt";
	}

};
