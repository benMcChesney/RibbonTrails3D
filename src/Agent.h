//
//  Agent.h
//  emptyExample
//
//  Created by Ben McChesney on 2/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_Agent_h
#define emptyExample_Agent_h

#include "ofMain.h"
#include "Ribbon.h"


class Agent
{
    public :
        Agent ( ) { }

        ofColor color ;
        ofColor nextColor ;
        bool bTarget ;
        float targetBufferDist ;    //How close until selecting a new target

        float wallDistance ;

        //acceleration,
        ofVec3f target, position,  force, velocity ;
        float maxVelocity , maxForce ;


       // int colorInterpolateNum ;
       // int curIndex ;
       // int pathSampling ;
       // bool bFinished ;
    
        int targetIndex ; 
        Ribbon ribbon ; 

    /*
     ofEvents<ofVec2f> NEW_AGENT_TARGET ;
     ofEvents<ofVec2f> TELEPORT_NEW_TARGET ;
     */
        void setup( ofVec3f p ) ; 
        void update( ) ;
        void draw( ) ; 
      //  void drawAgent( ) ;
      //  void drawEntirePath ( ) ;

       // void startNewPath( )  ;
      //  void newAgentTargetHandler ( ofVec3f &args ) ;


        void addForce ( ofVec3f _force ) ;
        void seek(ofVec3f oTarget) ;
        void setTarget( ofVec3f _target ) ;


};

#endif
