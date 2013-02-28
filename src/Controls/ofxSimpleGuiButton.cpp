
#include "ofxSimpleGuiButton.h"


ofxSimpleGuiButton::ofxSimpleGuiButton(string name, bool &value) : ofxSimpleGuiValueControl<bool>(name, value) {
	isPressed = false;
    oldValue = false;
    counter = 0;
	controlType = "Button";
	setup();
}

void ofxSimpleGuiButton::setup() {
	setSize(config->gridSize.x - config->padding.x, config->buttonHeight);
}


#ifndef OFXMSAGUI_DONT_USE_XML
void ofxSimpleGuiButton::loadFromXML(ofxXmlSettings &XML) {
	setValue(XML.getValue(controlType + "_" + key + ":value", 0));
    setFix((bool)(XML.getValue(controlType + "_" + key + ":isFixed", 0)));
}

void ofxSimpleGuiButton::saveToXML(ofxXmlSettings &XML) {
	XML.addTag(controlType + "_" + key);
	XML.pushTag(controlType + "_" + key);
	XML.addValue("name", name);
	XML.addValue("value", getValue());
    XML.addValue("isFixed", isFixed());
	XML.popTag();
}
#endif

void ofxSimpleGuiButton::keyPressed( int key ) {
	if(key==keyboardShortcut) toggle();
}



bool ofxSimpleGuiButton::getValue() {
	return (*value);
}

void ofxSimpleGuiButton::setValue(bool b) {
	(*value) = b;
}

void ofxSimpleGuiButton::toggle() {
	(*value) = !(*value);
}

void ofxSimpleGuiButton::onPress(int x, int y, int button) {
    if (oldValue) {
        string s;
        ofLog(OF_LOG_ERROR, "gui/" + controlType + "/" + name + "に入れているvalueがfalseに戻されていません。");
    }
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        isPressed = true;
        oldValue = (*value) = true;
    }
}

void ofxSimpleGuiButton::onRelease(int x, int y, int button) {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) return;
    else if (!isFixed()) {
        isPressed = false;
        oldValue = *value = false;
        counter++;
    }
}

void ofxSimpleGuiButton::draw(float x, float y) {
	setPos(x, y);
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	
	ofEnableAlphaBlending();
	ofFill();
	setTextBGColor(!isFixed());
	ofRect(0, 0, width, height);
    
	setTextColor(!isFixed());
    ofCircle(height/3, height/2, height /5);
    ofDrawBitmapString(name + " (" + ofToString(counter)+")", height - 15, 26);
	ofDisableAlphaBlending();
    
    fixButtonDraw();
	
	glPopMatrix();
}
