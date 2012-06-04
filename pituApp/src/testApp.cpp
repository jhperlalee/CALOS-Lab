#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	
	//soundStream.listDevices();
	//if you want to set a different device id 
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	soundStream.setup(this, 0, 2, 44100, 256, 4);
    // 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
    smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
    thresholdVol    = 0.1;
    lerpVal         = 0.99;
    
    arrow.loadImage("arrow01.png");
    arrowPos = 0.0;
    arrowColor.set(255,0,0);
}

//--------------------------------------------------------------
void testApp::update(){
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    if ( (arrowPos >= 0.0) && 
        (arrowPos <= 1.0) &&
        (scaledVol > thresholdVol)){
        arrowPos += (scaledVol-thresholdVol)/(ofGetFrameRate()*0.1);
    }
    
    arrowPos *= lerpVal;
    arrowColor.setHue(arrowPos*90);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackgroundGradient(ofColor::gray, ofColor::black);
    
    // draw the average volume:
	ofPushStyle();
    ofPushMatrix();
    ofTranslate(10, 110, 0);
    
    ofSetColor(arrowColor,200);
    ofFill();	
	ofRect(2, (scaledVol * -100.0f), 10, (scaledVol * 100.0f));
    
    
    ofNoFill();		
    ofSetColor(255,100);
    ofRect(0, -100, 14, 100);
    ofSetColor(255,150);
    ofLine(0, 0.1*-100.0, 14, 0.1*-100.0);

    ofPopMatrix();
	ofPopStyle();
    
    //Dibuja la Flecha
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(arrowPos*ofGetWidth(), ofGetHeight(), 0);
    
    ofSetColor(arrowColor);
    arrow.draw(-arrow.getWidth()*0.25, -arrow.getHeight()*0.5,arrow.getWidth()*0.5,arrow.getHeight()*0.5);
    
    ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	
    
    float left[bufferSize];
    float right[bufferSize];
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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