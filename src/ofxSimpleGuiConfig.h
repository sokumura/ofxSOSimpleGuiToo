#pragma once

#include "ofTypes.h"
#include "ofPoint.h"

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
    
    float   lockButtonWidth;
    float   lockButtonHeight;
    ofPoint lockButtonPos;
    
    float width;

	ofPoint padding;
	ofPoint offset;
	ofPoint	slider2DSize;
    
    int titleColor[5];

	int	textColor;
	int textOverColor;
	int textBGColor;
	int textBGOverColor;
    int textOFFColor;

	int fullColor;
	int	fullOverColor;
	int fullActiveColor;
	int emptyColor;
	int borderColor;

	ofxSimpleGuiConfig();
};


extern ofxSimpleGuiConfig defaultSimpleGuiConfig;

