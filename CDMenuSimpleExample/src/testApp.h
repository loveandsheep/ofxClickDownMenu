#pragma once

#include "ofMain.h"
#include "ofxClickDownMenu.h"

#define SHAPE_RECT 0
#define SHAPE_CIRCLE 1
#define SHAPE_TRIANGLE 2

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	void cmdEvent(ofxCDMEvent &ev);
	ofxClickDownMenu Menu;

	ofColor col;
	int shape;
	float brightness;
	float size;
};
