//
//  ofxClickDownMenu.cpp
//  
//
//  Created by Sheep on 12/06/21.
//  Copyright (c) 2012 Sheep. All rights reserved.
//

#include "ofxClickDownMenu.h"

ofxClickDownMenu::ofxClickDownMenu(){
	OnlyRightClick = true;
	useFont = false;
	
	font.loadFont("BEBAS___.TTF", 10);
	phase = PHASE_WAIT;
	frame = 0;
	window_size = ofPoint(0,100);
	
	ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);

	menu_focused = -1;
	haveChild = false;
	haveFChild = false;
	isChild = false;
	hilight.setHsb(235, 255, 255,180);
	focus_y = 1;
	Enable = true;
}

ofxClickDownMenu::~ofxClickDownMenu(){
	ofUnregisterMouseEvents(this);
	ofUnregisterKeyEvents(this);
}

void ofxClickDownMenu::draw(){
    glDisable(GL_DEPTH_TEST);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	if (phase == PHASE_CLICK){
		frame += 1 * 90.0f / ofGetFrameRate();
		window_y += (window_size.y - window_y) / 5.0 * 120.0f / ofGetFrameRate();
		window_y = MIN(window_size.y,window_y);
		ofSetColor(255, 255, 255,140);
		ofNoFill();
		ofRect(window_pos,window_size.x,window_y);
		ofFill();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(0, 0, 0,255);
		ofRect(window_pos,window_size.x,window_y);
		
		for (int i = 0;i < menus.size();i++){
			if (frame > i*3) {
				ofSetColor(255,255,255,100);
				if (i > 0) ofLine(window_pos.x		, window_pos.y+i*20, 
								  window_pos.x+window_size.x*(1-(powf((MIN(1.0,MAX(0.0,frame-i*3)/15.0))-1.0,4.0))),
								  window_pos.y+i*20);
				ofSetColor(255,255,255);
				string mes = "";
				
				mes += menus[i].message.substr(0,MIN(menus[i].message.length(),(frame-i*3)/2));
				
				for (int j = 0;j < MAX(0,(float)menus[i].message.length()-MAX(0,(frame-i*3)/2));j++){
					mes += ofToString((char)ofRandom(33,120));
				}
				if (menus[i].isBranch) mes += " >";
				if (useFont){
					font.drawString(mes, window_pos.x+4,window_pos.y+i*20+15);					
				}else{
					ofDrawBitmapString(mes, window_pos.x+4,window_pos.y+i*20+13);					
				}
			}
			if (menu_focused == i){
				ofEnableBlendMode(OF_BLENDMODE_ADD);
				ofSetColor(hilight);
//				ofRect(window_pos.x,window_pos.y+i*20, window_size.x, 20);
				ofEnableBlendMode(OF_BLENDMODE_ALPHA);
			}
		}
		ofSetColor(hilight);
		focus_y += (menu_focused*20 - focus_y) / 2.0;
		focus_y = MAX(0,focus_y);
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofRect(window_pos.x, window_pos.y+focus_y, window_size.x, 20);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	}
	if (phase == PHASE_SELECT){
		frame += 1 * 90.0f / ofGetFrameRate();;
		ofSetHexColor(0xFFFFFF);
		if (frame > 7) ofSetColor(255*(ofGetFrameNum()%2));
		if (useFont){
			font.drawString(menus[menu_focused].message, window_pos.x+4,window_pos.y+menu_focused*20+15);				
		}else{
			ofDrawBitmapString(menus[menu_focused].message, window_pos.x+4,window_pos.y+menu_focused*20+13);	
		}
		
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		if (frame > 7) ofSetColor(hilight.r,hilight.g,hilight.b,255*ofGetFrameNum()%2);
		else		   ofSetColor(hilight);

		hl.a -= 20;
		ofSetColor(hl);
		ofNoFill();

		ofRect(window_pos.x,window_pos.y+menu_focused*20+10, window_size.x, 5.0/(frame));
		ofRect(window_pos.x, window_pos.y, window_size.x, window_size.y);
		ofFill();
		if (frame > 15){
			if (isChild){
				parent->haveChild = false;
				delete this;
			}
			phase = PHASE_WAIT;
		}
	}				
	
	if (haveChild) child->draw();
	if (haveFChild)fchild->draw();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetRectMode(OF_RECTMODE_CORNER);
}

void ofxClickDownMenu::mousePressed(ofMouseEventArgs &mouse){
	hl = hilight;
	if (haveChild) return;
	if (haveFChild)return;
	if (phase == PHASE_SELECT) return;
	if ((phase == PHASE_WAIT)&&(Enable)){
		if (((mouse.button == 2)&&(OnlyRightClick))||(!OnlyRightClick)) {
			openMenu(mouse.x,mouse.y);
		}
	}else if (phase == PHASE_CLICK){
		if (menu_focused != -1){
			doFunction();
		}else{
			menu_focused = menus.size()-1;
			doFunction();
		}
	}
	
	
}

void ofxClickDownMenu::mouseDragged(ofMouseEventArgs &mouse){
	
}

void ofxClickDownMenu::mouseMoved(ofMouseEventArgs &mouse){
	if (phase == PHASE_CLICK){
		if ((!haveChild)&&(!haveFChild)){
			if ((window_pos.x < mouse.x)&&(mouse.x < window_pos.x+window_size.x)&&
				(window_pos.y < mouse.y)&&(mouse.y < window_pos.y+window_size.y)){
				menu_focused = (mouse.y - window_pos.y)/20;
			}else{
				menu_focused = -1;
			}
		}
	}
}

void ofxClickDownMenu::mouseReleased(ofMouseEventArgs &mouse){
	
}

void ofxClickDownMenu::keyPressed(ofKeyEventArgs &key){
}

void ofxClickDownMenu::keyReleased(ofKeyEventArgs &key){
	
}

void ofxClickDownMenu::RegisterMenu(string Menu){
	if ((menus.size() > 0)&&(menus[menus.size()-1].message == " X Cancel")){
		menus.pop_back();
	}
	ofxCDMButton bt;
	bt.message = Menu;
	bt.isBranch = false;
	bt.isFader  = false;
	
	menus.push_back(bt);
	
	if (menus[menus.size()-1].message != " X Cancel") RegisterMenu(" X Cancel");
	
	window_size.y = menus.size()*20;
	window_size.x = MAX(bt.message.length()*9,window_size.x);
}

void ofxClickDownMenu::RegisterBranch(string Menu, vector<string> *Menus){
	if ((menus.size() > 0)&&(menus[menus.size()-1].message == " X Cancel")){
		menus.pop_back();
	}
	ofxCDMButton bt;
	bt.message = Menu;
	bt.isBranch = true;
	bt.isFader  = false;

	for (int i = 0;i < Menus->size();i++){
		bt.branchmenu.push_back((*Menus)[i]);
	}
	bt.branchmenu.push_back("<< Back");
	menus.push_back(bt);
	
	if (menus[menus.size()-1].message != " X Cancel") RegisterMenu(" X Cancel");
	
	window_size.y = menus.size()*20;
	window_size.x = MAX(bt.message.length()*9,window_size.x);
}

void ofxClickDownMenu::RegisterFader(string Menu, float *valueP){
	if ((menus.size() > 0)&&(menus[menus.size()-1].message == " X Cancel")){
		menus.pop_back();
	}
	ofxCDMButton bt;
	bt.message = Menu;
	bt.isBranch = false;
	bt.isFader  = true;
	bt.fader_Pointer = valueP;
	
	menus.push_back(bt);
	
	if (menus[menus.size()-1].message != " X Cancel") RegisterMenu(" X Cancel");
	
	window_size.y = menus.size()*20;
	window_size.x = MAX(bt.message.length()*9,window_size.x);

}

void ofxClickDownMenu::UnRegisterMenu(string Menu){
	int cnt = 0;
	while (cnt < menus.size()) {
		if (Menu == menus[cnt].message){
			menus.erase(menus.begin()+cnt);
		}else{
			cnt++;
		}
	}
	window_size.y = menus.size()*20;
	for (int i = 0;i < menus.size();i++){
		window_size.x = MAX(menus[i].message.length()*9,window_size.x);
	}
}

void ofxClickDownMenu::doFunction(){
	if (menus[menu_focused].isBranch){
		// Gen Branch menu
		if (!haveChild){
			child = new ofxClickDownMenu();
			child->menu_name = menu_name + "::" + menus[menu_focused].message;
			for (int i = 0;i < menus[menu_focused].branchmenu.size();i++){
				child->RegisterMenu(menus[menu_focused].branchmenu[i]);
			}
			child->openMenu(window_pos.x+window_size.x, window_pos.y);
			child->isChild = true;
			child->parent = this;
			haveChild = true;		
		}else{
			frame = 0;
			phase = PHASE_SELECT;
		}
	}else if(menus[menu_focused].isFader){
		//Gen Fader
		if (!haveFChild){
			fchild = new ofxClickDownFader(menus[menu_focused].fader_Pointer, window_pos+ofPoint(window_size.x,0));
			fchild->parent = this;
			haveFChild = true;
		}else{
			ofxCDMEvent ev;
			ev.message = menu_name + "::" + menus[menu_focused].message;
			ofNotifyEvent(ofxCDMEvent::MenuPressed,ev);

			frame = 0;
			phase = PHASE_SELECT;
		}
	}else {
		//Gen normal event handler
		frame = 0;
		phase = PHASE_SELECT;
		if (haveChild){
			
		}else{
			if (isChild){
				if (menus[menu_focused].message == "<< Back"){
					
				}else{
					ofxCDMEvent ev;
					ev.message = menu_name + "::" + menus[menu_focused].message;
					ofNotifyEvent(ofxCDMEvent::MenuPressed,ev);
					parent->doFunction();
				}
			}else{
				ofxCDMEvent ev;
				ev.message = menu_name + "::" + menus[menu_focused].message;
				ofNotifyEvent(ofxCDMEvent::MenuPressed,ev);
			}
		}

	}
}

void ofxClickDownMenu::openMenu(int x,int y){
	window_pos = ofPoint(x,y);
	if ((ofGetHeight() - y) < window_size.y) window_pos.y = ofGetHeight() - window_size.y;
	window_y = 0;
	frame = 0;
	menu_focused = -1;
	phase = PHASE_CLICK;		
	ofxCDMEvent ev;
	ev.message = menu_name + "::" + "mouseFix";
	ofNotifyEvent(ofxCDMEvent::MenuPressed,ev);
}