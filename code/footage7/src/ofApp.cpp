/*Footage7 from Re-re-present Consciousness,Keyu Li,2024: 04:26；
 creates a visual representation of the FFT output. 
 It uses random colors for drawing rectangles that represent the magnitude of each frequency band. 
 The width of each rectangle is proportionally scaled based on 
 the number of bins and the width of the window, 
 while the height is scaled by the magnitude values in the FFT output. 
 This results in a series of vertical bars across the screen that visually oscillate 
 in response to the frequency content of the audio, 
 providing an engaging and colorful display.*/
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    bufferSize = 512;  
    fftOutput = new float[bufferSize/2]; 

    int sampleRate = 44100;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    fft.setup(bufferSize, 512, 256);  
    oct.setup(44100, 1024, 10);      

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
        float currentSample = noise.noise() * modulator.phasor(0.1, 0, 5);
        if (fft.process(currentSample)) {
            oct.calculate(fft.magnitudes);  
        }

        for (int j = 0; j < fft.bins; j++) {
            fftOutput[j] = fft.magnitudes[j];
        }

        output[i * output.getNumChannels()] = currentSample;
        output[i * output.getNumChannels() + 1] = currentSample;
    }
}
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    float width = (float)(ofGetWidth() / (fft.bins)*0.1);
    for (int i = 0; i < fft.bins; i++) {
        float height = fftOutput[i] * 200;
        ofDrawRectangle(i * width* 20, ofGetHeight()/2, -width, -height);
        ofDrawRectangle(i * width* 40, ofGetHeight()/2, -width, height);
    }
}


//--------------------------------------------------------------
void ofApp::exit() {
    soundStream.close();
    delete[] fftOutput;
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
