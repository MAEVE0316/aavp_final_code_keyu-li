/*Footage9 from Re-re-present Consciousness,Keyu Li,2024: 05:08；
generates a noise texture that visually represents the vibration effects based on 
the current sound sample. The noise texture's pixels are shifted horizontally 
according to the current audio sample value, 
creating a vibration effect that visually mimics the dynamic changes in the sound.
*/
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

    snowPixels.allocate(ofGetWidth(), ofGetHeight(), OF_PIXELS_GRAY);
    snowTexture.allocate(snowPixels);
    frequency = 440; 
    amplitude = 0.5; 
}


//--------------------------------------------------------------
void ofApp::update() {
    float time = ofGetElapsedTimef();
    float frequencyModulation = sin(time * 0.1) * 200 + 440; 

    frequency = frequencyModulation;
    amplitude = 0.5 + 0.5 * sin(time * 0.07);  
    currentSample = amplitude * (osc.noise() + osc.sinewave(frequency));
    float noiseScale = 0.05;
    for (int y = 0; y < ofGetHeight(); y++) {
        for (int x = 0; x < ofGetWidth(); x++) {
            float noiseValue = ofNoise(x * noiseScale, y * noiseScale, ofGetElapsedTimef() * 0.2);
            int xOffset = ofMap(currentSample, -1, 1, -5, 5);
            snowPixels.setColor((x + xOffset) % ofGetWidth(), y, 255 * noiseValue);
        }
    }
    snowTexture.loadData(snowPixels);
}


//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    snowTexture.draw(0, 0);
}


//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output) {
    for (size_t i = 0; i < output.getNumFrames(); i++) {
        currentSample = amplitude * (osc.noise() + osc.sinewave(frequency));
        output[i * output.getNumChannels()] = currentSample;
        output[i * output.getNumChannels() + 1] = currentSample;
    }
}


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
