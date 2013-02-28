#include "ofxSimpleGuiConfig.h"

ofxSimpleGuiConfig defaultSimpleGuiConfig;


ofxSimpleGuiConfig::ofxSimpleGuiConfig() {
	
	sliderHeight		= 8;
	sliderTextHeight	= 36;
	defaultHeight		= sliderHeight + sliderTextHeight;
    titleHeight         = sliderTextHeight - 10.0f;
	toggleHeight		= defaultHeight;
	buttonHeight		= defaultHeight + 0.4f;
	slider2DTextHeight	= defaultHeight * 1.2;
	comboBoxHeight		= defaultHeight;	//15
	comboBoxTextHeight	= 15;
    colorPickerTextHeight = sliderTextHeight * 2.0;
    
    contentTextHeight = sliderTextHeight * 0.6;
    
    monitorSlider2dAlpha =  70;
    
    
    lockButtonWidth     = 12.0f;
    lockButtonHeight    = defaultHeight;
    lockButtonPos.set(0.0f, 0.0f);
	
    width = 200;
	
	padding.set			(defaultHeight/4, 8);
	offset.set			(defaultHeight/4, defaultHeight/4);
	//slider2DSize.set	(defaultHeight * 4, defaultHeight * 4);
    secBtnPos.set(width / 2, 0.0f);
    
	gridSize.x			= width + padding.x;
	gridSize.y			= toggleHeight + padding.y;

	
	textColor			= 0x000000;
    textColor2          = 0x002000;
	textOverColor		= 0xe8e8e8;
    textOverColor2      = 0xffff00;
	textBGColor			= 0xe6e6e6;
	textBGOverColor		= 0x545454;
	
	fullColor			= 0x949494;
	fullOverColor		= 0x2278bd;//0x4a9dee;
	fullActiveColor		= 0x2278bd;//0x4a9dee;
	emptyColor			= 0x333333;
	
	borderColor			= 0x222222;
    
    pointsColor[0]      = 0xff0000;
    pointsColor[1]      = 0x00ff00;
    pointsColor[2]      = 0x0067ff;
    pointsColor[3]      = 0xff8f00;
    pointsColor[4]      = 0xff99c4;
    pointsColor[5]      = 0xa100c5;
    
    for (int i = 6; i < POINT_NUM_LIMIT; i++) {
        pointsColor[i]      = 0xffffff;
    }
    
}