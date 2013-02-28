//
//  ofxSimpleGuiContentSlider2d.h
//  TuboWariProjection
//
//  Created by Shuya Okumura on 2013/02/09.
//
//
#pragma once

#include "ofxSimpleGuiControl.h"


class ofxSimpleGuiContentSlider2d : public ofxSimpleGuiControl {
public:
	ofPoint		*value;
    ofPoint     *value2;
	ofPoint		point, point2, min, max;
    ofTexture * content;
    
    float			fixwidth;
	float			fixheight;
    float secondPointBoxWidth;
    
	ofxSimpleGuiContentSlider2d(string name, int nBlock, ofTexture & content, ofPoint& value, ofPoint& value2, float xmin, float xmax, float ymin, float ymax, bool bSecond = false);
	void setup();
#ifndef OFXMSAGUI_DONT_USE_XML
	void loadFromXML(ofxXmlSettings &XML);
	void saveToXML(ofxXmlSettings &XML);
#endif
	void setValue(float x, float y);
    void setValue2(float x, float y);
	void setMin(float x, float y);
	void setMax(float x, float y);
	void onPress(int x, int y, int button);
	void onDragOver(int x, int y, int button);
	void onDragOutside(int x, int y, int button);
	void onRelease();
	void update();
	void draw(float x, float y);
private:
    float sliderHeight;
    float sliderTextHeight;
    bool bSecondPoint;
    ofPoint secBtnPos;
};
