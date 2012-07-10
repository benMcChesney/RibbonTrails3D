//
//  Ribbon.h
//  cameraRibbonExample
//
//  Created by Ben McChesney on 7/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef cameraRibbonExample_Ribbon_h
#define cameraRibbonExample_Ribbon_h

#include "ofMain.h"

//Quick class to wrap the 3d mesh trail

class Ribbon
{
    public : 
    
        Ribbon ( ) { } ; 
        ~Ribbon ( ) { } ; 
        
        ofMesh mesh ; 
        
        
        vector<ofVec3f> points ;    //Center point for all our points
    
        
        int currentIndex ;          //Where the tail starts
        int tailLength ;            //How long the tail is
    
        ofColor color ;             //Color of mesh
        ofVec3f offset ;            //Offset from ribbon center
    
        float maxThickness ;        //Varying thickness per ribbon
        bool bDoneDrawing ;
    
        
        
        void setup ( ) 
        {
            currentIndex = 1 ; 
            tailLength = ofRandom ( 12 , 55 ) ; 
            color = ofColor( ofRandom( 255 ) , ofRandom( 255 ) , ofRandom ( 255 ) ) ; 
            
            float range = 46 ; 
            offset = ofVec3f ( ofRandom( -range , range ) , ofRandom ( -range , range ) , ofRandom ( -range , range ) ) ; 
            maxThickness = ofRandom ( 8 , 25 ) ; 
            bDoneDrawing = false ; 
            
            
            //cout << "setup : " << endl ; 
        } 
        
        void reset ( ) 
        {
            points.clear() ; 
            bDoneDrawing = true ; 
        }
    
        void update ( ) 
        {
            //Increment the index , if above the # of particles we have start at 0 again
            currentIndex++ ; 
            if ( currentIndex >= ( points.size() -1 ) ) 
            {
                currentIndex = 1 ; 
            }
        } 
        
        void addPoint ( ofVec3f p ) 
        {
            //Add our offset to the points list
            p = p + offset ; 
            points.push_back( p ) ; 
        }
    
        void draw ( ) 
        {
            
            mesh.clear() ; 
            ofSetColor( color );
            //do the same thing from the first example...
            
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP); 
            
            int minIndex = currentIndex - tailLength ; 
            for(int i = 1; i < points.size(); i++){
                
                

                if ( ( i < currentIndex ) && ( i > minIndex ) ) 
                {
                    float ratio = 0.0f ; 
                    ratio = (float) ( i - minIndex ) / ( float ) tailLength ; 
                    //find this point and the next point
                    ofVec3f thisPoint = points[i-1];
                    ofVec3f nextPoint = points[i];
                    
                    //get the direction from one to the next. 
                    //the ribbon should fan out from this direction
                    ofVec3f direction = (nextPoint - thisPoint);
                    
                    //get the distance from one point to the next
                    float distance = direction.length();
                    
                    //get the normalized direction. normalized vectors always have a length of one
                    //and are really useful for representing directions as opposed to something with length
                    ofVec3f unitDirection = direction.normalized();
                    
                    //find both directions to the left and to the right
                    float offset = sin ( ofGetElapsedTimef() ) * ( maxThickness * 0.15 )  ; 
                    ofVec3f toTheLeft = unitDirection.getRotated(-90 - offset , ofVec3f(0,0,1));
                    ofVec3f toTheRight = unitDirection.getRotated(90 + offset , ofVec3f(0,0,1));
                    
                    //use the map function to determine the distance.
                    //the longer the distance, the narrower the line. 
                    //this makes it look a bit like brush strokes
                    float thickness = ofMap(distance, 0, 60 , 1.0f , maxThickness * ratio + 1.1f , true);
                    
                    //calculate the points to the left and to the right
                    //by extending the current point in the direction of left/right by the length
                    ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
                    ofVec3f rightPoint = thisPoint+toTheRight*thickness;
                    
                    //add these points to the triangle strip
                    mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
                    mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
                }
            }
            
            //end the shape
            mesh.draw(); 
        } 

};

#endif
