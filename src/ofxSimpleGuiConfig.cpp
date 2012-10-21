#include "ofxSimpleGuiConfig.h"

ofxSimpleGuiConfig defaultSimpleGuiConfig;


ofxSimpleGuiConfig::ofxSimpleGuiConfig() {
	
	sliderHeight		= 8;
	sliderTextHeight	= 36;
	defaultHeight		= sliderHeight + sliderTextHeight;
    titleHeight         = sliderTextHeight - 10.0f;
	toggleHeight		= defaultHeight;
	buttonHeight		= defaultHeight;
	slider2DTextHeight	= defaultHeight * 1.1;
	comboBoxHeight		= defaultHeight;	//15
	comboBoxTextHeight	= 15;
    colorPickerTextHeight = sliderTextHeight * 2.0;
    
    lockButtonWidth     = 12.0f;
    lockButtonHeight    = defaultHeight;
    lockButtonPos.set(0.0f, 0.0f);
	
    width = 250;
	
	padding.set			(defaultHeight/2, 8);
	offset.set			(defaultHeight/2, defaultHeight/2);
	//slider2DSize.set	(defaultHeight * 4, defaultHeight * 4);
    
	gridSize.x			= width + padding.x;
	gridSize.y			= toggleHeight + padding.y;
	
	textColor			= 0x000000;
	textOverColor		= 0xe8e8e8;
	textBGColor			= 0xe6e6e6;
	textBGOverColor		= 0x545454;
	
	fullColor			= 0x949494;
	fullOverColor		= 0x2278bd;//0x4a9dee;
	fullActiveColor		= 0x2278bd;//0x4a9dee;
	emptyColor			= 0x333333;
	
	borderColor			= 0x222222;
}