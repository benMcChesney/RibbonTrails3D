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


#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	//just set up the openFrameworks stuff
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);
		
	//initialize the variable so it's off at the beginning
    bMouseDown = false ; 
    
    //Add some nice looking colors, acquired from adobe kuler
    ofColor col1 = ofColor ( 0 , 166 , 149 ) ; 
    ofColor col2 = ofColor ( 255 , 51 , 0 ) ; 
    ofColor col3 = ofColor ( 255 , 102 , 0 ) ; 
    ofColor col4 = ofColor ( 255 , 166 , 0 ) ; 
    ofColor col5 = ofColor ( 255 , 217 , 0 ) ; 
    
    colorPool.addColor( col1 ) ; 
    colorPool.addColor( col2 ) ; 
    colorPool.addColor( col3 ) ; 
    colorPool.addColor( col4 ) ; 
    colorPool.addColor( col5 ) ; 
    
    camera.setPosition( ofGetWidth()/2 , ofGetHeight()/2 , -100 ) ; //ofGetWidth()/2, ofGetHeight()/2, 0 ) ; 
    
    setupUI() ; 
    //camera.enableMouseInput() ; 
    //camera.disableMouseInput() ;
    //gui->toggleVisible() ; 
   

}

//--------------------------------------------------------------
void testApp::update(){
       
    ofVec3f mousePoint( mouseX , ofGetHeight() - mouseY , sin( ofGetElapsedTimef() * 5 ) * 200.0f ) ; //sin ( ofGetElapsedTimef() * 1.5 ) * 300.0f );
    
    ofVec3f offset = ofVec3f ( ofGetWidth() / 2 , ofGetHeight() /2  , 0 ) ; 
    mousePoint -= offset ; 
    
    for ( int a = 0 ; a < agents.size() ; a++ ) 
    {
        //agents[a]->setTarget( mousePoint ) ; 
        agents[a]->update( ) ; 
        if ( bMouseDown == true )  // && gui->isVisible() == false && camera.getMouseInputEnabled() == false ) 
        {
            agents[a]->followRibbon.addPoint( mousePoint ) ; 
        }
    }
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
	
    
	//if we're using the camera, start it.
	//everything that you draw between begin()/end() shows up from the view of the camera
    camera.begin();

    
    //Draw the ribbons ! Nice and simple
    for ( int a = 0 ; a < agents.size() ; a++ ) 
    {
        agents[a]->draw( ) ; 
    }  
		
	//if we're using the camera, take it away
    camera.end();
    
    
    ofSetColor( 15 , 15 , 15 ) ; 
    
    string status = " ofEasyCam mouse input is : " ; 
    if ( camera.getMouseInputEnabled() == true ) 
        status += " ENABLED" ; 
    else
        status += " DISABLED" ; 
    
    status += "\n" ; 
    
    ofDrawBitmapString( status , 30 , ofGetHeight() - 35 ) ; 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch ( key ) 
    {
        case 'm':
        case 'M':
            cout << "toggeling mouse!" << endl ; 
            //Toggle mouse on the camera
            
            if ( !camera.getMouseInputEnabled() ) 
                camera.enableMouseInput() ; 
            else
                camera.disableMouseInput() ; 
            break  ;
            
        case 'g':
        case 'G':
            gui->toggleVisible() ; 
            break ; 
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

// ofxUI
 
void testApp::setupUI ( ) 
{
    float dim = 24; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 180-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
	
    //gui->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE));  
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.01, 9.0f , maxForce, "MAX FORCE" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.01, 3.0f , maxForceRandom, "MAX FORCE RANDOM" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.01, 25.0f , maxSpeed, "MAX SPEED" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.01, 15.0f , maxSpeedRandom, "MAX SPEED RANDOM" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 5.0f, 300.0f , bufferDistance, "BUFFER DISTANCE" )); 
    
     ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui->loadSettings("GUI/settings.xml") ; 
    

    gui->toggleVisible() ; 
}


//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	if(name == "MAX FORCE")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		maxForce = slider->getScaledValue(); 
    }
    
    if(name == "MAX FORCE RANDOM" )
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		maxForceRandom = slider->getScaledValue(); 
    }
    
    if(name == "MAX SPEED" )
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		maxSpeed = slider->getScaledValue(); 
    }
    
    if(name == "MAX SPEED RANDOM" )
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		maxSpeedRandom = slider->getScaledValue(); 
    }
    if ( name ==  "BUFFER DISTANCE"  ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		bufferDistance = slider->getScaledValue(); 
        
    }

    gui->saveSettings("GUI/settings.xml") ; 
    updateAgents( )  ; 
}

void testApp::updateAgents( ) 
{
    return ; 
    
    for ( int i = 0 ; i < agents.size() ; i++ ) 
    {
        agents[i]->maxForce = maxForce + ofRandom( -maxForceRandom , maxForceRandom ) ;
        agents[i]->maxVelocity = maxSpeed + ofRandom( -maxSpeedRandom , maxSpeedRandom ) ;
        agents[i]->targetBufferDist = bufferDistance ; 
    }
}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    }

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if ( camera.getMouseInputEnabled() == true ) 
        return ; 
    
   // if ( gui->isVisible() == true )
   //     return ; 
    
    //Reset all of our ribbons
    bMouseDown = true ; 
    
    numRibbons = ofRandom ( 85 , 125 ) ;  
    agents.clear() ; 
    
    for ( int i = 0 ; i < numRibbons ; i++ ) 
    {
        Agent * agent = new Agent() ; 
        agent->color = colorPool.getRandomColor( ) ; 
        agent->setup( ofVec3f( 0 , 0, 0 ) ) ;
        agents.push_back( agent ) ; 
    }
    
    updateAgents( ) ; 
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    if ( camera.getMouseInputEnabled() == true || gui->isVisible() == true ) 
        return ; 
    
    //End our drawing
    bMouseDown = false ; 
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}