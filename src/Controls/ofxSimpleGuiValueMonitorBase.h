#pragma once

#include "ofxSimpleGuiControl.h"

template <typename Type> class ofxSimpleGuiValueMonitorBase : public ofxSimpleGuiControl {
public:
    
    Type  *value;
    
	ofxSimpleGuiValueMonitorBase(string _name, Type &value) : ofxSimpleGuiControl(_name){
        this->value = &value;
        controlType = "ValueMonitroBase";
        setup();
    }	
	void setup(){
        setSize(config->gridSize.x - config->padding.x, config->defaultHeight);
    }
#ifndef OFXMSAGUI_DONT_USE_XML
    void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
		XML.popTag();
	}
#endif
    
	Type getValue() {
		return (*value);
	}
    
	void draw(float x, float y){
        setPos(x, y);
        
        glPushMatrix();
        glTranslatef(x, y, 0);
        
        //	ofEnableAlphaBlending();
        //	ofFill();
        //	setTextBGColor(false);
        //	ofRect(0, 0, width, height);
        
        setTextColor(false);
        ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 6, 26);
        
        glPopMatrix();
    }
};
