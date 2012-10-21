//
//  customFunc.h
//  ofTuboWari_Projection
//
//  Created by Shuya Okumura on 2012/10/18.
//
//

#ifndef customFunc_h
#define customFunc_h

#include "ofMain.h"

//--------------------------------------------------
ofRectangle ofGetBitmapStringBoundingBox(string text) {
	vector<string> lines = ofSplitString(text, "\n");
	int textLength = 0;
	for(int i = 0; i < lines.size(); i++) {
		// tabs are not rendered
		int tabs = count(lines[i].begin(), lines[i].end(), '\t');
		int curLength = lines[i].length() - tabs;
		if(curLength > textLength) {
			textLength = curLength;
		}
	}
	
	int padding = 0;
	int fontSize = 8;
	float leading = 1.7;
	int height = lines.size() * fontSize * leading - 1;
	int width = textLength * fontSize;
	
	ofRectangle rect = ofRectangle(0, 0, width, height);
    return rect;
}



#endif
