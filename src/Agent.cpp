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
    targetBufferDist = 80.0f ;
    position = p ;
    bTarget = false ;
    velocity = ( ofRandom(TWO_PI) , ofRandom( TWO_PI ) ) ;

    force = ofVec3f( 0.0f , 0.0f ) ;
    maxVelocity = ofRandom( 18, 36 )  ;

    //Max turn
    maxForce = ofRandom( 0.1 , 0.5f ) ; 
    
    targetIndex = 0 ;

    trailRibbon.setup() ; 
    trailRibbon.color = color ; //colorPool.getRandomColor( ) ; 
    
    followRibbon.setup() ; 
    followRibbon.color = color ;
    
    bFirstTarget = false ; 
    
    thickness = ofRandom( 20 , 32 ) ; 
    trailRibbon.maxThickness = thickness ;  
}

void Agent::draw( ) 
{
    ofSetColor ( color ) ; 
    trailRibbon.draw() ; 
    ofPushMatrix() ; 
        ofTranslate( position ) ; 
        ofSetColor( color );
        ofSphere( 0 , 0, 0 , thickness/2 ) ; 
        //ofCircle( 0 , 0, 25 ) ; 
    ofPopMatrix() ; 
}

void Agent::update( )
{
    float dist = ofDist ( position.x , position.y , target.x , target.y ) ;
    if ( dist < targetBufferDist )
    {
        if ( bFirstTarget == false ) 
            bFirstTarget = true ; 
        
        //bTarget = true ;
       // if ( agent.bTarget == true && points.size() > 1 ) 
       // {
        targetIndex+= 1 ; 
        //cout << "target index is now : " << targetIndex << endl ; 
        //cout << " x : " << target.x << " , " << target.y << " , " << target.z << endl ; 
        if ( targetIndex >= ( followRibbon.points.size() - 1 ) ) 
        {
            targetIndex = 0 ; 
        }
          
        if ( followRibbon.points.size() > 0 ) 
        {
            target = followRibbon.points [ targetIndex ] ;
        }
        
         
        //    agent.bTarget = false ; 
        //}

    }
    
    if ( bFirstTarget == true ) 
        trailRibbon.addPoint( ofVec3f( position ) ) ;
    
    //  float dist = mousePoint.distance( agents[a]->target ) ; // ofDist( mousePoint.x , mousePoint.y , agents[a]->target.x , 
    followRibbon.update() ; // = (*ribbons[a] ) ; 
    trailRibbon.update() ;

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