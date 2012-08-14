//
//  ofxClickDownFader.h
//  
//
//  Created by Sheep on 12/06/21.
//  Copyright (c) 2012 Sheep. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "ofxClickDownMenu.h"
#define FADER_VIEW 1
#define FADER_CLOSE 2

class ofxClickDownMenu;

class ofxClickDownFader{
public:
	ofxClickDownFader(float* val,ofPoint pos);
	~ofxClickDownFader();
	
	void draw();
	
	int		phase;
	float	frame;
	int		value;
	float*	valueP;
	float	defaultV;
	float	fValue;
	float	viewValue;
	string	fader_name;
	string  okc;
	ofxClickDownMenu* parent;
	
	ofPoint window_pos;
	ofPoint window_size;
	float window_y;
	ofColor hilight;
	
	
	//Mouse & Key Events
	void mousePressed(ofMouseEventArgs& mouse);
	void mouseDragged(ofMouseEventArgs& mouse);
	void mouseMoved(ofMouseEventArgs& mouse);
	void mouseReleased(ofMouseEventArgs& mouse);
	void keyPressed(ofKeyEventArgs  &key);
	void keyReleased(ofKeyEventArgs &key);
};