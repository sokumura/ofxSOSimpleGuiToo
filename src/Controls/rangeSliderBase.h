#pragma once

#include "ofxSimpleGuiControl.h"

//

template <typename Type> class rangeSliderBase : public ofxSimpleGuiControl {
public:

	Type		*valueS, *valueL;
	Type		min, max;

	float		barwidth;//実数バーの長さ
    float       sliderBGHeight;
	float		pctS, pctL;//それぞれのx座標

	float		lerpSpeed;//
	Type		targetValueS, targetValueL;//動かす数値（SかLか座標によって決める)
	Type		oldValueS, oldValueL;//
    
    float       harf;

	//--------------------------------------------------------------------- construct
	rangeSliderBase(string name, Type &_valueS, Type &_valueL, Type _min, Type _max) : ofxSimpleGuiControl(name) {
        
        if (_valueS <= _valueL) {
            this->valueS = &_valueS;//Sを初期化
            this->valueL = &_valueL;//Lを初期化
        } else {
            ofLogError("ofxSimpleGuiToo/"+name, " valueSとvalueLの初期値がおかしい。");
            this->valueS = &_valueL;//Sを初期化
            this->valueL = &_valueS;//Lを初期化
        }
        if (_min <= _max) {
            setMin(_min);
            setMax(_max);
        } else { 
            ofLogError("ofxSimpleGuiToo/"+name, " minとmaxの初期値がおかしい。");
            setMin(_max);
            setMax(_min);
		}

        targetValueS	= _valueS;
        targetValueL    = _valueL;
		oldValueS	= targetValueS;
        oldValueL   = targetValueL;
		controlType = "RangeSliderBase";
		
//		setIncrement(0);
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
		setSize(config->gridSize.x - config->padding.x, config->sliderHeight + config->sliderTextHeight);//背景の大きさを指定
		pctS = ofMap((*valueS), min, max, 0.0, width);
        pctL = ofMap((*valueL), min, max, 0.0, width);
        
		barwidth = pctL - pctS;
        sliderBGHeight = height;
	}

#ifndef OFXMSAGUI_DONT_USE_XML
	void loadFromXML(ofxXmlSettings &XML) {
		setValueS((Type)XML.getValue(controlType + "_" + key + ":valueS", 0));
        setValueL((Type)XML.getValue(controlType + "_" + key + ":valueL", 0));
        setFix((bool)(XML.getValue(controlType + "_" + key + ":isFixed", 0)));
	}
    
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
        XML.addValue("name", name);
		XML.addValue("valueS", getValueS());
        XML.addValue("valueL", getValueL());
        XML.addValue("isFixed", isFixed());
		XML.popTag();
	}
#endif	
    
	void setSmoothing(float smoothing) {
        if (smoothing < 0 || 1 < smoothing) {
            ofLog(OF_LOG_WARNING, "ofxSimpleGuiToo/rangeSliderBase : smoothingは 0 - 1までのfloatです。");
            float _smoothing = ofClamp(smoothing, 0.0f, 1.0f);
        }
            
		lerpSpeed	= 1.0f - smoothing * 0.9;		// so smoothing :1 still results in some motion!
	}
    
	
	Type getValueS() const {
		return (*valueS);
	}
    
    Type getValueL() const {
		return (*valueL);
	}

	void setValueS(Type f) {//
		setTargetValueS(f);
		oldValueS = *valueS =  targetValueS;
        pctS = ofMap(*valueS, min, max, 0, width);
	}
    
    void setValueL(Type f) {//
		setTargetValueL(f);
		oldValueL = *valueL =  targetValueL;
        pctL = ofMap(*valueL, min, max, 0, width);
	}
	
	void setTargetValueS(Type f) {//
		targetValueS = ofClamp(f, min, max);
	}
    
    void setTargetValueL(Type f) {//
		targetValueL = ofClamp(f, min, max);
	}
	

	void updateSlider() {
		if(!enabled) return;
        harf = pctS + (pctL - pctS) / 2;//左端からのharfの座標
        if (getMouseX() - x < harf) {//左側だったら
            pctS = getMouseX() - x;//pctSを動かす
        } else {                    //右だったら
            pctL = getMouseX() - x;//pctLを動かす
        }
        
        //pctの判定
        if (pctS > pctL) std::swap(pctS, pctL);
        pctL = MIN(width, pctL);
        pctS = MAX(0.0f, pctS);
        
        //pctをvalueに入れる値に戻す
        float tempS = ofMap(pctS, 0.0, width, min, max, true);
        float tempL = ofMap(pctL, 0.0, width, min, max, true);
        
        //targetValueにとりあえず入れる
        targetValueS = (Type)tempS;
        targetValueL = (Type)tempL;
        oldValueS = *valueS;		// save oldValue (so the draw doesn't update target but uses it)
        oldValueL = *valueL;
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
		
		if(oldValueS != *valueS) {					// if value has changed programmatically by something else
			oldValueS = targetValueS = *valueS;			// save the value in target and oldvalue
		} else {									// otherwise lerp
			*valueS += (Type)((targetValueS - *valueS) * lerpSpeed);
			oldValueS = *valueS;							// and save oldvalue
		}
        
        if(oldValueL != *valueL) {					// if value has changed programmatically by something else
			oldValueL = targetValueL = *valueL;			// save the value in target and oldvalue
		} else {									// otherwise lerp
			*valueL += (Type)((targetValueL - *valueL) * lerpSpeed);
			oldValueL = *valueL;							// and save oldvalue
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
		barwidth = pctL - pctS;
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
        ofRect(pctS, height*3/4, barwidth, height/4);
        
        int textHeight = 15;
        
		setTextColor(!isFixed());
        
        //string s = name + " S:"+ofToString((*valueS)) + " L:" + ofToString((*valueL));
        ofDrawBitmapString(name, 6, textHeight);
        
        
        //get width and height
        ofRectangle minBox  = base64GetStringBoundingBox(ofToString(min));
        ofRectangle maxBox  = base64GetStringBoundingBox(ofToString(max));
        ofRectangle valSBox = base64GetStringBoundingBox(ofToString(*valueS));
        ofRectangle valLBox = base64GetStringBoundingBox(ofToString(*valueL));
        
        ofSetHexColor(0xFFFFFF);
        base64DrawBitmapString(ofToString(min), 1, height - minBox.height - 1);
        base64DrawBitmapString(ofToString(max), width - maxBox.width - 1, height - maxBox.height - 1);
        
        setTextColor(!isFixed());
        int pctSH = height*3/4 - valSBox.height - 1;
        int pctLH = height*3/4 - valLBox.height - 1;
        
        if (pctL - pctS < (valSBox.width + valLBox.width)){
            pctSH += 2;
            pctLH -= 5;
        } 
        
        if (pctS < valSBox.width / 2)  base64DrawBitmapString(ofToString(*valueS), 1, pctSH);
        else if (pctS > width - valLBox.width) base64DrawBitmapString(ofToString(*valueS), width - valSBox.width - 1, pctSH);
        else base64DrawBitmapString(ofToString(*valueS), pctS - valSBox.width/2, pctSH);
        
        if (pctL > width - valLBox.width) base64DrawBitmapString(ofToString(*valueL), width - valLBox.width - 1, pctLH);
        else if (pctL < valLBox.width / 2) base64DrawBitmapString(ofToString(*valueL), 1, pctLH); 
        else base64DrawBitmapString(ofToString(*valueL), pctL - valLBox.width/2, pctLH);
        
        
		ofDisableAlphaBlending();
        
        fixButtonDraw();

		glPopMatrix();
        
        
	}



};
