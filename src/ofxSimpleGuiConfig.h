#pragma once

#include "ofTypes.h"
#include "ofPoint.h"
#define POINT_NUM_LIMIT 10

class ofxSimpleGuiConfig {
public:
	ofPoint	gridSize;

	float	buttonHeight;
	float	toggleHeight;
	float	sliderHeight;
	float	sliderTextHeight;
	float	slider2DTextHeight;
    float   defaultHeight;
	float	titleHeight;
	float	comboBoxHeight;
	float	comboBoxTextHeight;
    float   colorPickerTextHeight;
    float   contentTextHeight;
    
    char monitorSlider2dAlpha;
    
    float   lockButtonWidth;
    float   lockButtonHeight;
    ofPoint lockButtonPos;
    
    float width;

	ofPoint padding;
	ofPoint offset;
	ofPoint	slider2DSize;
    ofPoint secBtnPos;
    
    int titleColor[5];

	int	textColor;
	int textOverColor;
    int	textColor2;
    int textOverColor2;
	int textBGColor;
	int textBGOverColor;
    int textOFFColor;

	int fullColor;
	int	fullOverColor;
	int fullActiveColor;
	int emptyColor;
	int borderColor;
    
    int pointsColor[POINT_NUM_LIMIT];

	ofxSimpleGuiConfig();
};


extern ofxSimpleGuiConfig defaultSimpleGuiConfig;

