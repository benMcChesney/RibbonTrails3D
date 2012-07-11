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
    ofBackground( 200 );
		
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
    
    numRibbons = 0 ; 
    numParticles = 3 ; 
    createAgents( true ) ; 
    setupUI() ; 
}

//--------------------------------------------------------------
void testApp::update(){
       
    ofVec3f mousePoint( mouseX , ofGetHeight() - mouseY , sin( ofGetElapsedTimef() * 5 ) * 200.0f ) ; //sin ( ofGetElapsedTimef() * 1.5 ) * 300.0f );
    
    ofVec3f offset = ofVec3f ( ofGetWidth() / 2 , ofGetHeight() /2  , 0 ) ; 
    mousePoint -= offset ; 
    
    for ( int a = 0 ; a < agents.size() ; a++ ) 
    {
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

    string status = "'(MOUSE DRAG)' draw ribbon - enabled ? " ;
    if ( camera.getMouseInputEnabled() == false &&  gui->isEnabled() == false )
        status += "ENABLED" ; 
    else
        status += "DISABLED" ; 
    
    status += "\n" ; 
    
    status += "'M' ofEasyCam mouse - enabled ? " ; 
    if ( camera.getMouseInputEnabled() == true ) 
        status += " ENABLED" ; 
    else
        status += " DISABLED" ; 
    
    status += "\n" ; 
    status += "'G' toggle ofxUI - enabled ? " ; 
    if ( gui->isEnabled() == true ) 
        status += " ENABLED" ; 
    else
        status += " DISABLED" ; 
    
    ofDrawBitmapString( status , 30 , ofGetHeight() - 60 ) ; 
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
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.01, 50.0f , maxSpeed, "MAX SPEED" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.01, 15.0f , maxSpeedRandom, "MAX SPEED RANDOM" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 5.0f, 300.0f , bufferDistance, "BUFFER DISTANCE" )); 
    
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 1, 100 , tailLength, "TRAIL LENGTH" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 1, 100 , tailLengthRandom, "TRAIL LENGTH RANDOM" )); 
    
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 1, 100 , thickness, "THICKNESS" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 1, 100 , thicknessRandom, "THICKNESS RANDOM" ));
    
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 2, 100 , numParticles, "NUM PARTICLES" ));
    
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
        updateAgents( )  ;
    }
    
    if(name == "MAX FORCE RANDOM" )
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		maxForceRandom = slider->getScaledValue(); 
        updateAgents( )  ;
    }
    
    if(name == "MAX SPEED" )
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		maxSpeed = slider->getScaledValue(); 
        updateAgents( )  ;
    }
    
    if(name == "MAX SPEED RANDOM" )
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		maxSpeedRandom = slider->getScaledValue(); 
        updateAgents( )  ;
    }
    if ( name ==  "BUFFER DISTANCE"  ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
		bufferDistance = slider->getScaledValue(); 
        updateAgents( )  ;
    }

    if ( name == "TRAIL LENGTH" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        tailLength = slider->getScaledValue();
        updateAgentTrails( ) ; 
    }
    
    if ( name == "TRAIL LENGTH RANDOM" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        tailLengthRandom = slider->getScaledValue();
        updateAgentTrails( ) ; 
    }
    
    if ( name == "THICKNESS" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        thickness = slider->getScaledValue();
        updateAgentTrails ( ) ; 
    }
    
    if ( name == "THICKNESS RANDOM" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        thicknessRandom = slider->getScaledValue();
        updateAgentTrails ( ) ; 
    }
    
    if ( name == "NUM PARTICLES" ) 
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        numParticles = slider->getScaledValue();
        createAgents() ; 
    }
    gui->saveSettings("GUI/settings.xml") ; 
     
}

void testApp::updateAgentTrails( ) 
{
    //Trails are seperate from flocking parameters
    for ( int i = 0 ; i < agents.size() ; i++ ) 
    {
        //Only update if the random range will never make it go below 0 
        if ( tailLengthRandom < tailLength ) 
            agents[i]->trailRibbon.tailLength = tailLength + ofRandom ( -tailLengthRandom , tailLengthRandom ) ; 
        
        if ( thicknessRandom < thickness ) 
            agents[i]->trailRibbon.maxThickness = thickness + ofRandom ( -thicknessRandom , thicknessRandom ) ;
    }
}

void testApp::updateAgents( ) 
{
    if ( agents.size() > 0 ) 
    {
        //Update the flocking parameters
        for ( int i = 0 ; i < agents.size() ; i++ ) 
        {
            //Only update if the random range will never make it go below 0 
            if ( maxForceRandom < maxForce ) 
                agents[i]->maxForce = maxForce + ofRandom( -maxForceRandom , maxForceRandom ) ;
            if ( maxSpeedRandom < maxSpeed ) 
                agents[i]->maxVelocity = maxSpeed + ofRandom( -maxSpeedRandom , maxSpeedRandom ) ;

            agents[i]->targetBufferDist = bufferDistance ; 
        }
    }
}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

void testApp::createAgents( bool bFirstMake )
{
    int oldNum = numRibbons ; 
    numRibbons = numParticles ; //ofRandom ( numParticles ) ; 
    
    if ( bFirstMake == true ) 
    {
        agents.clear() ; 
        for ( int i = 0 ; i < numRibbons ; i++ ) 
        {
            Agent * agent = new Agent() ; 
            agent->color = colorPool.getRandomColor( ) ; 
            agent->setup( ofVec3f( 0 , 0, 0 ) ) ;
            agents.push_back( agent ) ;
            
        } 
        
        updateAgents( ) ; 
        updateAgentTrails( ) ; 
        return ; 
    }
    //agents.clear() ; 
    
    if ( agents.size() > 0 ) 
    {
        int diff = oldNum - numRibbons ; 
        cout << "agent # difference is : " << diff << endl ; 
        // Diff > 0 
        if ( oldNum > numRibbons ) 
        {
            cout << "more last time than before! " << endl ; 
            for ( int a = 0 ; a < diff ; a++ ) 
            {
                agents.pop_back() ; 
            }
        }
        else
        {
            cout << "less last time than before! " << endl ;  
            int absDiff = abs( diff ) ; 
            for ( int b = 0 ; b < absDiff ; b++ ) 
            {
                Agent * agent = new Agent() ; 
                agent->color = colorPool.getRandomColor( ) ; 
                agent->setup( ofVec3f( 0 , 0, 0 ) ) ;
                agent->followRibbon = agents[0]->followRibbon ; 
                agents.push_back( agent ) ;

            }
        }
    }

    updateAgents( ) ; 
    updateAgentTrails( ) ; 
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if ( camera.getMouseInputEnabled() == true ) //|| gui->isVisible() == true ) 
        return ; 
    
    
    cout << "past mouse pressed ! " << endl ; 
    
    if ( gui->isEnabled() == true ) 
        return ; 
    
    cout << "past GUI" << endl ; 
    //Reset all of our ribbons
    bMouseDown = true ; 
    
    numRibbons = 0 ;
    createAgents( true ) ; 
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    if ( camera.getMouseInputEnabled() == true ) 
        return ; 
    
    if ( gui->isEnabled() == true ) 
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