#include "sphere.h"
// HAAAANDS
Sphere::Sphere(float radius,int slices,int stacks)
{
		this->radius=radius;
		this->slices=slices;
		this->stacks=stacks;
};

void Sphere::draw(){
		
		GLUquadric *quadric; 
		quadric=gluNewQuadric(); 
		gluQuadricNormals(quadric, GLU_SMOOTH); 
		gluQuadricTexture(quadric, GL_TRUE); 
		glEnable(GL_TEXTURE_2D);
		gluSphere(quadric,radius,slices,stacks);
};