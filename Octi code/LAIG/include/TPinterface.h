#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "CGFapplication.h"
#include "XMLScene.h"
#include "socket.h"
#include <algorithm>

class TPinterface: public CGFinterface {
	public:
		TPinterface(Game* game, CGFapplication* app);

		Game* octi;
		CGFapplication* application;

		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);

		// Picking
		virtual void processMouse(int button, int state, int x, int y);	
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]); 
		void clickHandler(GLuint* selected, GLint nselected);
		virtual void processKeyboard(unsigned char key, int x, int y);
		virtual void processPassiveMouseMoved (int x, int y);

		int testVar;
};


#endif