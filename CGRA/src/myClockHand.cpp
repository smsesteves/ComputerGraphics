#include "myClockHand.h"

myClockHand::myClockHand()
{
	ponteiro = new myUnitCube();
	angle=0;
}

void myClockHand::setAngle(float angle2)
{
	this->angle=-angle2;
}

void myClockHand::draw(int type)
{
	if(type==1)
	{
		glPushMatrix();
		glTranslated(7,7,0);
		glRotated(angle,0,0,1);
		glScaled(0.1,1,1);
		glScaled(0.5,0.5,0.5);
		glTranslated(0.5,0.5,0.5);
		//glTranslated(0,0.5,0);
		//glScaled(1,3,1);
		//glScaled(0.05,0.2,0.7);
		//glTranslated(0,0.5,0.5);
		ponteiro->draw();
		glPopMatrix();
	}
	if(type==2)
	{
		glPushMatrix();
		glTranslated(7,7,0);
		glRotated(angle,0,0,1);

		glScaled(0.8,1.3,1);


		glScaled(0.1,1,1);
		glScaled(0.5,0.5,0.5);
		glTranslated(0.5,0.5,0.5);
		//glTranslated(0,0.5,0);
		//glScaled(1,3,1);
		//glScaled(0.05,0.2,0.7);
		//glTranslated(0,0.5,0.5);
		ponteiro->draw();
		glPopMatrix();
	}

	if(type==3)
	{
		glPushMatrix();
		glTranslated(7,7,0);
		glRotated(angle,0,0,1);

		glScaled(0.7,1.4,1);


		glScaled(0.1,1,1);
		glScaled(0.5,0.5,0.5);
		glTranslated(0.5,0.5,0.5);
		//glTranslated(0,0.5,0);
		//glScaled(1,3,1);
		//glScaled(0.05,0.2,0.7);
		//glTranslated(0,0.5,0.5);
		ponteiro->draw();
		glPopMatrix();
	}



}