
#include "ofxSimpleGuiToggle.h"


ofxSimpleGuiToggle::ofxSimpleGuiToggle(string name, bool &value) : ofxSimpleGuiControl(name) {
	this->value	= &value;
	setMomentary(false);
	controlType = "Toggle";
	setup();
}

ofxSimpleGuiToggle& ofxSimpleGuiToggle::setMomentary(bool m) {
	momentary = m;
	return *this;
}


void ofxSimpleGuiToggle::setup() {
	setSize(config->gridSize.x - config->padding.x, config->toggleHeight);
}

#ifndef OFXMSAGUI_DONT_USE_XML
void ofxSimpleGuiToggle::loadFromXML(ofxXmlSettings &XML) {
	setValue(XML.getValue(controlType + "_" + key + ":value", 0));
    setFix((bool)(XML.getValue(controlType + "_" + key + ":isFixed", 0)));
}

void ofxSimpleGuiToggle::saveToXML(ofxXmlSettings &XML) {
	XML.addTag(controlType + "_" + key);
	XML.pushTag(controlType + "_" + key);
	XML.addValue("name", name);
	XML.addValue("value", getValue());
    XML.addValue("isFixed", isFixed());
	XML.popTag();
}
#endif

bool ofxSimpleGuiToggle::getValue() {
	return (*value);
}

void ofxSimpleGuiToggle::setValue(bool b) {
	(*value) = b;
}

void ofxSimpleGuiToggle::toggle() {
	(*value) = !(*value); 
}

void ofxSimpleGuiToggle::onPress(int x, int y, int button) {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        if(momentary) setValue(true);
        else toggle();
    }
}

void ofxSimpleGuiToggle::onRelease(int x, int y, int button) {
	if(momentary) setValue(false);
}

void ofxSimpleGuiToggle::keyPressed( int key ) {
	if(key==keyboardShortcut) onPress(0, 0, 0);
}

void ofxSimpleGuiToggle::keyReleased( int key ) {
	if(key==keyboardShortcut) onRelease(0, 0, 0);
}

void ofxSimpleGuiToggle::onKeyEnter() {
	toggle();
}

void ofxSimpleGuiToggle::update() {
//	if(!enabled) return;
//	enabled = false;
}

void ofxSimpleGuiToggle::draw(float x, float y) {
//	enabled = true;
	setPos(x, y);
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	
	ofEnableAlphaBlending();
	ofFill();
    
    setTextBGColor(!isFixed());
	ofRect(0, 0, width, height);
    
	//setFullColor(*value);
    if (*value) ofSetHexColor(config->fullActiveColor);
    else ofSetHexColor(config->emptyColor);
	ofRect(6, 6, height-12, height-12);
	
	setTextColor(!isFixed());
	ofDrawBitmapString(name, height + 8, 26);
	ofDisableAlphaBlending();
    ofSetHexColor(0xFFFFFF);
    if (*value) ofDrawBitmapString("YES", height/3 - 4, height/2 + 5);
    else {
        ofDrawBitmapString("NO", height/3, height/2 + 5);
    }
    
    fixButtonDraw();
	
	glPopMatrix();
}

