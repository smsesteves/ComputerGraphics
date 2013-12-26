#include "mySphere.h"
#include "cmath"

mySphere::mySphere(int slices, int stacks) {

	this->angle = 2*acos(-1.0)/slices;
	this->slices = slices;
	this->stacks = stacks;
	this->height = 1;
	this->stackHeight = (height/stacks);

}

void mySphere::draw()
{
	// Base
	glBegin(GL_POLYGON);
		for(int i = 0; i < slices; i++)
			glVertex3d(cos(angle*i),0, sin(angle*i));		
	glEnd();

	// Superficie Concava

	double jBefore = 0, sideBefore = cos(asin(0));

	for(double j = stackHeight; j <= height; j += stackHeight) {

		double side = cos(asin(j));

		for(int i = 1; i <= slices; i++) {		
			glBegin(GL_QUADS);

				glVertex3d(side*cos(angle*i),			j,			side*sin(angle*i));
				glVertex3d(side*cos(angle*(i+1)),		j,			side*sin(angle*(i+1)));
				glVertex3d(sideBefore*cos(angle*(i+1)),	jBefore,	sideBefore*sin(angle*(i+1)));	
				glVertex3d(sideBefore*cos(angle*i),		jBefore,	sideBefore*sin(angle*i));
				
			glEnd();
		}

		jBefore = j;
		sideBefore = side;
	}


}