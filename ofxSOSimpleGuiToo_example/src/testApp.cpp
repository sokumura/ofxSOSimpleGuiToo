#include "testApp.h"

//GLOBAL/////////////////////////
bool td = false;
float myFloat1 = 0.56;
int myInt1 = 10;
int box1 = 3;
bool randomizeButton = true;
float * value;
float myFloat2 = 0.5;
int myInt2 = 6;
bool myBool2 = false;
int box2 = 1;
float myFloat5 = 3.0;
float myFloat6 = 0.3;
float myFloat9 = 0.0054;
bool myBool9 = false;

int nearThreshold = 50;
int farThreshold = 200;
float near = 0.001f;
float far = 0.8f;

ofPoint p = ofPoint(50.0f,50.0f);

ofFloatColor fc = ofFloatColor(0.5,0.5,0.5,0.5);
/////////////////////////////////

//--------------------------------------------------------------
void testApp::setup(){
    
    gui.setup("test page 1");
    
    gui.addTitle("Control Window");
    gui.addRangeSlider("testRenge", nearThreshold, farThreshold, 0, 500).setSmoothing(1.0f);
    gui.addRangeSlider("testFloatRenge", near, far, 0.0f, 1.0f);
    gui.addToggle("Full Screen", td);
    gui.addSlider("myFloat1: noise", myFloat1, 0.0, 1);
    gui.addSlider("myInt1", myInt1, 100, 200);
    gui.addComboBox("box1", box1, 12, NULL);
    gui.addBlank();
    gui.addButton("Randomize Background", randomizeButton);
    //gui.addColorPicker("BG Color", value);
    
    //gui.addPage();
    gui.addTitle("Another group").setNewColumn(true);
    gui.addColorPicker("colorPickerExample", fc);
	gui.addSlider("myFloat2", myFloat2, 0.0, 1).setSmoothing(0.5);
	gui.addSlider("myInt2", myInt2, 3, 8);
	gui.addToggle("myBool2", myBool2);
	string titleArray[] = {"Lame", "Alright", "Better", "Best"};
	gui.addComboBox("box2", box2, 4,  titleArray);
    
    gui.addSlider2d("2dSlider Test", p, 0.0f, 200.0f, 0.0f, 100.0f);
    
	gui.addSlider("myFloat5", myFloat5, 0.0, 5);
	gui.addSlider("myFloat6", myFloat6, 0.0, 1);
	gui.addSlider("myFloat9", myFloat9, 0.0, 0.01 );
	gui.addToggle("myBool9", myBool9);
    
    gui.setPage(1);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key>='0' && key<='9') {
        gui.setPage(key - '0');
        gui.show();
    } else {
        switch(key) {
            case ' ': gui.toggleDraw(); break;
            case '[': gui.prevPage(); break;
            case ']': gui.nextPage(); break;
            case 'p': gui.nextPageWithBlank(); break;
        }
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}