#include "gameElements.h"

Pod::Pod(float x, float y){
	this->x = x;
	this->y = y;
}

void Pod::draw(){

	GLUquadricObj *quadric; 
	quadric=gluNewQuadric(); 
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glTranslated(0,0,1);
		gluDisk(quadric,0,0.5 ,8,8); 
	glPopMatrix();

	glPushMatrix();
		glRotated(180,0,1,0);
		gluDisk(quadric,0,0.5,8,8); 
	glPopMatrix();

	gluCylinder(quadric, 0.5,0.5, 1, 8, 10);

}