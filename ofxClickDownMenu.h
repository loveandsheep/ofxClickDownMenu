//
//  ofxClickDownMenu.h
//  
//
//  Created by Sheep on 12/06/21.
//  Copyright (c) 2012 Sheep. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include <GLUT/GLUT.h> 
#include "ofxCDMEvent.h"
#include "ofxClickDownFader.h"

#define PHASE_WAIT 0
#define PHASE_CLICK 1
#define PHASE_WAIT_SELECT 2
#define PHASE_BRANCH 3
#define PHASE_SELECT 4
#define PHASE_BACK 5

class ofxClickDownFader;

struct ofxCDMButton{
	string message;
	bool isBranch;
	bool isFader;
	float* fader_Pointer;
	vector<string> branchmenu;
};

class ofxClickDownMenu{
public:
	ofTrueTypeFont font;
	
	ofColor hilight;
	ofColor hl;
	ofxClickDownMenu();
	~ofxClickDownMenu();
	void draw();
	void RegisterMenu(string Menu);
	void RegisterBranch(string Menu,vector<string> *Menus);
	void RegisterFader(string Menu,float *valueP);
	
	
	void openMenu(int x,int y);
	void doFunction();
	
	ofPoint menu_pos;
	string menu_name;
	deque<ofxCDMButton> menus;

	ofPoint window_pos;
	ofPoint window_size;
	float window_y;
	float focus_y;
	int phase;
	float frame;
	int menu_focused;
	
	ofxClickDownMenu *child;
	ofxClickDownFader *fchild;
	bool haveChild;
	bool haveFChild;
	bool isChild;
	ofxClickDownMenu *parent;
	
	bool useFont;
	bool OnlyRightClick;
	
	//Mouse & Key Events
	void mousePressed(ofMouseEventArgs& mouse);
	void mouseDragged(ofMouseEventArgs& mouse);
	void mouseMoved(ofMouseEventArgs& mouse);
	void mouseReleased(ofMouseEventArgs& mouse);
	void keyPressed(ofKeyEventArgs  &key);
	void keyReleased(ofKeyEventArgs &key);

};