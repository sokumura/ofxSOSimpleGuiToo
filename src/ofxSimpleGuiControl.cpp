#include "ofxSimpleGuiControl.h"


ofxSimpleGuiControl::ofxSimpleGuiControl(string name) {
	controlType = "";
	this->config = &defaultSimpleGuiConfig;
	setName(name);
	setKey(key);
	setPos(0, 0);
	lock	  = false;
	focused	  = false;
	newColumn = false;
	setKeyboardShortcut(0);
    fixed     = false;
    bDrawFixButton = true;
    fixboxWidth = 8.0f;
	setup();
	
	disableAllEvents();		// just for safety to make sure nothing is registered twice
//	enableAppEvents();
//	enableMouseEvents();
//	disableKeyEvents();
}

ofxSimpleGuiControl &ofxSimpleGuiControl::setConfig(ofxSimpleGuiConfig *config) {
	this->config = config;
	setup();
	return *this;
}

ofxSimpleGuiControl &ofxSimpleGuiControl::setNewColumn(bool b) {
	newColumn = b;
	return *this;
}



ofxSimpleGuiControl &ofxSimpleGuiControl::setName(string newName) {
	name = newName;
	origName = name;
	if(key.compare("") == 0) setKey("");	// if key has not been set yet, set name as key too
	
	hasTitle = (name.compare("") != 0);
	return *this;
}


ofxSimpleGuiControl &ofxSimpleGuiControl::setKey(string newKey) {
	if(newKey.compare("") == 0) key = name;
	else key = newKey;
	for(int i=0; i<key.size(); i++) {
		if(key[i] == ' ') key[i] = '_';
	}
	return *this;
}

ofxSimpleGuiControl &ofxSimpleGuiControl::setTextColor(bool clickable) {
	if(isMouseOver() && clickable) ofSetHexColor(config->textOverColor);
	else ofSetHexColor(config->textColor);
	return *this;
}

ofxSimpleGuiControl &ofxSimpleGuiControl::setTextBGColor(bool clickable) {
	if(isMouseOver() && clickable) ofSetHexColor(config->textBGOverColor);
	else ofSetHexColor(config->textBGColor);
	return *this;
}

ofxSimpleGuiControl &ofxSimpleGuiControl::setFullColor(bool forceActive) {
	if(isMouseDown() || forceActive) ofSetHexColor(config->fullActiveColor);
	else if(isMouseOver()) ofSetHexColor(config->fullOverColor);
	else ofSetHexColor(config->fullColor);
	return *this;
}

ofxSimpleGuiControl &ofxSimpleGuiControl::set2DSliderBGColor(bool clickable) {
	if(isMouseDown() || isMouseOver() || clickable) ofSetHexColor(config->fullActiveColor);
	else ofSetHexColor(config->emptyColor);
	return *this;
}


ofxSimpleGuiControl &ofxSimpleGuiControl::setEmptyColor() {
	ofSetHexColor(config->emptyColor);
	//		if(isMouseOver()) ofSetHexColor(config->overColor.r, config->overColor.g, config->overColor.b);
	//		if(focused && !isMouseOver()) ofSetHexColor(config->focusColor.r, config->focusColor.g, config->focusColor.b);
	return *this;
}

ofxSimpleGuiControl &ofxSimpleGuiControl::setKeyboardShortcut(char c) {
	keyboardShortcut = c;
	if(c) {
	//	printf("ofxSimpleGuiControl::setKeyboardShortcut %s %c\n", name.c_str(), c);
		name = origName + " (" + c + ")";
	} else {
		name = origName;
	}
	return *this;
}

bool ofxSimpleGuiControl::isFixed() const {
    return fixed;
}

void ofxSimpleGuiControl::toggleFix() {
    fixed = !fixed;
    
}

void ofxSimpleGuiControl::fixButtonDraw() {
    if (!bDrawFixButton) return;
    ofFill();
    if (fixed) {
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, 80);
        ofRect(0.0f, 0.0f, width, height);
        ofDisableAlphaBlending();
        ofSetHexColor(config->textBGColor);
    }
    else ofSetHexColor(config->emptyColor);
    ofRect(width - fixboxWidth, 0.0f, fixboxWidth, fixboxWidth);
    if(!fixed)ofSetHexColor(0xFFFFFF);
    else ofSetHexColor(config->borderColor);
    ofSetLineWidth(0.5);
    ofLine(width - fixboxWidth, 0.0f, width, fixboxWidth);
    ofLine(width - fixboxWidth, fixboxWidth, width, 0.0f);
    ofNoFill();
    ofSetHexColor(config->borderColor);
    ofRect(width - fixboxWidth, 0.0f, fixboxWidth, fixboxWidth);
}

void ofxSimpleGuiControl::setFix(bool fix){
    fixed = fix;
}

void ofxSimpleGuiControl::disableFix(){
    bDrawFixButton = false;
}
void ofxSimpleGuiControl::enableFix(){
    bDrawFixButton = true;
}