//Footage1 from Re-re-present Consciousness,Keyu Li,2024: 00:00；
//generates real-time audio by creating white noise, 
//which is then filtered to reduce higher frequencies, 
//resulting in a smoother, less harsh sound. 
//This processed noise is output to both stereo channels, 
//creating a consistent audio experience. 
//Over time, the volume of the noise decays gradually, 
//producing a fading-out effect that diminishes until it becomes inaudible.

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0, 0, 0);
    bufferSize = 512;
    sampleRate = 44100;
    decayRate = 0.999; 
    volume = 1.0; 
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
        float noise = noiseOsc.noise() * volume; 
        float filteredNoise = filter.lores(noise, 1000, 0.8); 

        output[i * output.getNumChannels()] = filteredNoise; 
        output[i * output.getNumChannels() + 1] = filteredNoise; 

        waveform[i] = filteredNoise; 
    }
    volume *= decayRate; 
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofTranslate(0, ofGetHeight() / 2);
    ofSetColor(255);
    ofSetLineWidth(1); 
    ofBeginShape();
    for (int i = 0; i < bufferSize; i++) {
        float x = ofMap(i, 0, bufferSize, 0, ofGetWidth());
        float y = waveform[i] * 100 * volume; 
        ofVertex(x, y);
    }
    ofEndShape(false);
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
