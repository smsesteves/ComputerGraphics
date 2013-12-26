#include "myChair.h"

void myChair::draw()
{

	//PERNA
	
	glPushMatrix();
	myUnitCube perna1;
	//glTranslated(0,0.1,0,);
	//glTranslated(0.15,1.75,0.15);
	glTranslated(0.75,0,0);
	glTranslated(0,1.75,-2.5);
	//glScaled(1,0.5,1);
	glScaled(0.3,3.5,0.3);
	perna1.draw();
	
	glPopMatrix();



	glPushMatrix();
	myUnitCube perna2;
	//glTranslated(0,0.1,0,);
	//glTranslated(0.15,1.75,0.15);
	glTranslated(-0.75,0,0);
	glTranslated(0,1.75,-2.5);
	//glScaled(1,0.5,1);
	glScaled(0.3,3.5,0.3);
	perna2.draw();
	
	glPopMatrix();

	glPushMatrix();
	myUnitCube perna3;
	//glTranslated(0,0.1,0,);
	//glTranslated(0.15,1.75,0.15);
	glTranslated(0,0,1.5);
	glTranslated(-0.75,0,0);
	glTranslated(0,1.75,-2.5);
	//glScaled(1,0.5,1);
	glTranslated(0,-1.75/2,0);
	glScaled(0.3,1.75,0.3);
	perna2.draw();
	
	glPopMatrix();

	glPushMatrix();
	myUnitCube perna4;
	//glTranslated(0,0.1,0,);
	//glTranslated(0.15,1.75,0.15);
	glTranslated(0,0,1.5);

	glTranslated(+0.75,0,0);
	glTranslated(0,1.75,-2.5);
	//glScaled(1,0.5,1);
	glTranslated(0,-1.75/2,0);
	glScaled(0.3,1.75,0.3);

	perna2.draw();
	
	glPopMatrix();



	myUnitCube tampo;
	glPushMatrix();
	glTranslated(0,0,-1.75);
	glTranslated(0,-1.75,0);
	glTranslated(0,3.6,0);
	glScaled(1.7,0.3,1.7);
	tampo.draw();
	glPopMatrix();	


	myUnitCube tampo2;
	glPushMatrix();
	

	glTranslated(0,3,-2.25);
	glRotated(90,1,0,0);

	//glTranslated(0,3.6,0);
	glScaled(1.7,0.3,1);
	
	tampo2.draw();
	glPopMatrix();	


}