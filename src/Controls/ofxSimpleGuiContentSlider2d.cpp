
#include "ofxSimpleGuiContentSlider2d.h"


ofxSimpleGuiContentSlider2d::ofxSimpleGuiContentSlider2d(string name, int nBlock, ofTexture & content, ofPoint& value, ofPoint & value2,float xmin, float xmax, float ymin, float ymax, bool bSecond) : ofxSimpleGuiControl(name) {
    this->content = &content;
	this->fixwidth  = nBlock * config->width + (nBlock - 1) * config->padding.x;
    this->secBtnPos = config->secBtnPos;
    this->secBtnPos.y + 1.0f;
	controlType = "ContentSlider2D";
    
    if (xmin > xmax) std::swap(xmin, xmax);
    if (ymin > ymax) std::swap(ymin, ymax);
	min.set(xmin, ymin);
	max.set(xmax, ymax);
	this->value = &value;
    this->value2 = &value2;
	
    width = fixwidth;
    
    sliderTextHeight = config->slider2DTextHeight;
    
    if (nBlock == 0) {
        ofLog(OF_LOG_ERROR, "ofxSimpleGuiContentSlider2d で nBlockに0が入っている。1以上にすべし。\n");
    }
    if (nBlock > 6) {
        ofLog(OF_LOG_WARNING, "ofxSimpleGuiContentSlider2d で nBlockに7以上の数字が入ってます。大き過ぎて画面に入らないと思います。\n");
    }
    
	setup();
}

void ofxSimpleGuiContentSlider2d::setup() {
    fixheight = fixwidth * content->getHeight()/content->getWidth();
    sliderHeight = fixheight;
	setSize(fixwidth, fixheight + sliderTextHeight);
    
	point.x = ofMap((*value).x, min.x, max.x, 0.0f, fixwidth);
	point.y = ofMap((*value).y, min.y, max.y, 0.0f, sliderHeight);
    
    point2.set(fixwidth, sliderHeight);
    
    secondPointBoxWidth = fixboxWidth * 2.0f;
}

#ifndef OFXMSAGUI_DONT_USE_XML
void ofxSimpleGuiContentSlider2d::loadFromXML(ofxXmlSettings &XML) {
	value->set(XML.getValue(controlType + "_" + key + ":valueX", 0.0f), XML.getValue(controlType + "_" + key + ":valueY", 0.0f));
    point.x = ofMap((*value).x, min.x, max.x, 0.0f, fixwidth);
	point.y = ofMap((*value).y, min.y, max.y, 0.0f, fixheight);
    setFix((bool)(XML.getValue(controlType + "_" + key + ":isFixed", 0)));
    
}


void ofxSimpleGuiContentSlider2d::saveToXML(ofxXmlSettings &XML) {
	XML.addTag(controlType + "_" + key);
	XML.pushTag(controlType + "_" + key);
	XML.addValue("name", name);
	XML.addValue("valueX", value->x);
	XML.addValue("valueY", value->y);
    XML.addValue("isFixed", isFixed());
	XML.popTag();
}
#endif

//void ofxSimpleGuiContentSlider2d::setValue(float x, float y) {
//	(*value).x = x;
//	(*value).y = y;
//}
//
//void ofxSimpleGuiContentSlider2d::setValue2(float x, float y) {
//	(*value2).x = x;
//	(*value2).y = y;
//}

void ofxSimpleGuiContentSlider2d::setMin(float x, float y) {
	min.x = x;
	min.y = y;
}

void ofxSimpleGuiContentSlider2d::setMax(float x, float y) {
	max.x = x;
	max.y = y;
}

void ofxSimpleGuiContentSlider2d::onPress(int x, int y, int button) {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    bool isOnSecondButton = x - this->x > secBtnPos.x && x-this->x < secBtnPos.x + secondPointBoxWidth && y - this->y < secondPointBoxWidth;
    bool isOnSlider = (y - this->y) > sliderTextHeight;
    if (isOnSecondButton) {
        bSecondPoint = !bSecondPoint;
    }
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed() && isOnSlider) {
        lock = true;
        if (bSecondPoint) {
            point2.set(x - this->x, y - this->y - sliderTextHeight);
        } else {
            point.set(x - this->x, y - this->y - sliderTextHeight);
        }
    }
}

void ofxSimpleGuiContentSlider2d::onDragOver(int x, int y, int button) {
    if (!isFixed()) {
        if (bSecondPoint) {
            if (lock) point2.set(x - this->x, y - this->y - sliderTextHeight);
        } else {
            if (lock) point.set(x - this->x, y - this->y - sliderTextHeight);
        }
    }
	
}

void ofxSimpleGuiContentSlider2d::onDragOutside(int x, int y, int button) {
    if (!lock) return;
    if (bSecondPoint) {
        point2.set(x - this->x, y - this->y - sliderTextHeight);
        point2.x = ofClamp(point2.x, 0.0f, width);
        point2.y = ofClamp(point2.y, 0.0f, sliderHeight);
    } else {
        point.set(x - this->x, y - this->y - sliderTextHeight);
        point.x = ofClamp(point.x, 0.0f, width);
        point.y = ofClamp(point.y, 0.0f, sliderHeight);
    }

    lock = false;
}

void ofxSimpleGuiContentSlider2d::onRelease() {
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        lock = false;
    }
}

void ofxSimpleGuiContentSlider2d::update() {
    //
    
    if (bSecondPoint) {
        if (point2.x < 2.0f) point2.x = 0.0f;
        if (point2.x > width - 2.0f) point2.x = width;
        if (point2.y < 2.0f) point2.y = 0.0f;
        if (point2.y > sliderHeight - 2.0f) point2.y = sliderHeight;
        
        if(lock){
            (*value2).x = ofMap(point2.x, 0, width, min.x, max.x);
            (*value2).y = ofMap(point2.y, 0, sliderHeight, min.y, max.y);
        }
    } else {
        if (point.x < 2.0f) point.x = 0.0f;
        if (point.x > width - 2.0f) point.x = width;
        if (point.y < 2.0f) point.y = 0.0f;
        if (point.y > sliderHeight - 2.0f) point.y = sliderHeight;
        
        if(lock){
            (*value).x = ofMap(point.x, 0, width, min.x, max.x);
            (*value).y = ofMap(point.y, 0, sliderHeight, min.y, max.y);
        }
    }
}

void ofxSimpleGuiContentSlider2d::draw(float x, float y) {
	setPos(x, y);
	ofEnableAlphaBlending();
	glPushMatrix();
	glTranslatef(x, y, 0);
    
    ofFill();
    glColor4f(0, 0, 0, 1.0f);
	ofRect(0, sliderTextHeight, width, sliderHeight);
	
	ofSetColor(255, 255, 255, 255);
	content->draw(0, sliderTextHeight, fixwidth, fixheight);
    
    setTextBGColor(!isFixed());
    ofRect(0, 0, width, sliderTextHeight);
    
    setTextColor(!isFixed());
    char vs[64];
    std::sprintf(vs, "\nx:%.2f\ny:%.2f", value->x,value->y);
    ofDrawBitmapString(name + vs , 6, 15);
    setTextColor2(!isFixed());
    char vs2[64];
    std::sprintf(vs2, "\n\nx:%.2f\ny:%.2f", value2->x,value2->y);
    ofDrawBitmapString(vs2 , secBtnPos.x, 0);
    ofSetHexColor(0xffffff);
    //////////
//    ofSetColor(0, 0, 0,0);
//    setContent2DSliderBGColor(!isFixed());
//    if (!isFixed()) ofRect(0, sliderTextHeight, fixwidth, fixheight);
    ofTranslate((int)0.0f, (int)sliderTextHeight);
    if (!isFixed()) {
        ofSetHexColor(0xFFFFFF);
        ofCircle(point.x, point.y, 2);
        ofLine(point.x, 0, point.x, fixheight);
        ofLine(0, point.y,width, point.y);
        if (bSecondPoint) {
            ofSetHexColor(0xFFFF00);
            ofCircle(point2.x, point2.y, 2);
            ofLine(point2.x, 0, point2.x, fixheight);
            ofLine(0, point2.y,width, point2.y);
        }
        ofSetHexColor(0xFFFFFF);
        ofRectangle maxxB = base64GetStringBoundingBox("X:" + ofToString(max.x));
        char valueString[64];
        std::sprintf(valueString,"( %.2f , %.2f )",(*value).x, (*value).y);
        ofRectangle valueStringBox = base64GetStringBoundingBox(valueString);
        base64DrawBitmapString("(" + ofToString(min.x) + "," + ofToString(min.y) + ")", 1, 2);
        base64DrawBitmapString("X:" + ofToString(max.x), width - maxxB.width - 1, 2);
        base64DrawBitmapString("Y:" + ofToString(max.y), 1, fixheight - maxxB.height -1);
        if (width/2 > point.x && fixheight/2 > (point.y - y)){ //Â∑¶‰∏ä„Å´„ÅÇ„Çã„Å®„Åç
            base64DrawBitmapString(valueString, point.x + 3, point.y + 3);
        } else if (width/2 < point.x && fixheight/2 > (point.y)) {//Âè≥‰∏ä
            base64DrawBitmapString(valueString, point.x - valueStringBox.width - 3, point.y + 3);
        } else if (width/2 > point.x && fixheight/2 < point.y) {//Â∑¶‰∏ã
            base64DrawBitmapString(valueString, point.x + 3, point.y - valueStringBox.height - 3);
        } else {//Âè≥‰∏ã
            base64DrawBitmapString(valueString, point.x - valueStringBox.width - 3, point.y - valueStringBox.height - 3);
        }
        
        if (bSecondPoint) {
            ofSetHexColor(0xFFFF00);
            char valueString2[64];
            std::sprintf(valueString2,"( %.2f , %.2f )",(*value2).x, (*value2).y);
            ofRectangle valueStringBox2 = base64GetStringBoundingBox(valueString2);
            if (width/2 > point2.x && fixheight/2 > (point2.y - y)){
                base64DrawBitmapString(valueString2, point2.x + 3, point2.y + 3);
            } else if (width/2 < point2.x && fixheight/2 > (point2.y)) {//Âè≥‰∏ä
                base64DrawBitmapString(valueString2, point2.x - valueStringBox2.width - 3, point2.y + 3);
            } else if (width/2 > point2.x && fixheight/2 < point2.y) {//Â∑¶‰∏ã
                base64DrawBitmapString(valueString2, point2.x + 3, point2.y - valueStringBox2.height - 3);
            } else {//Âè≥‰∏ã
                base64DrawBitmapString(valueString2, point2.x - valueStringBox2.width - 3, point2.y - valueStringBox2.height - 3);
            }
        }
    }
    ofTranslate(0, 0 - (int)sliderTextHeight);
    fixButtonDrawOfContentSlider2d();
    
    if (!fixed) {
        ofFill();
        ofSetHexColor(config->emptyColor);
        ofRect(secBtnPos.x, 1.0f, secondPointBoxWidth, secondPointBoxWidth);
        ofSetHexColor(0xFFFF00);
    }
    else {
        ofSetHexColor(config->borderColor);
        ofNoFill();
    }
    ofSetLineWidth(0.5);
    if (bSecondPoint) {
        ofFill();
    } else ofNoFill();
    ofCircle(secBtnPos.x + secondPointBoxWidth / 2.0f, secondPointBoxWidth / 2 + 1.0f, secondPointBoxWidth / 2);
    ofNoFill();
    ofSetHexColor(config->borderColor);
    ofRect(secBtnPos.x - 0.5, 0.5f, secondPointBoxWidth + 1.0f, secondPointBoxWidth + 1.0f);
    
    
	glPopMatrix();
	ofDisableAlphaBlending();
	
}