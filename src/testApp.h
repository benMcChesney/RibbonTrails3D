/**
 *
 * OFDevCon Example Code Sprint
 * Camera Ribbon example
 * This example generates ribbons along the mouse trail that descend in space
 * When you click space bar, you can
 *
 * Created by James George for openFrameworks workshop at Waves Festival Vienna sponsored by Lichterloh and Pratersauna
 * Adapted during ofDevCon on 2/23/2012
 */

#pragma once

#include "ofMain.h"
#include "Ribbon.h"
#include "ColorPool.h"
#include "ofxUI.h"
#include "Agent.h"

class testApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
	
	//this holds all of our points
    //vector<ofVec3f> points;
    //this keeps track of the center of all the points
    ofVec3f center;
    
	//our camera objects for looking at the scene from multiple perspectives
	ofEasyCam camera;
	
	//if usecamera is true, we'll turn on the camera view
    bool usecamera;

//    vector<Ribbon*> ribbons ; 
    int numRibbons ; 
    
    vector<Agent*> agents ; 
    
    bool bMouseDown ; 
    
    ColorPool colorPool ; 
    
    ofxUICanvas *gui;   	
	void guiEvent(ofxUIEventArgs &e);
    bool drawPadding; 
    
    void setupUI( ) ; 
    
    float maxForce ; 
    float maxForceRandom ; 
    float maxSpeed ; 
    float maxSpeedRandom ; 
    float bufferDistance ; 
    
    void updateAgents() ; 
    
    
};
