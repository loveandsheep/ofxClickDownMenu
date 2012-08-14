//
//  ofxCDMEvent.h
//  
//
//  Created by Sheep on 12/06/21.
//  Copyright (c) 2012 Sheep. All rights reserved.
//

#pragma once
#include "ofMain.h"

class ofxCDMEvent : public ofEventArgs {
public:
	float args;
	string message;
	
	static ofEvent <ofxCDMEvent> MenuPressed;
};