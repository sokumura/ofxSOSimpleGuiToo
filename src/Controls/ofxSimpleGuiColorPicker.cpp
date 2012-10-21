/*
 *  ofxSimpleGuiColorPicker.cpp
 *  OpenCL Particles 3. single segment trails
 *
 *  Created by Mehmet Akten on 01/11/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxSimpleGuiColorPicker.h"

ofxSimpleGuiColorPicker::ofxSimpleGuiColorPicker(string name, ofFloatColor& color, float max) : ofxSimpleGuiControl(name) {
	this->value = &color;
	this->min	= 0;
	this->max	= max;
	
	controlType = "ColorPicker";
	setup();
}

void ofxSimpleGuiColorPicker::setup() {
	setSize(config->gridSize.x - config->padding.x, config->sliderHeight * 8 + config->colorPickerTextHeight);
	for(int i=0; i<4; i++) {
		pct[i] = ofMap(getValue(i), 0, max, 0.0, width);
		barwidth[i] = pct[i];
	}
}

#ifndef OFXMSAGUI_DONT_USE_XML
void ofxSimpleGuiColorPicker::loadFromXML(ofxXmlSettings &XML) {
	for(int i=0; i<4; i++) {
		setValue(XML.getValue(controlType + "_" + key + ":values_" + ofToString(i), 0.0f), i);
	}
    setFix((bool)(XML.getValue(controlType + "_" + key + ":isFixed", 0)));
}

void ofxSimpleGuiColorPicker::saveToXML(ofxXmlSettings &XML) {
	XML.addTag(controlType + "_" + key);
	XML.pushTag(controlType + "_" + key);
	XML.addValue("name", name);
	for(int i=0; i<4; i++) {
		XML.addValue("values_" + ofToString(i), getValue(i));
	}
    XML.addValue("isFixed", isFixed());
	XML.popTag();
}
#endif


float ofxSimpleGuiColorPicker::getValue(int i) const {
	return value->v[i];
}


void ofxSimpleGuiColorPicker::setValue(float f, int i) {
	if(f < min) f = min;
	else if(f > max) f = max;
	value->v[i] = f;
}


void ofxSimpleGuiColorPicker::updateSlider() {
	if(!enabled) return;
	
	int i= (getMouseY() - y - config->colorPickerTextHeight) / config->sliderHeight / 2;
	if(i<0 || i>=4) return;
	
	if(pct[i] > width || pct[i] < 0.0f) {
		ofClamp(pct[i], 0.0f, (float)width);
	}
	else {
		pct[i] = getMouseX() - x;
		setValue(ofMap(pct[i], 0.0, (float)width, 0, max), i);
	}
}

void ofxSimpleGuiColorPicker::onPress(int x, int y, int button) {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        updateSlider();
    }
	
}

void ofxSimpleGuiColorPicker::onDragOver(int x, int y, int button) {
	bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        updateSlider();
    }
}

void ofxSimpleGuiColorPicker::onDragOutside(int x, int y, int button) {
	bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        updateSlider();
    }
}



//--------------------------------------------------------------------- update
void ofxSimpleGuiColorPicker::update() {
	if(!enabled) return;
	
	if(lock) {
		updateSlider();
	}
	
//	enabled = false;
}

//--------------------------------------------------------------------- draw
void ofxSimpleGuiColorPicker::draw(float x, float y) {
	
//	enabled = true;
	
	//update postion of gui object
	setPos(x, y);
	glPushMatrix();
	glTranslatef(x, y, 0);
    
    ofFill();
	
	setTextBGColor(!isFixed());
	ofRect(0, 0, width, config->colorPickerTextHeight + config->sliderHeight * 8);
    
	glColor3f(getValue(0), getValue(1), getValue(2));
	ofRect(5, 24, width - 11, config->colorPickerTextHeight * 0.6);//完成色
	
	setTextColor(!isFixed());//タイトルテキスト
	string s = name;
	ofDrawBitmapString(s, 6, 16);
	ofDisableAlphaBlending();
	
	int startY = config->colorPickerTextHeight;
	for(int i=0; i<4; i++) {
		
		barwidth[i] = ofMap(getValue(i), 0, max, 0.0, (float)width);//幅
		//if(barwidth[i] > width)	barwidth[i] = width;//
		//else if(barwidth[i] < 0) barwidth[i] = 0;
        ofClamp(barwidth[i], 0, width);
		
		ofEnableAlphaBlending();
		ofFill();
		setEmptyColor();
		ofRect(0, startY, width, config->sliderHeight*1.8);
		
	
		switch(i) {
			case 0:glColor3f(getValue(i), 0, 0); break;
			case 1:glColor3f(0, getValue(i), 0); break;
			case 2:glColor3f(0, 0, getValue(i)); break;
			case 3:glColor3f(getValue(i), getValue(i), getValue(i)); break;
		}
		
		ofRect(0, startY, barwidth[i], config->sliderHeight * 1.8);
		
        glColor3f(1.0f, 1.0f, 1.0f);
		if ((i == 3 || i ==1) && barwidth[i] > width * 0.7) {
            glColor3f(0.1f, 0.1f, 0.1f);
        }
        
		base64DrawBitmapString(ofToString(getValue(i), 4), 3, startY + 4);
        
		startY += config->sliderHeight * 2;
	}
	
    fixButtonDraw();
	
	glPopMatrix();
}
