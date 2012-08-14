#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetCircleResolution(40);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	brightness	= 0.8;
	size		= 0.8;
	shape		= SHAPE_RECT;
	
	
	/*-------------Define Menu Property-------------*/
	Menu.OnlyRightClick = false;
	Menu.menu_name = "mainMenu";
	
	//Standard Button Menus
	Menu.RegisterMenu("Rect");
	Menu.RegisterMenu("Circle");
	Menu.RegisterMenu("Triangle");
	
	//Branch Buttons Menu
	vector<string> BranchMenu_Color;
	BranchMenu_Color.push_back("Red");
	BranchMenu_Color.push_back("Blue");
	BranchMenu_Color.push_back("Green");
	Menu.RegisterBranch("Color", &BranchMenu_Color);
	
	//Fader Menu(Range is 0.0f~1.0f)
	Menu.RegisterFader("Alpha", &brightness);
	Menu.RegisterFader("Size", &size);
	
	//Add Event Listener
	ofAddListener(ofxCDMEvent::MenuPressed, this, &testApp::cmdEvent);
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0, 0, 0);
	
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString("Click & open Menu Dialog.", 30,30);
	
	/*-------------Draw Menu-------------*/
	Menu.draw();
	
	col.a = 255 * brightness; 
	ofSetColor(col);
	
	switch (shape) {
		case SHAPE_RECT:
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(ofGetWidth()/2, ofGetHeight()/2, 300*size, 300*size);
			ofSetRectMode(OF_RECTMODE_CORNER);
			break;
			
		case SHAPE_CIRCLE:
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 150*size);
			break;
			
		case SHAPE_TRIANGLE:
			ofSetCircleResolution(3);
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 150*size);
			ofSetCircleResolution(40);
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void testApp::cmdEvent(ofxCDMEvent &ev){
	/*-------------Catch menu messages-------------*/
	if (ev.message == "mainMenu::Rect") shape = SHAPE_RECT;
	if (ev.message == "mainMenu::Circle") shape = SHAPE_CIRCLE;
	if (ev.message == "mainMenu::Triangle") shape = SHAPE_TRIANGLE;

	if (ev.message == "mainMenu::Color::Red") col.set(255, 0, 0);
	if (ev.message == "mainMenu::Color::Blue") col.set(0, 0, 255);
	if (ev.message == "mainMenu::Color::Green") col.set(0, 255, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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