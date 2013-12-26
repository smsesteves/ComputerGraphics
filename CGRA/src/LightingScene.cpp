#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "myTable.h"
#include "Plane.h"
#include "myCylinder.h"
#include "mySphere.h"
#include "TPinterface.h"

#include <iostream>


#include <math.h>

#define GL_CLAMP_TO_EDGE 0x812F

float pi = acos(-1.0);
float deg2rad=pi/180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

// Positions for two lights
float light0_pos[4] = {4, 6.0, 1.0, 1.0};
float light1_pos[4] = {10.5, 6.0, 1.0, 1.0};

float light2_pos[4] = {10.5, 6.0, 5.0, 1.0};
float light3_pos[4] = {4, 6.0, 5.0, 1.0};

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4]= {0,0,0,1.0};
//float globalAmbientLight[4]= {0.2,0.2,0.2,1.0};

// number of divisions
#define BOARD_A_DIVISIONS 30
#define BOARD_B_DIVISIONS 100

// Coefficients for material A
float ambA[3] = {0.2, 0.2, 0.2};
float difA[3] = {0.6, 0.6, 0.6};
float specA[3] = {0.2, 0.2, 0.2};
//float specA[3] = {0, 0.8, 0.8};
float shininessA = 120.f;

// Coefficients for material B
float ambB[3] = {0.2, 0.2, 0.2};
float difB[3] = {0.6, 0.6, 0.6};
float specB[3] = {0.8, 0.8, 0.8};
float shininessB = 120.f;

// Coefficients for material C madeira
float ambC[3] = {0.72, 0.52, 0.04};
float difC[3] = {0.72, 0.52, 0.04};
float specC[3] = {0.72, 0.52, 0.04};
float shininessC = 120.f;


// Coefficients for material D metalico
float ambD[3] = {0.2, 0.2, 0.2};
float difD[3] = {0.6, 0.6, 0.6};
float specD[3] = {0.8, 0.8, 0.8};
float shininessD = 120.f;

// Coefficients for BOARD

float ambBoard[3] = {0, 0, 0};
float difBoard[3] = {0.4, 0.4, 0.4};
float specBoard[3] = {0.2, 0.2, 0.2};
float shininessBoard = 0.9;

// Coefficients for TABLE

float ambTable[3] = {0.1, 0.1, 0.1};
float difTable[3] = {0.9, 0.9, 0.9};
float specTable[3] = {0.2, 0.2, 0.2};
float shininessTable = 0;

// Coefficients for SLIDES

float ambSlides[3] = {0.1, 0.1, 0.1};
float difSlides[3] = {0.9, 0.9, 0.9};
float specSlides[3] = {0.2, 0.2, 0.2};
float shininessSlides = 0.2;

float ambientNull[4]={0,0,0,1};
float yellow[4]={1,1,0,1};

void LightingScene::init() 
{

	mode=1;
	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);  
	
	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);  
	
	// Declares and enables two lights, with null ambient component

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(ambientNull);
	//light0->setSpecular(yellow);

	lightsState.clear();
	lights.clear();

	lights.push_back(light0);
	lightsState.push_back(1);
	light0->disable();
	light0->enable();

	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambientNull);
	
	lights.push_back(light1);
	lightsState.push_back(1);
	light1->disable();
	light1->enable();

	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->setAmbient(ambientNull);
	light2->setKc(0);
	light2->setKl(1);
	light2->setKq(0);
	
	lights.push_back(light2);
	lightsState.push_back(1);
	light2->disable();
	light2->enable();

	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->setAmbient(ambientNull);
	//light3->setSpecular(yellow);
	light3->setKc(0);
	light3->setKl(0);
	light3->setKq(1);

	lights.push_back(light3);
	lightsState.push_back(1);
	light3->disable();
	light3->enable();
	
	// Uncomment below to enable normalization of lighting normal vectors
	glEnable (GL_NORMALIZE);
		
	//Declares scene elements
	table = new myTable();
	wall = new Plane();
	boardA = new Plane(BOARD_A_DIVISIONS);
	boardB = new Plane(BOARD_B_DIVISIONS);
	cilindro = new myCylinder(10, 5, false);
	cilindro2 = new myCylinder(10, 5, true);
	semiEsfera = new mySphere(100, 10);
	relogio=new myClock();
	robot = new myRobot();
	robot->setRotation(200);
	robot->setX(7);
	robot->setY(0);
	robot->setZ(7);
	
	//Declares materials
	materialA = new CGFappearance(ambA,difA,specA,shininessA);
	materialB = new CGFappearance(ambB,difB,specB,shininessB);
	materialC = new CGFappearance(ambC,difC,specC,shininessC);
	materialD = new CGFappearance(ambD,difD,specD,shininessD);

	
	
	tableAppearance = new CGFappearance(ambTable, difTable, specTable, shininessTable);
	tableAppearance->setTexture("../textures/table.png");
	
	boardAppearance = new CGFappearance(ambBoard, difBoard, specBoard, shininessBoard);
	boardAppearance->setTexture("../textures/board.png");

	slidesAppearance = new CGFappearance(ambSlides, difSlides, specSlides, shininessSlides);
	slidesAppearance->setTexture("../textures/slides.png");

	windowAppearance = new CGFappearance(ambSlides, difSlides, specSlides, shininessSlides);
	windowAppearance->setTexture("../textures/window.png");
	
	landscapeAppearance = new CGFappearance(ambSlides, difSlides, specSlides, shininessSlides);
	landscapeAppearance->setTexture("../textures/landscape.jpg");

	floorAppearance = new CGFappearance(ambTable, difTable, specTable, shininessTable);
	floorAppearance->setTexture("../textures/floor.png");

	relogioAppearance = new CGFappearance(ambBoard, difBoard, specBoard, shininessBoard);
	relogioAppearance->setTexture("../textures/clock.png");

	robotAppearance = new CGFappearance(ambSlides, difSlides, specSlides, shininessSlides);
	robotAppearance->setTexture("../textures/robot1.jpg");

	// Flat Shading
	//glShadeModel(GL_FLAT);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	setUpdatePeriod(100);

	sceneVar = 0;
	
}

void LightingScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	light0->draw();
	light1->draw();
	light2->draw();
	light3->draw();
	
	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section

	//First Table
	glPushMatrix();
		glTranslated(5,0,8);
		table->draw(tableAppearance, materialA);
	glPopMatrix();





	//Second Table
	//glPushMatrix();
	//	glTranslated(12,0,8);
	//	table->draw(tableAppearance, materialA);
	//glPopMatrix();


	



	// Cilindro
	glPushMatrix();
		glTranslated(5,0,12);
		glScaled(1,5,1);
		materialA->apply();
		cilindro->draw();
	glPopMatrix();	

	// Cilindro 2
	//glPushMatrix();
	//	glTranslated(10,0,12);
	//	glScaled(1,5,1);
	//	materialA->apply();
	//	cilindro2->draw();
	//glPopMatrix();	

	//Floor
	glPushMatrix();
		glTranslated(7.5,0,7.5);
		glScaled(15,0.2,15);
		floorAppearance->apply();
		//materialA->apply();
		wall->drawT(10,12);
	glPopMatrix();

	//LeftWall
	glPushMatrix();		
		glTranslated(0,4,7.5);
		glRotated(-90.0,0,0,1);
		glRotated(90.0,0,1,0);		
		glScaled(15,0.2,8);
		windowAppearance->setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		windowAppearance->apply();
		wall->drawHole();
		//wall->drawCentered();
	glPopMatrix();

	//Landscape
	glPushMatrix();		
		glTranslated(-5,6,7.5);
		glRotated(-90.0,0,0,1);
		glRotated(90.0,0,1,0);		
		glScaled(33,0.2,25);
		//landscapeAppearance->setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		landscapeAppearance->apply();
		//wall->drawHole();
		wall->draw();
	glPopMatrix();

	//PlaneWall
	glPushMatrix();
		glTranslated(7.5,4,0);
		glRotated(90.0,1,0,0);
		glScaled(15,0.2,8);		
		materialA->apply();
		wall->draw();
	glPopMatrix();

	// Board A
	glPushMatrix();
		glTranslated(4,4,0.2);
		glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
		glRotated(90.0,1,0,0);
		slidesAppearance->apply();
		boardA->draw();
	glPopMatrix();
	
	// Board B
	glPushMatrix();
		glTranslated(10.5,4,0.2);
		glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
		glRotated(90.0,1,0,0);
		boardAppearance->setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		boardAppearance->apply();
		boardB->draw(512,372);
	glPopMatrix();

	// Relogio
	glPushMatrix();	
		relogioAppearance->apply();
		relogio->draw();
		materialB->apply();	
	glPopMatrix();

	// Robot

	if (robottexture == 1)
		robotAppearance->setTexture("../textures/robot1.jpg");
	else if(robottexture == 2)
		robotAppearance->setTexture("../textures/floor.png");
	else if(robottexture==3)
		robotAppearance->setTexture("../textures/landscape.jpg");

	glPushMatrix();
		
		robotAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);
		robotAppearance->apply();	
		robot->draw(mode);	
	glPopMatrix();


	


	// ---- END Primitive drawing section
	

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}


void LightingScene::update(unsigned long timelocal)
{
	relogio->update(timelocal);
}


LightingScene::~LightingScene() 
{
	delete(light0);
	delete(light1);

	delete(table);
	delete(wall);
	delete(boardA);
	delete(boardB);
	delete(materialA);
	delete(materialB);
	delete(materialC);
	delete(materialD);
	delete(tableAppearance);
	delete(boardAppearance);
	delete(slidesAppearance);
	delete(windowAppearance);
}

void LightingScene::toggleSomething() {
	
}

void LightingScene::rotateRobot(bool direction) {
	if(direction) 
		robot->incrementRotation(3);
	else 
		robot->incrementRotation(-3);

	glPushMatrix();
		
		robot->draw(mode);
	glPopMatrix();
}

void LightingScene::moveRobot(bool front) {
	if(front) {
		robot->setX(robot->getX()+sin(robot->getRotation()*pi/180.0));
		robot->setZ(robot->getZ()+cos(robot->getRotation()*pi/180.0));
	} else {
		robot->setX(robot->getX()-sin(robot->getRotation()*pi/180.0));
		robot->setZ(robot->getZ()-cos(robot->getRotation()*pi/180.0));
	}

	glPushMatrix();		
		robot->draw(mode);
	glPopMatrix();
}

bool LightingScene::setLightState(int n) {

	if(n >= lightsState.size() || n >= lights.size())
		return false;

	if(lightsState[n] == 1) {
		lights[n]->enable();
	} else {
		lights[n]->disable();
	}	
}



void LightingScene::watchPause()
{
	relogio->setActivate(false);
}

void LightingScene::watchReset()
{
	relogio->setActivate(true);
}

