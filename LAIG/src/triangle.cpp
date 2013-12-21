#include "triangle.h"
#include <iostream>

Triangle::Triangle(float x1,float y1,float z1,float x2, float y2,float z2,float x3,float y3,float z3)
{
	this->x1=x1;
	this->x2=x2;
	this->x3=x3;
	this->y1=y1;
	this->y2=y2;
	this->y3=y3;
	this->z1=z1;
	this->z2=z2;
	this->z3=z3;

	float base1 = sqrtf(pow(2.0f, x2 - x1) + pow(2.0f, y2 - y1) + pow(2.0f, z2 - z1));
	float hipot = sqrtf(pow(2.0f, x3 - x1) + pow(2.0f, y3 - y1) + pow(2.0f, z3 - z1));
	float teta = acos((x1 * x2 + y1 * y2 + z1 * z2) / (base1 * hipot));
	float base2 = hipot * cos(teta);
	float height	= sqrt(pow(2.0f, hipot) - pow(2.0f, base2));
	texture3 = base1;
	texture2 = base2;
	texture1 = height;

	newellsNormal();

}


void Triangle::draw()
{
	
    glBegin(GL_TRIANGLES);		
	glNormal3f(n1,n2,n3);
		glTexCoord2f(0, 0);
		glVertex3f(x1,y1,z1);	
		glTexCoord2f(texture3, 0);
		glVertex3f(x2,y2,z2);	
		glTexCoord2f(texture2, texture1);
		glVertex3f(x3,y3, z3);		
    glEnd();					
   			// Move Right
   
}

void Triangle::newellsNormal(){

	float v[3];
	float u[3];



	v[0] = x2 - this->x1;
	v[1] = this->y2 - this->y1;
	v[2] = this->z2 - this->z1;

	u[0] = this->x3 - this->x1;
	u[1] = this->y3 - this->y1;
	u[2] = this->z3 - this->z1;

	n1 = (u[1] * v[2]) - (u[2] * v[1]);
	n2 = (u[2] * v[0]) - (u[0] * v[2]);
	n3 = (u[0] * v[1]) - (u[1] * v[0]);

}