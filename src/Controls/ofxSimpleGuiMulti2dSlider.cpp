//
//  ofxSimpleGuiMulti2dSlider.cpp
//  TuboWariProjection
//
//  Created by Shuya Okumura on 2013/02/11.
//
//

#include "ofxSimpleGuiMulti2dSlider.h"


ofxSimpleGuiMulti2dSlider::ofxSimpleGuiMulti2dSlider(string name, int nBlock, int pointNum, ofPoint * values, float _xmin, float _xmax, float _ymin, float _ymax, float sliderAspectWbyH, bool bBgTransparent, float _offsetScale) : ofxSimpleGuiControl(name) {

    pValues = values;

    if (offsetScale > 1.0f) {
        ofLogError("ofxSimpleGuiMulti2dSlider : offsetScale's value is error!!\n");
    }
    this->offsetScale = _offsetScale;
	this->width = nBlock * config->width + (nBlock - 1) * config->padding.x;
    sliderHeight = width * 3.0f / 4.0f;
    sliderTextHeight = config->slider2DTextHeight;
	controlType = "ContentSlider2D";
    bBgTrans = bBgTransparent;
    aspect = sliderAspectWbyH;

//    for (int i = 0; i < POINT_NUM_LIMIT; i++) {
//        pSliderPoint[i] = ofPoint(width/2, sliderHeight / 2);
//    }
    
	setSize(width, sliderHeight + sliderTextHeight);
    nPointNum = pointNum;
    mainMin.set(_xmin, _ymin);
    mainMax.set(_xmax, _ymax);
    
    if (_xmin > _xmax) std::swap(_xmin, _xmax);
    if (_ymin > _ymax) std::swap(_ymin, _ymax);
    float offsetX = ((_xmax - _xmin) - (_xmax - _xmin) * offsetScale) / 2.0f;
    float offsetY = ((_ymax - _ymin) - (_ymax - _ymin) * offsetScale) / 2.0f;
	min.set(_xmin - offsetX, _ymin - offsetY);
	max.set(_xmax + offsetX, _ymax + offsetY);
    ofPoint p1;
    p1.set(ofMap(_xmin, min.x, max.x, 0.0f, width), ofMap(_ymin, min.y, max.y, sliderTextHeight, sliderTextHeight + sliderHeight));
    ofPoint p2;
    p2.set(ofMap(_xmax, min.x, max.x, 0.0f, width), ofMap(_ymax, min.y, max.y, sliderTextHeight, sliderTextHeight + sliderHeight));
    insideRect.set(p1, p2);
    
    for (int i = 0; i < nPointNum; i++) {
        pValues[i].x = ofClamp(pValues[i].x, min.x, max.x);
        pValues[i].y = ofClamp(pValues[i].y, min.y, max.y);
    }
    if (nBlock == 0) {
        ofLog(OF_LOG_ERROR, "ofxSimpleGuiMulti2dSlider で nBlockに0が入っている。1以上にすべし。\n");
    }
    if (nBlock > 6) {
        ofLog(OF_LOG_WARNING, "ofxSimpleGuiMulti2dSlider で nBlockに7以上の数字が入ってます。大き過ぎて画面に入らないと思います。\n");
    }
    
	setup();
}

void ofxSimpleGuiMulti2dSlider::setup() {
    for (int i = 0; i < nPointNum; i++) {
        pSliderPoint[i].x = ofMap(pValues[i].x, min.x, max.x, 0.0f, width);
        pSliderPoint[i].y = ofMap(pValues[i].y, min.y, max.y, 0.0f, sliderHeight);
    }
}

void ofxSimpleGuiMulti2dSlider::setMin(float x, float y) {
	min.x = x;
	min.y = y;
}

void ofxSimpleGuiMulti2dSlider::setMax(float x, float y) {
	max.x = x;
	max.y = y;
}

void ofxSimpleGuiMulti2dSlider::onPress(int x, int y, int button) {
    targetNo = nPointNum;
    
    bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
    bool isOnSlider = (y - this->y) > sliderTextHeight;
    if (isOnFixButton) {
        toggleFix();
    } else if (!isFixed()) {
        ofPoint p = ofPoint(x - this->x ,y - this->y - sliderTextHeight);
        float dist = width;
        printf("1 ");
        for (int i = 0; i < nPointNum; i++) {
            float d = p.distance(pSliderPoint[i]);
            if (dist >= d) {
                targetNo = i;
                dist = d;
                
            }
        }
        if (targetNo != nPointNum && dist < width / 10.0f) {
            lock = true;
            //pSliderPoint[targetNo] = p;
        } else {
            targetNo = nPointNum;
        }
    }
}

void ofxSimpleGuiMulti2dSlider::onDragOver(int x, int y, int button) {
    if (targetNo == nPointNum) return;
    if (!isFixed() && lock) {
        pSliderPoint[targetNo].set(x, y - this->y - sliderTextHeight);
    }
}

void ofxSimpleGuiMulti2dSlider::onDragOutside(int x, int y, int button) {
    if (!isFixed()) {
        targetNo = nPointNum;
        lock = false;
    }
}

void ofxSimpleGuiMulti2dSlider::onRelease(int x, int y, int button) {
    if (!isFixed()) {
        targetNo = nPointNum;
        lock = false;
    }
}

void ofxSimpleGuiMulti2dSlider::update() {


    if (lock) {
        pSliderPoint[targetNo].x = ofClamp(pSliderPoint[targetNo].x, 0.0f, width);
        pSliderPoint[targetNo].y = ofClamp(pSliderPoint[targetNo].y, 0.0f, sliderHeight);
        pValues[targetNo].x = ofMap(pSliderPoint[targetNo].x, 0, width, min.x, max.x);
        pValues[targetNo].y = ofMap(pSliderPoint[targetNo].y, 0, sliderHeight, min.y, max.y);
    }
}

void ofxSimpleGuiMulti2dSlider::draw(float x, float y) {
	setPos(x, y);
	ofEnableAlphaBlending();
	glPushMatrix();
	glTranslatef(this->x, this->y, 0);
    
    ofFill();
    if (bBgTrans) glColor4f(1.0f, 0, 0, 0);//黒 - 背景
    else {
        ofSetColor(255, 0, 0,255);
        set2DSliderBGColor();
    }
    ofRect(0, sliderTextHeight, width, sliderHeight);
	if (offsetScale < 1.0f) {
        ofNoFill();
        ofSetColor(255, 255, 255, 255);
        ofRect(insideRect);
    }
    ofFill();
    ofSetColor(255, 255, 255, 255);
    setTextBGColor(!isFixed());
    ofRect(0, 0, width, sliderTextHeight);
    
    setTextColor();
    ofDrawBitmapString(this->name, 6.0f, 13.0f);

    char vs[nPointNum][128];
    for (int i = 0; i < nPointNum; i++) {
        if (i != targetNo) setTextColor(!isFixed());
        else setTextColor2();
        std::sprintf(&vs[i][0], "%u\nx:%.2f\ny:%.2f", i, pValues[i].x, pValues[i].y);
        base64DrawBitmapString(vs[i] , 6 + i * (width / nPointNum), 18.0f);
    }
    
    ofTranslate((int)0.0f, (int)sliderTextHeight);
    for (int i = 0; i < nPointNum; i++) {
        ofSetColor(0,0,0, 255);
        ofSetHexColor(config->pointsColor[i]);      
        if (targetNo != nPointNum) {
            
            if (i == targetNo) {
                ofLine(pSliderPoint[i].x, 0, pSliderPoint[i].x, sliderHeight);
                ofLine(0, pSliderPoint[i].y,width, pSliderPoint[i].y);
            } 
        }
        ofCircle(pSliderPoint[i].x, pSliderPoint[i].y, 3);
        ofSetHexColor(0xffffff);
        ofRectangle maxxB = base64GetStringBoundingBox("X:" + ofToString(mainMax.x));
//        string valueString = "(" + ofToString(ppValues[i].x) + "," + ofToString(ppValues[i].y) + ")";
//        ofRectangle valueStringBox = base64GetStringBoundingBox(ofToString(i));
        
        base64DrawBitmapString("(" + ofToString(mainMin.x) + "," + ofToString(mainMin.y) + ")", 1, 2);
        base64DrawBitmapString("X:" + ofToString(mainMax.x), width - maxxB.width - 1, 2);
        base64DrawBitmapString("Y:" + ofToString(mainMax.y), 1, sliderHeight - maxxB.height -1);
        ofRectangle nameBox = base64GetStringBoundingBox(this->name);
        base64DrawBitmapString(name, width - nameBox.width - 1, sliderHeight - nameBox.height - 1);
        
        ofSetHexColor(config->pointsColor[i]);
        ofDrawBitmapString(ofToString(i), ofPoint(pSliderPoint[i]) - ofPoint(10.0f, 6.0f));
    }
    
    ofTranslate(0, (int)(-1)*(sliderTextHeight) + 2);
    //fixButtonDrawOfContentSlider2d();
    fixButtonDraw();
	glPopMatrix();
	ofDisableAlphaBlending();
	
}