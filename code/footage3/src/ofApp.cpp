//Footage3 from Re-re-present Consciousness,Keyu Li,2024: 00:21；
//The visual output is directly linked to the processed audio. 
//Each pixel's brightness on the screen is mapped from the audio waveform values, 
//which represent the mixed noise. As the waveform values change with each audio frame, 
//so do the brightness values of the pixels, 
//creating a dynamic grayscale visualization that fluctuates in intensity in sync with the audio. 

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    bufferSize = 512;

    int sampleRate = 44100;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    videoPixels.allocate(ofGetWidth(), ofGetHeight(), OF_PIXELS_RGB);
    texture.allocate(videoPixels);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output) {
    for (int i = 0; i < output.getNumFrames(); ++i) {
        double noise = noiseOsc.noise() * 0.5;
        double filteredNoise = filter.lores(noise, 1000, 0.8);

        // Apply multiple delays
        delays[0] = delay.dl(filteredNoise, 500, 0.5);
        delays[1] = delay.dl(filteredNoise, 300, 0.5);
        delays[2] = delay.dl(filteredNoise, 800, 0.5);
        
        double mixedNoise = (delays[0] + delays[1] + delays[2]) / 3.0;

        output[i * output.getNumChannels()] = mixedNoise;
        output[i * output.getNumChannels() + 1] = mixedNoise;

        waveform[i] = mixedNoise;
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    for (int y = 0; y < videoPixels.getHeight(); y++) {
        for (int x = 0; x < videoPixels.getWidth(); x++) {
            float brightness = ofMap(waveform[(x + y) % bufferSize], -1, 1, 0, 255);
            videoPixels.setColor(x, y, ofColor(brightness));
        }
    }
    texture.loadData(videoPixels);
}

//--------------------------------------------------------------
void ofApp::draw() {
    texture.draw(0, 0, ofGetWidth(), ofGetHeight());
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
