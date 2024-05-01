/*Footage8 from Re-re-present Consciousness,Keyu Li,2024: 04:32；
Initial frequencies for the main tone and a secondary "toot" tone are set, 
along with an initial phase increment rate for increasing these frequencies over time. 
Visual and audio timing intervals (for flashes and toots) are also established here.*/
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofSoundStreamSetup(2, 0, this, 44100, 512, 4);

    mainFrequency = 440;  
    tootFrequency = 200;  
    phaseIncrement = 0.02; 

    nextFlashTime = 0;
    flashInterval = 0.5; 

    nextTootTime = 0;
    tootInterval = 0.5;  
    flashRect.set(ofRandomWidth(), ofRandomHeight(), 100, 50);
}


//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &buffer){
    for (size_t i = 0; i < buffer.getNumFrames(); ++i) {
        double mainSample = mainOscillator.sinewave(mainFrequency);
        double tootSample = (ofGetElapsedTimef() < nextTootTime) ? tootOscillator.sinewave(tootFrequency) : 0;

        buffer[i * buffer.getNumChannels()] = mainSample + tootSample;
        buffer[i * buffer.getNumChannels() + 1] = mainSample + tootSample;
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    mainFrequency += 10 * phaseIncrement;
    tootFrequency += 5 * phaseIncrement;  
    phaseIncrement += 0.001;

    flashInterval = fmax(0.05, flashInterval - 0.001);
    tootInterval = fmax(0.05, tootInterval - 0.005); 

    if (ofGetElapsedTimef() > nextFlashTime) {
        nextFlashTime = ofGetElapsedTimef() + flashInterval;
        flashRect.setPosition(ofRandomWidth() - flashRect.getWidth(), ofRandomHeight() - flashRect.getHeight());
    }

    if (ofGetElapsedTimef() > nextTootTime) {
        nextTootTime = ofGetElapsedTimef() + tootInterval;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (ofGetElapsedTimef() < nextFlashTime) {
        ofFill();
        ofSetColor(255, 0, 0);
        ofDrawRectangle(flashRect);
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
