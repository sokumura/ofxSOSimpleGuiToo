//
//  ofSimpleGuiBlank.h
//  emptyExample
//
//  Created by 奥村 周也 on 12/10/10.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_ofSimpleGuiBlank_h
#define emptyExample_ofSimpleGuiBlank_h

class ofxSimpleGuiBlank: public ofxSimpleGuiControl {
	
public:
    
	ofxSimpleGuiBlank(string name = "", float height = 0): ofxSimpleGuiControl(name) {
        //		this->value	= &value;
        controlType = "Blank";
        //		newColumn	= true;
        
        if(height == 0) height = config->defaultHeight;
        if(hasTitle == false) height/=2;
        setSize(config->gridSize.x - config->padding.x, height);
    }
    
	void draw(float x, float y){
    
    }
};

#endif
