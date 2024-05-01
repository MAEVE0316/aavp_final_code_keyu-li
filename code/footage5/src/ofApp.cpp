/*Footage5 from Re-re-present Consciousness,Keyu Li,2024: 02:36；
uses this brightness to color three circles drawn on the canvas at different positions and sizes. 
The color intensity of these circles varies according to the audio output, 
creating a visual representation that synchronizes with the sound.
*/

#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup() {
    ofBackground(0);
    modulation = 0.0;

    int sampleRate = 44100;
    int bufferSize = 512;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output) {
    for (int i = 0; i < output.getNumFrames(); ++i) {
   
        modulation = abs(osc.sinebuf(100));
        float currentSample = modulation * 2;  

        output[i * output.getNumChannels()] = currentSample;
        output[i * output.getNumChannels() + 1] = currentSample;
    }
}


//--------------------------------------------------------------
void ofApp::update() {
   
    brightness = ofRandom(255 * modulation);  
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(brightness);
    
    ofDrawCircle(ofGetWidth() * 0.25, ofGetHeight() * 0.25, 100);  
    ofDrawCircle(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 200);  
    ofDrawCircle(10, 10, 50);  
}


//--------------------------------------------------------------
void ofApp::exit() {
    soundStream.close();
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
