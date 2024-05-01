/*Footage4 from Re-re-present Consciousness,Keyu Li,2024: 02:00；
The visual component dynamically illustrates the audio waveform through a 
geometric representation. It starts with a base circle centered in the window, 
and extends lines from the circle's edge based on the audio waveform values. 
Each point on the circle corresponds to a frame in the audio buffer, 
and the length of each line is modulated by the waveform amplitude at that frame. 
This creates a pulsating effect where the circle appears to oscillate in and out, 
visually mimicking the waveform of the audio signal.*/
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    bufferSize = 512;
    waveform.resize(bufferSize, 0.0);

    int sampleRate = 44100;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    angleStep = TWO_PI / bufferSize; 
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output) {
    for (int i = 0; i < output.getNumFrames(); ++i) {
        float currentSample = osc.sinewave(440) * 0.5; 
        output[i * output.getNumChannels()] = currentSample;
        output[i * output.getNumChannels() + 1] = currentSample;
        waveform[i] = currentSample; 
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); 
    ofSetColor(255);

    float radius = 100; 
    for (int i = 0; i < bufferSize; i++) {
        float angle = i * angleStep; 
        float x = radius * cos(angle); 
        float y = radius * sin(angle); 
        float modRadius = radius + waveform[i] * 10;
        float modX = modRadius * cos(angle);
        float modY = modRadius * sin(angle);

        ofDrawLine(x, y, modX, modY); 
    ofPopMatrix();
    }
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
