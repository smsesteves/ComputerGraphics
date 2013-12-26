
#include "myTable.h"

void myTable::draw(CGFappearance* tampoT, CGFappearance* pernasT)
{
	


	glPushMatrix();
	myChair cadeira;
	cadeira.draw();
	glPopMatrix();




	

	//TAMPO
	myUnitCube tampo;
	
	glPushMatrix();
	glTranslated(0,3.7,0);
	glScaled(5,0.3,3);
	tampoT->apply();
	tampo.draw();
	glPopMatrix();	

	// PERNAS
	
	glPushMatrix();
	pernasT->apply();
	
	//1 PERNA

	myLeg perna1;
	glTranslated(-2.5,0,-1.5);
	perna1.draw();

	//2 PERNA


	myLeg perna2;
	glTranslated(4.7,0,0);
	perna2.draw();
		  
	//3 PERNA

	myLeg perna3;
	glTranslated(0,0,2.7);
	perna3.draw();

	//4 PERNA

	myLeg perna4;
	glTranslated(-4.7,0,0);
	perna4.draw();

	glPopMatrix();
}