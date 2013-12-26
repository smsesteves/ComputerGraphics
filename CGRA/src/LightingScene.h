#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "myTable.h"
#include "Plane.h"
#include "myCylinder.h"
#include "mySphere.h"
#include "myClock.h"
#include "myRobot.h"
#include <cmath>
class LightingScene : public CGFscene
{
public:
	void init();
	void display();

	void update(unsigned long);

	void toggleSomething();
	int sceneVar;
	
	void rotateRobot(bool direction);
	void moveRobot(bool front);

	void changeMode();
	void watchPause();
	void watchReset();

	int mode;
	int robottexture;
	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;

	vector<CGFlight*> lights;

	vector<int> lightsState;
	bool setLightState(int n);

	myTable* table;
	Plane* wall; 
	Plane* boardA;	
	myClock* relogio;
	myRobot* robot;

	Plane* boardB;
	myCylinder* cilindro;
	myCylinder* cilindro2;
	mySphere* semiEsfera;

	CGFappearance* materialA;
	CGFappearance* materialB;
	CGFappearance* materialC;
	CGFappearance* materialD;

	CGFappearance* tableAppearance;
	CGFappearance* slidesAppearance;
	CGFappearance* boardAppearance;
	CGFappearance* windowAppearance;
	CGFappearance* landscapeAppearance;
	CGFappearance* floorAppearance;
	CGFappearance* relogioAppearance;
	CGFappearance* robotAppearance;

	~LightingScene();
};

#endif