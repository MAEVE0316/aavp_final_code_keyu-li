/*Footage10 from Re-re-present Consciousness,Keyu Li,2024: 05:01；
provides immediate visual feedback based on the current active audio channel. When sound is active, 
it displays a red dot on the left side if the left channel is active, 
or a green dot on the right if the right channel is active. */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);

    int sampleRate = 44100;
    int bufferSize = 512;
    ofSoundStreamSettings settings;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.sampleRate = sampleRate;
    settings.bufferSize = bufferSize;
    settings.setOutListener(this);
    ofSoundStreamSetup(settings);

    currentChannel = 0;    
    panPosition = 0;       
    lastSwitchTime = 0;    
    switchInterval = 0.1; 
    soundActive = false;  
    leftDotPos.set(100, ofGetHeight() / 2);  
    rightDotPos.set(ofGetWidth() - 100, ofGetHeight() / 2);  
}
//--------------------------------------------------------------
void ofApp::update() {
    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastSwitchTime >= switchInterval) {
        lastSwitchTime = currentTime; 
        currentChannel = !currentChannel; 
        soundActive = true; 
    } else {
        soundActive = false; 
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (soundActive) {
        if (currentChannel == 0) {
            ofSetColor(255, 0, 0);
            ofDrawCircle(leftDotPos, 20);  
        } else {
            ofSetColor(0, 255, 0);
            ofDrawCircle(rightDotPos, 20);  
        }
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output) {
    for (size_t i = 0; i < output.getNumFrames(); i++) {
        float sample = soundActive ? osc.sinewave(440) : 0; 
        output[i * output.getNumChannels()] = (currentChannel == 0) ? sample : 0;
        output[i * output.getNumChannels() + 1] = (currentChannel == 1) ? sample : 0; 
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    ofSoundStreamClose();
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
