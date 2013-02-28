//
//  ofxSimpleGuiMulti2dSlider.h
//  TuboWariProjection
//
//  Created by Shuya Okumura on 2013/02/11.
//
//
#pragma once
#include "ofxSimpleGuiControl.h"

class ofxSimpleGuiMulti2dSlider : public ofxSimpleGuiControl {
public:
    
	ofxSimpleGuiMulti2dSlider(string name, int nBlock, int pointNum, ofPoint * values, float _xmin, float _xmax, float _ymin, float _ymax, float sliderAspectWbyH = 1.0f, bool bBgTransparent = false, float _offsetScale = 1.0f);
	void setup();
	void setValue(int num, float x, float y);
	void setMin(float x, float y);
	void setMax(float x, float y);
	void onPress(int x, int y, int button);
	void onDragOver(int x, int y, int button);
	void onDragOutside(int x, int y, int button);
	void onRelease(int x, int y, int button);
	void update();
	void draw(float x, float y);
    ofRectangle insideRect;
private:
    float sliderWidth;
    float sliderHeight;
    float sliderTextHeight;
    bool  bBgTrans;
    int nPointNum;
    int targetNo;
    ofPoint * pValues;
    ofPoint pSliderPoint[POINT_NUM_LIMIT];
    ofPoint mainMin, mainMax;
	ofPoint	min, max;
    float aspect;
    float offsetScale;
    //float offsetSliderX, offsetSliderY;
    
};
