//
//  Agent.cpp
//  emptyExample
//
//  Created by Ben McChesney on 6/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Agent.h"

/*
 void teleportNewTargetHandler ( ofVec2f &args )
 {
 cout << "teleport handler called!" << endl ;
 position = args ;
 setTarget ( args ) ;
 startNewPath() ;
 }
 */

void Agent::setup( ofVec3f p ) // , ofVec3f a , float _wallDistance = 1.0f )
{
    targetBufferDist = 50.0f ;
    //wallDistance = _wallDistance ;
    position = p ;
    //acceleration = a ;
    bTarget = false ;

   // position = ofVec3f ( ofGetWidth()/2 , ofGetHeight()/2 , 0 ) ;
    //velocity = ofVec2f ( 1 ,  ofRandom( TWO_PI )  ) ;

    velocity = ( ofRandom(TWO_PI) , ofRandom( TWO_PI ) ) ;
    //acceleration = ofVec2f( .4 , .4 ) ;

    force = ofVec3f( 0.0f , 0.0f ) ;
    maxVelocity = ofRandom( 9, 12 )  ;

    //Max turn
    maxForce = ofRandom( 0.1 , 0.5f ) ; 
    
    targetIndex = 0 ;

}

void Agent::draw( ) 
{
    ofSetColor ( color ) ; 
    //ribbon.draw() ; 
    ofPushMatrix() ; 
        ofTranslate( position ) ; 
        ofSetColor( color );
        ofCircle( 0 , 0, 25 ) ; 
    ofPopMatrix() ; 
}

void Agent::update( )
{
    ribbon.update() ; 
    ribbon.addPoint( position ) ; 
    ribbon.maxThickness = 6 ; 
    ribbon.color = color ; 
 //   if ( bFinished )
 //       return ;
    
    float dist = ofDist ( position.x , position.y , target.x , target.y ) ;
    if ( dist < targetBufferDist )
    {
        
        //bTarget = true ;
       // if ( agent.bTarget == true && points.size() > 1 ) 
       // {
        targetIndex+= 1 ; 
        cout << "target index is now : " << targetIndex << endl ; 
        cout << " x : " << target.x << " , " << target.y << " , " << target.z << endl ; 
        if ( targetIndex >= ( ribbon.points.size() - 1 ) ) 
        {
            targetIndex = 0 ; 
        }
          
        if ( ribbon.points.size() > 0 ) 
        {
            target = ribbon.points [ targetIndex ] ;
        }
        //    agent.bTarget = false ; 
        //}

    }
/*
    if ( ofGetFrameNum() % pathSampling == 0 )
    {
        curIndex++ ;
        ColorPoint cp ;


        if ( curIndex == colorInterpolateNum )
        {
            curIndex = 0 ;
            color = nextColor ;
            nextColor = colorPool.getRandomColor() ;
        }

        float ratio = (float)curIndex / (float)colorInterpolateNum ;
        ofColor lerp = color.lerp( nextColor , ratio ) ;
        cp.color = lerp ;
        cp.color.a = ofRandom( 255.0f * .7 , 255.0f * 1.0f ) ;
        cp.position = position ;
        cp.radius =  ofRandom ( 0.25 , 4 ) ; //4 + sin( ofGetElapsedTimef() ) * 1 ;
        curPath.addPoint( cp ) ; //.push_back( cp ) ;
    }
 */
    force.limit(maxForce);
    velocity += force;

    velocity.limit(maxVelocity);
    position += velocity;

    /*
     NO WRAP
     int w = ofGetWidth() ;
     int h = ofGetHeight() ;
     if ( position.x < 0 )
     position.x += w ;
     if ( position.x > w )
     position += -w ;
     if ( position.y < 0 )
     position.y += h ;
     if ( position.y > h )
     position.y += -h ;
     */
    seek( target ) ;
}

void Agent::addForce ( ofVec3f _force )
{
    force += _force ;
}

void Agent::seek(ofVec3f oTarget)
{

    //From Roxlu's Boids code ( www.roxlu.com )
    // This is how it works.
    // 1. We calculate the change in position which would bring
    // use directly to the target. This is "desired_vel". Though we don't
    // want to jump directly to this target, but slowly move to it.
    ofVec3f desiredVelocity = oTarget - position;

    // 2. Therefore we want to move to this position at the maximum
    // allowed speed. We do this by normalizing the vector and then
    // multiplying it with the maximum allowed speed. This is exactly
    // what ofxVec3f.scale() does.
    desiredVelocity.scale(maxVelocity);

    // 3. Now we have the maximum desired velocity at the maximum speed.
    // Though we need to adjust this speed as we want to go into that direction
    // at the best we are allowed, which is the remaining velocity.
    desiredVelocity -= velocity;

    addForce(desiredVelocity);

    //cout << "Desired vel: " << desired_vel.x << ", " << desired_vel.y << endl;
}

void Agent::setTarget( ofVec3f _target )
{
    target = _target ;
    bTarget = false ;
}