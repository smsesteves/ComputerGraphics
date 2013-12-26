#include "myFloor.h"

void myFloor::draw() 
{
	myUnitCube cube;

	glPushMatrix();
	glTranslated(0,-0.05,0);
	glScalef(8,0.1,6);
	cube.draw();
	glPopMatrix();

}
	
