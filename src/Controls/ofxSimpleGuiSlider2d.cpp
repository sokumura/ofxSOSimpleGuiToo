
#include "ofxSimpleGuiSlider2d.h"


ofxSimpleGuiSlider2d::ofxSimpleGuiSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax) : ofxSimpleGuiControl(name) {
	min.set(xmin, ymin);
	max.set(xmax, ymax);
	this->value = &value;
	controlType = "Slider2D";
    width = config->width; //他のcontrolと同じ。つもり。
    if (xmin > xmax) std::swap(xmin, xmax);
    if (ymin > ymax) std::swap(ymin, ymax);
    sliderHeight = width * (ymax - ymin) / (xmax - xmin);
    sliderTextHeight = config->slider2DTextHeight;
	setup();
}

void ofxSimpleGuiSlider2d::setup() {
	setSize(width, sliderHeight + config->slider2DTextHeight);
	point.x = ofMap((*value).x, min.x, max.x, 0.0f, width);
	point.y = ofMap((*value).y, min.y, max.y, 0.0f, sliderHeight);
    
}

#ifndef OFXMSAGUI_DONT_USE_XML
void ofxSimpleGuiSlider2d::loadFromXML(ofxXmlSettings &XML) {
	value->set(XML.getValue(controlType + "_" + key + ":valueX", 0.0f), XML.getValue(controlType + "_" + key + ":valueY", 0.0f));
    point.x = ofMap((*value).x, min.x, max.x, 0.0f, width);
	point.y = ofMap((*value).y, min.y, max.y, 0.0f, sliderHeight);
    setFix((bool)(XML.getValue(controlType + "_" + key + ":isFixed", 0)));
    
}


void ofxSimpleGuiSlider2d::saveToXML(ofxXmlSettings &XML) {
	XML.addTag(controlType + "_" + key);
	XML.pushTag(controlType + "_" + key);
	XML.addValue("name", name);
	XML.addValue("valueX", value->x);
	XML.addValue("valueY", value->y);
    XML.addValue("isFixed", isFixed());
	XML.popTag();
}
#endif

void ofxSimpleGuiSlider2d::setValue(float x, float y) {
	(*value).x = x;
	(*value).y = y;
}

void ofxSimpleGuiSlider2d::setMin(float x, float y) {
	min.x = x;
	min.y = y;
}

void ofxSimpleGuiSlider2d::setMax(float x, float y) {
	max.x = x;
	max.y = y;
}

void ofxSimpleGuiSlider2d::onPress(int x, int y, int button) {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        lock = true;
        point.set(x - this->x, y - this->y - sliderTextHeight);
    }
}

void ofxSimpleGuiSlider2d::onDragOver(int x, int y, int button) {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        if (lock) point.set(x - this->x, y - this->y - sliderTextHeight);
    }
	
}

void ofxSimpleGuiSlider2d::onDragOutside(int x, int y, int button) {
	bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        if (lock) point.set(x - this->x, y - this->y - sliderTextHeight);
    }
}

void ofxSimpleGuiSlider2d::onRelease() {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        lock = false;
    }
}

void ofxSimpleGuiSlider2d::update() {
    //判定
    point.x = ofClamp(point.x, 0.0f, width);
    point.y = ofClamp(point.y, 0.0f, sliderHeight);
	
	if(lock){
		(*value).x = ofMap(point.x, 0, width, min.x, max.x);
		(*value).y = ofMap(point.y, 0, sliderHeight, min.y, max.y);
	}
}

void ofxSimpleGuiSlider2d::draw(float x, float y) {
	setPos(x, y);
//	ofPoint	pointv;
//	pointv.x = ofMap((*value).x, min.x, max.x, x, x+width);
//	pointv.y = ofMap((*value).y, min.y, max.y, y, y+sliderHeight);
	
	ofEnableAlphaBlending();
	glPushMatrix();
	glTranslatef(x, y, 0);
	
    ofFill();
	setTextBGColor(!isFixed());
	ofRect(0, 0, width, sliderTextHeight);
	
	setTextColor(!isFixed());
	ofDrawBitmapString(name+"\nx:"+ofToString(value->x, 2)+"\ny:"+ofToString(value->y, 2), 6, 15);
    
	set2DSliderBGColor(!isFixed());
	ofRect(0, sliderTextHeight, width, sliderHeight);
	
    ofTranslate((int)0.0f, (int)sliderTextHeight);

    ofSetHexColor(0xFFFFFF);
    ofCircle(point.x, point.y, 2);
	ofLine(point.x, 0, point.x, sliderHeight);
	ofLine(0, point.y,width, point.y);
    
    ofRectangle maxxB = base64GetStringBoundingBox("X:" + ofToString(max.x));
    //ofRectangle maxyB = base64GetStringBoundingBox("maxY:" + ofToString(max.y));
    string valueString = "(" + ofToString((*value).x) + "," + ofToString((*value).y) + ")";
    ofRectangle valueStringBox = base64GetStringBoundingBox(valueString);
    
    base64DrawBitmapString("(" + ofToString(min.x) + "," + ofToString(min.y) + ")", 1, 2);
    base64DrawBitmapString("X:" + ofToString(max.x), width - maxxB.width - 1, 2);
    base64DrawBitmapString("Y:" + ofToString(max.y), 1, sliderHeight - maxxB.height -1);
    if (width/2 > point.x && sliderHeight/2 > (point.y - y)){ //左上にあるとき
        base64DrawBitmapString(valueString, point.x + 3, point.y + 3);
    } else if (width/2 < point.x && sliderHeight/2 > (point.y)) {//右上
        base64DrawBitmapString(valueString, point.x - valueStringBox.width - 3, point.y + 3);
    } else if (width/2 > point.x && sliderHeight/2 < point.y) {//左下
        base64DrawBitmapString(valueString, point.x + 3, point.y - valueStringBox.height - 3);
    } else {//右下
        base64DrawBitmapString(valueString, point.x - valueStringBox.width - 3, point.y - valueStringBox.height - 3);
	}
    ofTranslate(0, 0 - (int)sliderTextHeight);
    fixButtonDraw();
	glPopMatrix();
	ofDisableAlphaBlending();
	
}