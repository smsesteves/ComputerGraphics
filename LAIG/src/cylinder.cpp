#include "cylinder.h"

Cylinder::Cylinder(float base,float top,float height,int slices,int stacks)
{
	this->base=base;
	this->top=top;
	this->height=height;
	this->slices=slices;
	this->stacks=stacks;
	
}


void Cylinder::draw()
{
	GLUquadricObj *quadric; 
	quadric=gluNewQuadric(); 
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glTranslated(0,0,height);
		gluDisk(quadric,0,top ,slices,slices); 
	glPopMatrix();

	glPushMatrix();
		glRotated(180,0,1,0);
		gluDisk(quadric,0,base,slices,slices); 
	glPopMatrix();

	gluCylinder(quadric, base, top, height, slices, stacks);
}