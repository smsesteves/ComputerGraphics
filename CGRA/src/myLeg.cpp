#include "myLeg.h"

void myLeg::draw()
{

	//PERNA
	
	glPushMatrix();
	myUnitCube perna1;
	glTranslated(0,0.1,0);
	//glTranslated(1.5,0,1.5);
	glTranslated(0.15,1.75,0.15);
	glScaled(0.3,3.5,0.3);
	perna1.draw();
	
	glPopMatrix();
}