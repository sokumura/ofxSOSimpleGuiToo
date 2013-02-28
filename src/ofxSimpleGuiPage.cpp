#include "ofxSimpleGuiPage.h"

ofxSimpleGuiPage::ofxSimpleGuiPage(string name) : ofxSimpleGuiControl(name) {
	disableAllEvents();
	width = 0;
	height = ofGetHeight();
	eventStealingControl = NULL;
	setXMLName(name + "_settings.xml");
    
}

ofxSimpleGuiPage::~ofxSimpleGuiPage() {
	// delete all controls
}


ofxSimpleGuiPage &ofxSimpleGuiPage::setXMLName(string s) {
	xmlFilename = s;
	return *this;
}


void ofxSimpleGuiPage::loadFromXML() {
	ofLog(OF_LOG_VERBOSE, "ofxSimpleGuiPage::loadFromXML: " + xmlFilename);
#ifndef OFXMSAGUI_DONT_USE_XML
	
	if(xmlFilename.compare("") == 0) return;

	if(XML.loadFile(xmlFilename) == false) {
		ofLog(OF_LOG_ERROR, "Error loading xmlFilename: " + xmlFilename);
		return;
	}
	
	XML.pushTag("controls");
	for(int i=0; i < controls.size(); i++) {
		controls[i]->loadFromXML(XML);
	}
	XML.popTag();
#endif    
}


void ofxSimpleGuiPage::saveToXML() {
	if(controls.size() <= 1 || xmlFilename.compare("") == 0) return;	// if it has no controls (title counts as one control)
	
#ifndef OFXMSAGUI_DONT_USE_XML
	XML.clear();	// clear cause we are building a new xml file
	
	XML.addTag("controls");
	XML.pushTag("controls");
	for(int i=0; i < controls.size(); i++) {
		controls[i]->saveToXML(XML);
	}
	XML.popTag();
	
	XML.saveFile(xmlFilename);
	//	if(doSaveBackup) 
	ofLog(OF_LOG_VERBOSE, "ofxSimpleGuiPage::saveToXML: " + xmlFilename + " " + ofToString(controls.size(), 0) + " items");
#endif    
}


float ofxSimpleGuiPage::getNextY(float y) {
	return y;
	int iy = (int)ceil(y/config->gridSize.y);
	return (iy) * config->gridSize.y;
}


void ofxSimpleGuiPage::draw(float x, float y, bool alignRight) {
	setPos(x += config->offset.x, y += config->offset.y);
	if(alignRight) x = ofGetWidth() - x -  config->gridSize.x;
	
	int posX		= 0;
	int posY		= 0;
	int stealingX = 0;
	int stealingY = 0;
	
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	for(int i=0; i<controls.size(); i++) {
		ofxSimpleGuiControl &control = *controls[i];
        
        if(posY + y >= height - control.height - config->padding.y || control.newColumn) {
			if(alignRight) posX -= config->gridSize.x;
			else posX += config->gridSize.x;
			posY = 0;
		}
		
		float controlX = posX + x;
		float controlY = posY + y;
		
		//we don't draw the event stealing controls until the end because they can expand and overlap with other controls (e.g. combo box)
		if(eventStealingControl == &control) {
			stealingX = controlX;
			stealingY = controlY;
		} else {
//			printf("drawing control: %s %s\n", control.controlType.c_str(), control.name.c_str());
			control.draw(controlX, controlY);
		}
		
		if(control.hasTitle) {
			ofNoFill();
			ofSetHexColor(config->borderColor);
			glLineWidth(0.5f);
			ofRect(controlX, controlY, control.width, control.height);
		}
        
        if (control.isFixed()) {
            ofEnableAlphaBlending();
            ofFill();
            ofSetColor(33,33,33,80);
            ofRect(controlX, controlY, control.width, control.height);
            ofDisableAlphaBlending();
        }
        
		posY = getNextY(posY + control.height + config->padding.y);
		
		
		
		//		if(guiFocus == controls[i]->guiID) controls[i]->focused = true;		// MEMO
		//		else							   controls[i]->focused = false;
	}
	//event stealing controls get drawn on top
	if(eventStealingControl) {
		eventStealingControl->draw(stealingX, stealingY);
		if(eventStealingControl->hasTitle) {
			ofNoFill();
			ofSetHexColor(config->borderColor);
			glLineWidth(0.5f);
			ofRect(stealingX, stealingY, eventStealingControl->width, eventStealingControl->height);
		}
	}
    
    
}


ofxSimpleGuiControl &ofxSimpleGuiPage::addControl(ofxSimpleGuiControl& control) {
	controls.push_back(&control);
	width += control.width + config->padding.x;
	return control;
}

ofxSimpleGuiButton &ofxSimpleGuiPage::addButton(string name, bool &value) {
	return (ofxSimpleGuiButton &)addControl(* new ofxSimpleGuiButton(name, value));
}

ofxSimpleGuiContent &ofxSimpleGuiPage::addContent(string name, ofBaseDraws &content, float fixwidth) {
	if(fixwidth == -1) fixwidth = config->gridSize.x - config->padding.x;
	return (ofxSimpleGuiContent &)addControl(* new ofxSimpleGuiContent(name, content, fixwidth));
}

//ofxSimpleGuiFPSCounter &ofxSimpleGuiPage::addFPSCounter() {
//	return (ofxSimpleGuiFPSCounter &)addControl(* new ofxSimpleGuiFPSCounter());
//}

ofxSimpleGuiQuadWarp &ofxSimpleGuiPage::addQuadWarper(string name, ofBaseDraws &baseDraw, ofPoint *pts) {
	return (ofxSimpleGuiQuadWarp &)addControl(* new ofxSimpleGuiQuadWarp(name, baseDraw, pts));
}
//
//ofxSimpleGuiMovieSlider &ofxSimpleGuiPage::addMovieSlider(string name, ofVideoPlayer& input) {
//	return (ofxSimpleGuiMovieSlider &)addControl(* new ofxSimpleGuiMovieSlider(name, input));
//}

ofxSimpleGuiSliderInt &ofxSimpleGuiPage::addSlider(string name, int &value, int min, int max) {
	return (ofxSimpleGuiSliderInt &)addControl(* new ofxSimpleGuiSliderInt(name, value, min, max));
}

ofxSimpleGuiSliderFloat &ofxSimpleGuiPage::addSlider(string name, float &value, float min, float max) {
	return (ofxSimpleGuiSliderFloat &)addControl(* new ofxSimpleGuiSliderFloat(name, value, min, max));
}

rangeSliderInt &ofxSimpleGuiPage::addRangeSlider(string name, int &_valueS, int &_valueL, int min, int max){
    return (rangeSliderInt &)addControl(* new rangeSliderInt(name, _valueS, _valueL, min, max));
}

rangeSliderFloat &ofxSimpleGuiPage::addRangeSlider(string name, float &_valueS, float &_valueL, float min, float max){
    return (rangeSliderFloat &)addControl(* new rangeSliderFloat(name, _valueS, _valueL, min, max));
}

ofxSimpleGuiValueMonitorInt &ofxSimpleGuiPage::addValueMonitor(string _name, int &value){
	return (ofxSimpleGuiValueMonitorInt &)addControl(* new ofxSimpleGuiValueMonitorInt(_name, value));
}
ofxSimpleGuiValueMonitorFloat &ofxSimpleGuiPage::addValueMonitor(string _name, float &value){
    return (ofxSimpleGuiValueMonitorFloat &)addControl(* new ofxSimpleGuiValueMonitorFloat(_name, value));
}

ofxSimpleGuiSlider2d &ofxSimpleGuiPage::addSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax) {
	return (ofxSimpleGuiSlider2d &)addControl(* new ofxSimpleGuiSlider2d(name, value, xmin, xmax, ymin, ymax));
}

ofxSimpleGuiContentSlider2d	&ofxSimpleGuiPage::addContentSlider2d(string name, int nBlock, ofTexture & content, ofPoint& value, ofPoint& value2, float xmin, float xmax, float ymin, float ymax, bool bSecond) {
    return (ofxSimpleGuiContentSlider2d &)addControl(* new ofxSimpleGuiContentSlider2d(name, nBlock, content, value, value2, xmin, xmax, ymin, ymax, bSecond));
}

ofxSimpleGuiMulti2dSlider	&ofxSimpleGuiPage::addMulti2dSlider(string name, int nBlock, int pointNum, ofPoint * values, float xmin, float xmax, float ymin, float ymax, float sliderAspectWbyH, bool bBgTransparent, float offsetScale) {
    return (ofxSimpleGuiMulti2dSlider &)addControl(* new ofxSimpleGuiMulti2dSlider(name, nBlock, pointNum, values, xmin, xmax,  ymin, ymax, sliderAspectWbyH, bBgTransparent, offsetScale));
}

ofxSimpleGuiTitle &ofxSimpleGuiPage::addTitle(string name, float height) {
	return (ofxSimpleGuiTitle &)addControl(* new ofxSimpleGuiTitle(name, height));
}

ofxSimpleGuiToggle &ofxSimpleGuiPage::addToggle(string name, bool &value) {
	return (ofxSimpleGuiToggle &)addControl(* new ofxSimpleGuiToggle(name, value));
}

ofxSimpleGuiColorPicker &ofxSimpleGuiPage::addColorPicker(string name, ofFloatColor& color) {
	return (ofxSimpleGuiColorPicker &)addControl(* new ofxSimpleGuiColorPicker(name, color));
}


ofxSimpleGuiComboBox &ofxSimpleGuiPage::addComboBox(string name, int &choice_out, int numChoices, string* choiceTitles) {
	return (ofxSimpleGuiComboBox &)addControl(* new ofxSimpleGuiComboBox(name, choice_out, numChoices, this, choiceTitles));
}

ofxSimpleGuiBlank &ofxSimpleGuiPage::addBlank(string name, float height) {
	return (ofxSimpleGuiBlank &)addControl(* new ofxSimpleGuiBlank(name, height));
}


void ofxSimpleGuiPage::update(ofEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->update();
}

void ofxSimpleGuiPage::SetEventStealingControl(ofxSimpleGuiControl &control) {
	eventStealingControl = &control;
}
void ofxSimpleGuiPage::ReleaseEventStealingControl() {
	eventStealingControl = NULL;
}

void ofxSimpleGuiPage::mouseMoved(ofMouseEventArgs &e) {
	if(eventStealingControl)
		eventStealingControl->_mouseMoved(e);
	else
		for(int i=0; i<controls.size(); i++) controls[i]->_mouseMoved(e);
}

void ofxSimpleGuiPage::mousePressed(ofMouseEventArgs &e) {
	if(eventStealingControl)
		eventStealingControl->_mousePressed(e);
	else
		for(int i=0; i<controls.size(); i++) controls[i]->_mousePressed(e);
}

void ofxSimpleGuiPage::mouseDragged(ofMouseEventArgs &e) {
	if(eventStealingControl)
		eventStealingControl->_mouseDragged(e);
	else
		for(int i=0; i<controls.size(); i++) controls[i]->_mouseDragged(e);
}

void ofxSimpleGuiPage::mouseReleased(ofMouseEventArgs &e) {
	if(eventStealingControl)
		eventStealingControl->_mouseReleased(e);
	else
		for(int i=0; i<controls.size(); i++) controls[i]->_mouseReleased(e);
}

void ofxSimpleGuiPage::keyPressed(ofKeyEventArgs &e) {
	bool keyUp		= e.key == OF_KEY_UP;
	bool keyDown	= e.key == OF_KEY_DOWN;
	bool keyLeft	= e.key == OF_KEY_LEFT;
	bool keyRight	= e.key == OF_KEY_RIGHT;
	bool keyEnter	= e.key == OF_KEY_RETURN;
	
	for(int i=0; i<controls.size(); i++) {
		ofxSimpleGuiControl *c = controls[i];
		if(c->isMouseOver()) {
			if(keyUp)		c->onKeyUp();
			if(keyDown)		c->onKeyDown();
			if(keyLeft)		c->onKeyLeft();
			if(keyRight)	c->onKeyRight();
			if(keyEnter)	c->onKeyEnter();
			c->_keyPressed(e);
		}
	}
}

void ofxSimpleGuiPage::keyReleased(ofKeyEventArgs &e) {
	for(int i=0; i<controls.size(); i++) if(controls[i]->isMouseOver()) controls[i]->_keyReleased(e);
}


vector <ofxSimpleGuiControl*>&	ofxSimpleGuiPage::getControls() {
	return controls;
}

