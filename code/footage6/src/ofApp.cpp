/*Footage6 from Re-re-present Consciousness,Keyu Li,2024: 03:33；
 initializes the audio environment with a set buffer size and sample rate. 
 It also sets up an envelope with specific attack, decay, 
 sustain, and release (ADSR) parameters. 
 These envelope settings control how the amplitude of the sound evolves over time, 
 starting quickly, sustaining at a high level, then decaying and releasing slowly.*/
 
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    bufferSize = 512;
    waveform = new float[bufferSize];  

    int sampleRate = 44100;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    env.setAttack(0);
    env.setDecay(200);
    env.setSustain(1);
    env.setRelease(500);

    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    rippleRadius = 0;  
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output) {
    for (int i = 0; i < output.getNumFrames(); ++i) {
        if (i % 22050 == 0) {  
            env.trigger = 1;  
        } else {
            env.trigger = 0;
        }

        float currentSample = env.adsr(1.0, env.trigger) * osc.sinewave(100);  
        output[i * output.getNumChannels()] = currentSample;
        output[i * output.getNumChannels() + 1] = currentSample;

        waveform[i] = currentSample; 
        rippleRadius = max(rippleRadius, abs(currentSample) * 200); 
    }
}


//--------------------------------------------------------------
void ofApp::update() {
    rippleRadius *= 0.95; 
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, rippleRadius);
}


//--------------------------------------------------------------
void ofApp::exit() {
    soundStream.close();
    delete[] waveform; 
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
