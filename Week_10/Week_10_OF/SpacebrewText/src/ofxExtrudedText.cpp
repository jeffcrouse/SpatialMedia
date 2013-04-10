//
//  ofxExtrudedText.cpp
//  SpacebrewText
//
//  Created by Jeffrey Crouse on 4/7/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "ofxExtrudedText.h"


// --------------------------------------------------
void ofxExtrudedText::setup(string _text, float depth, ofTrueTypeFont& font) {
    text = _text;
    bb = font.getStringBoundingBox(text, 0, 0);
    verts = 0;
    vector<ofPath> letterPaths = font.getStringAsPoints(text);
    for(int i=0; i<letterPaths.size(); i++)
    {
        ofPath& letter = letterPaths[i];
        letter.translate(ofPoint(-bb.width/2.0, bb.height/2.0, depth/2.0));
        vector<ofPolyline>& lines = letter.getOutline();
        for(int j=0; j<lines.size(); j++) {
            lines[j].simplify(1.1);
        }
        
        
        
        ofMesh front = letter.getTessellation();
        ofMesh back = front;
        ofMesh side;
        
        // Loop through all of the vertices that we just added.
        vector<ofPoint>& vf = front.getVertices();
        vector<ofPoint>& vb = back.getVertices();
        for (int j=0; j<vf.size(); j++)
        {
            front.addNormal(ofVec3f(0,0,-1));
            front.addColor( ofColor::violet );
            
            vb[j].z -= depth;
            back.addNormal(ofVec3f(0,0,1));
            back.addColor(ofColor::steelBlue);
        }

        
        // The path of a letter may contain several different lines
        // Think about the inside of a shape with a hole like "O", "P", "D"
        for(int j=0; j<lines.size(); j++)
        {
            // Now we have to make the "ribbon" that gets sandwiched between
            // the front and the back
            // Loop through all of the points and make 2 triangles at a time:
            // the first one uses 2 points from "front" and one from "back"
            // the second uses 2 from "back" and 1 from "front"
            vector<ofPoint>& points = lines[j].getVertices();
            int k;
            for(k=0; k<points.size()-1; k++)
            {
                ofPoint p1 = points[k+0];
                ofPoint p2 = points[k+1];
                
                side.addVertex(p1);
                side.addVertex(p2);
                side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
                
                side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth));
                side.addVertex(p2);
            }
            
            // Connect the last triangles to the first
            ofPoint p1 = points[k];
            ofPoint p2 = points[0];
            
            side.addVertex(p1);
            side.addVertex(p2);
            side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
            
            side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
            side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth));
            side.addVertex(p2);
        }
        
        side = getIndiciedMeshFromNonIndiciedMesh( side );
        calcNormals( side, true );
        
        meshes.push_back(front);
        meshes.push_back(back);
        meshes.push_back(side);
    
        verts += front.getNumVertices();
        verts += back.getNumVertices();
        verts += side.getNumVertices();
    }
    //translate(-bb.width/2.0, -bb.height/2.0, 0);
    
    setPosition(ofRandomWidth(), ofRandom(-bb.height, -bb.height*3), 0);
    vel.set(0, 0, 0);
    acc.set(0, 200, 0);
    float r = 100;
    rotvel.set(ofRandom(-r, r), ofRandom(-r, r), ofRandom(-r, r));
    setScale(2);
}


// --------------------------------------------------
ofMesh ofxExtrudedText::getIndiciedMeshFromNonIndiciedMesh( ofMesh & mesh ){
    
    ofMesh newMesh;
    vector < ofPoint > uniqueVertices;
    for (int i = 0; i < mesh.getVertices().size(); i++){
        
        int id = -1;
        for (int j = 0; j < uniqueVertices.size(); j++){
            if ( (uniqueVertices[j] - mesh.getVertices()[i]).length() < 0.1f){
                id = j;
            }
        }
        
        if (id == -1){
            uniqueVertices.push_back(mesh.getVertices()[i]);
            id = uniqueVertices.size() - 1;
            newMesh.addVertex(mesh.getVertices()[i]);
        }
        
        newMesh.addIndex(id);
    }
    return newMesh;
}


//--------------------------------------------------------------------------
void ofxExtrudedText::calcNormals( ofMesh & mesh, bool bNormalize ){
    
    for( int i=0; i < mesh.getVertices().size(); i++ ) mesh.addNormal(ofPoint(0,0,0));
    
    for( int i=0; i < mesh.getIndices().size(); i+=3 ){
        const int ia = mesh.getIndices()[i];
        const int ib = mesh.getIndices()[i+1];
        const int ic = mesh.getIndices()[i+2];
        
        ofVec3f e1 = mesh.getVertices()[ia] - mesh.getVertices()[ib];
        ofVec3f e2 = mesh.getVertices()[ic] - mesh.getVertices()[ib];
        ofVec3f no = e2.cross( e1 );
        
        // depending on your clockwise / winding order, you might want to reverse the e2 / e1 above if your normals are flipped.
        
        mesh.getNormals()[ia] += no;
        mesh.getNormals()[ib] += no;
        mesh.getNormals()[ic] += no;
    }
    
    if (bNormalize)
        for(int i=0; i < mesh.getNormals().size(); i++ ) {
            mesh.getNormals()[i].normalize();
        }
}


// --------------------------------------------------
void ofxExtrudedText::update(float deltaTime) {
    
    vel += (acc * deltaTime);
    
    setPosition(getPosition() + vel * deltaTime);
    
  	tilt(rotvel.x * deltaTime);						// tilt up+down (around local x axis)
	pan(rotvel.y * deltaTime);						// rotate left+right (around local y axis)
	roll(rotvel.z * deltaTime);						// roll left+right (around local z axis)
}


// --------------------------------------------------
void ofxExtrudedText::customDraw() {

    //ofSetColor(255, 0, 0);
    //ofSphere(0, 0, 0, 10);
    
    ofSetColor(255);
    for(int i=0; i<meshes.size(); i++) {
        meshes[i].drawFaces();
    }
}