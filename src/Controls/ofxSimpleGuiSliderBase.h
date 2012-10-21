#pragma once

#include "ofxSimpleGuiControl.h"



template <typename Type> class ofxSimpleGuiSliderBase : public ofxSimpleGuiControl {
public:

	Type		*value;
	Type		min, max;

	float		barwidth;
    float       sliderBGHeight;
	float		pct;

	float		lerpSpeed;
	Type		targetValue;
	Type		oldValue;
	Type		increment;

	//--------------------------------------------------------------------- construct
	ofxSimpleGuiSliderBase(string name, Type &value, Type min, Type max) : ofxSimpleGuiControl(name) {
		this->value = &value;
		setMin(min);
		setMax(max);

		targetValue	= value;
		oldValue	= targetValue;
		controlType = "SliderBase";
		
		setIncrement(0);
		setSmoothing(0);
		
		setup();
	}

	void setMin(Type m) {
		min = m;
	}
	
	void setMax(Type m) {
		max = m;
	}
	
	void setup() {
		setSize(config->gridSize.x - config->padding.x, config->sliderHeight + config->sliderTextHeight);
		pct		 = ofMap((*value), min, max, 0.0, width);
		barwidth = pct;
        sliderBGHeight = height;
	}

#ifndef OFXMSAGUI_DONT_USE_XML
	void loadFromXML(ofxXmlSettings &XML) {
		setValue((Type)XML.getValue(controlType + "_" + key + ":value", 0.0f));
        setFix((bool)(XML.getValue(controlType + "_" + key + ":isFixed", 0)));
	}
    
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
        XML.addValue("isFixed", isFixed());
		XML.popTag();
	}
#endif	
    
	void setSmoothing(float smoothing) {
		lerpSpeed	= 1.0f - smoothing * 0.9;		// so smoothing :1 still results in some motion!
	}
	
	void setIncrement(Type increment) {
		this->increment = increment;
	}



	Type getValue() {
		return (*value);
	}


	void setValue(Type f) {
		setTargetValue(f);
		oldValue = *value =  targetValue;
	}
	
	void setTargetValue(Type f) {
		targetValue = ofClamp(f, min, max);
	}
	

	void increase() {
		if(increment == 0) setIncrement((max - min) * 0.001);
//		oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
		setTargetValue(*value + increment);
	}

	void decrease() {
		if(increment == 0) setIncrement((max - min) * 0.001);
//		oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
		setTargetValue(*value - increment);
	}


	void updateSlider() {
		if(!enabled) return;

		if(pct > width) {
			pct = width;
		}
		else {
			pct = getMouseX() - x;
			float temp = ofMap(pct, 0.0, width, min, max, true);

			targetValue = (Type)temp;
			oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
		}
	}

	void onPress(int x, int y, int button) {
		bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
        if (isOnFixButton) {
            toggleFix();
        } else if (!isFixed()) {
            updateSlider();
        }
	}

	void onDragOver(int x, int y, int button) {
		bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
        if (isOnFixButton) {
            toggleFix();
        } else if (!isFixed()) {
            updateSlider();
        }
	}

	void onDragOutside(int x, int y, int button) {
        bool isOnFixButton = x - this->x > width - fixboxWidth && y - this->y < fixboxWidth && bDrawFixButton;
        if (isOnFixButton) {
            toggleFix();
        } else if (!isFixed()) {
            updateSlider();
        }
	}


	//--------------------------------------------------------------------- update
	void update() {
		if(!enabled) return;
		
		if(oldValue != *value) {					// if value has changed programmatically by something else
			oldValue = targetValue = *value;			// save the value in target and oldvalue
		} else {									// otherwise lerp
			*value += (Type)((targetValue - *value) * lerpSpeed);
			oldValue = *value;							// and save oldvalue
		}
		
		if(lock) {
			updateSlider();
		}

//		enabled = false;

	}

	//--------------------------------------------------------------------- draw
	void draw(float x, float y) {

//		enabled = true;

		//update postion of gui object
		setPos(x, y);

		//VALUE CLAMP
		barwidth = ofMap((*value), min, max, 0.0, (float)width);
		if(barwidth > width) barwidth = width;
		else if(barwidth < 0) barwidth = 0;

		ofEnableAlphaBlending();
		glPushMatrix();
		glTranslatef(x, y, 0);
		ofFill();
        setTextBGColor(!isFixed());
        ofRect(0, 0, width, height);
        
		setEmptyColor();
        //float sliderHight0 = sliderBGHeight/2 - config->sliderHeight/2 + 11;
        ofRect(0, height*3/4, width, height/4);
        
		setFullColor(!isFixed());
        ofRect(0, height*3/4, barwidth, height/4);
        
        int textHeight = 15;
        
		setTextColor();

        string s = name + ": "+ofToString((*value));
        ofDrawBitmapString(s, 6, textHeight);
        
        //get width and height
        ofRectangle minBox  = base64GetStringBoundingBox(ofToString(min));
        ofRectangle maxBox  = base64GetStringBoundingBox(ofToString(max));
        ofRectangle valBox = base64GetStringBoundingBox(ofToString(*value));
        
        base64DrawBitmapString(ofToString(min), 1, height*3/4 - minBox.height -1);
        base64DrawBitmapString(ofToString(max), width - maxBox.width - 1, height*3/4 - maxBox.height -1);
        
        fixButtonDraw();

		ofDisableAlphaBlending();
		glPopMatrix();
	}



};
