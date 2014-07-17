#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // oF
    ofSetFrameRate(60);
    ofBackground(0);

    // sphere
    sphere.setRadius(250);
    sphere.setResolution(2);
    sphere.setMode(OF_PRIMITIVE_TRIANGLES);

    sphereOriginal.setRadius(250);
    sphereOriginal.setResolution(2);
    sphereOriginal.setMode(OF_PRIMITIVE_TRIANGLES);

    // audio
    fft.setup();

    // post
    post.init();
    post.createPass<EdgePass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);

}

//--------------------------------------------------------------
void ofApp::update(){

    // triangle faces
    vector<ofMeshFace> triangles = sphereOriginal.getMesh().getUniqueFaces();

    // audio
    int numData = triangles.size() * 4;
    float * audioData = new float[numData];

    fft.update();
    fft.getFftPeakData(audioData, numData);

    // sphere
    float angle = (ofGetElapsedTimef() * 0.1);

    for(int i = 0; i < triangles.size(); i++ ) {
        float audioValue = audioData[i];
        float mod = ofNoise(angle, i, 0.5) * -100;
        ofPoint faceNormal = triangles[i].getFaceNormal();

        for(int j = 0; j < 3; j++ ) {
            ofPoint vertex = triangles[i].getVertex(j);
            vertex += faceNormal * audioValue * mod;
            triangles[i].setVertex(j, vertex);
        }
    }

    sphere.getMesh().setFromTriangles(triangles);

}

//--------------------------------------------------------------
void ofApp::draw(){

    post.begin(cam);
    sphere.draw();
    post.end();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
