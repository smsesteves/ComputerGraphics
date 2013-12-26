#include "myCylinder.h"
#include "cmath"

myCylinder::myCylinder(int slices, int stacks, bool smooth) {

	this->angle = 2*acos(-1.0)/slices;
	this->slices = slices;
	this->stacks = stacks;
	this->height = 1;
	this->smooth = smooth;

	//std::cout << angle << std::endl;
	//for(int i = 0; i < slices; i++) {
	//	std::cout << angle*i << ": " << cos(angle*i) << " // " << sin(angle*i) << std::endl;
	//}
}

void myCylinder::draw() {
	// Base
	
	glBegin(GL_POLYGON);
		glNormal3d(0,-1,0);
		for(int i = 0; i < slices; i++)
		{
			
			glVertex3d(cos(angle*i),0, sin(angle*i));
		}
	glEnd();

	// Topo
	
	glBegin(GL_POLYGON);
		glNormal3d(0,1,0);
		for(int i = slices; i > 0; i--)
		{
			glTexCoord2d((cos(angle*i)/2)-0.5,( sin(angle*i)/2)-0.5);
			glVertex3d(cos(angle*i),height, sin(angle*i));	
		}
	glEnd();

	// Lados
	for(double j = (height/stacks); j <= height; j = j+(height/stacks))
		for(int i = 0; i < slices; i++) {
			glBegin(GL_QUADS);
				if(!this->smooth)
					glNormal3d(cos(angle*(i+0.5)),0,sin(angle*(i+0.5)));
				else
					glNormal3d(cos(angle*(i)),0,sin(angle*(i)));
				glVertex3d(cos(angle*i),j, sin(angle*i));

				if(this->smooth)
					glNormal3d(cos(angle*(i+1)),0,sin(angle*(i+1)));
				glVertex3d(cos(angle*(i+1)),j, sin(angle*(i+1)));
				glVertex3d(cos(angle*(i+1)),j-(height/stacks), sin(angle*(i+1)));	

				if(this->smooth)
					glNormal3d(cos(angle*(i)),0,sin(angle*(i)));
				glVertex3d(cos(angle*i),j-(height/stacks), sin(angle*i));		
			glEnd();
		}
	
}
