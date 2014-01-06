#ifndef YAF_SCENE_H
#define YAF_SCENE_H

#include "globals.h"
#include "cameras.h"
#include "perspective.h"
#include "ortho.h"
#include "lighting.h"
#include "omni.h"
#include "spot.h"
#include "texture.h"
#include "appearance.h"
#include "node.h"
#include "sphere.h"
#include "torus.h"
#include "vehicle.h"
#include <map>
#include "utils.h"
#include <iostream>
#include "glui.h"
#include "glut.h"
#include "CGFapplication.h"
#include "GL\gl.h"
#include "CGFaxis.h"
#include "animation.h"
#include "plane.h"
#include "patch.h"
#include "waterline.h"
#include "linearAnimation.h"

class YAFScene
{
private:
public:
	map<string,Node*> graph;
	map<Animation*,vector<Node*> > graphanimation;
	int mode;



	map<string,Animation*> animationsComp;
	string rootid;

	Globals globalsComp;
	Lighting* lightConfig;
	vector<Light*> lightsComp;
	vector<Appearance*> appearancesComp;
	vector<Cameras*> camerasComp;
	vector<Texture*> texturesComp;
	
	Node* menuVitoria;
	Node* envolente;
	vector<Node*> redPods;
	vector<Node*> bluePods;
	vector<Node*> tabCells;
	vector<Node*> octiCells;
	vector<Node*> bPickProng;
	vector<Node*> rPickProng;

	int nextTheme;
	void switchTheme();

	map<string,Node*> defaultGraph;

	int itActiveCamera;

	vector<int> lightsState;
			

	//void initGlobals();
	void setLightConfig(Lighting* lightConfig);
	void initLights();
	void initCameras();
	//void initTextures();
	//void initAppearances();
	void initAnimations();
	void createdisplays(string root,vector<Appearance*>appearancesStack);
	void calcmatrix();
	void trans(string node);
	void draw(string node,vector<Appearance*> &appstack);
	void resetvisited();
	void initGlobals();
	void animationsTeste();
	void initposition(string node);
	void initInterfaceAnim(int iterador);

};

#endif