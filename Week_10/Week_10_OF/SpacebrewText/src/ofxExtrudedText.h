//
//  ofxExtrudedText.h
//  SpacebrewText
//
//  Created by Jeffrey Crouse on 4/7/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//


#pragma once
#include "ofMain.h"

class ofxExtrudedText : public ofNode {
public:
    vector<ofMesh> meshes;
    void setup(string text, float depth, ofTrueTypeFont& font);
    void update(float deltaTime);
    virtual void customDraw();
    ofRectangle bb;
    ofVec3f acc, vel, rotvel;
    string text;
    int verts;
    
    ofMesh getIndiciedMeshFromNonIndiciedMesh( ofMesh & mesh );
    void calcNormals( ofMesh & mesh, bool bNormalize );
};