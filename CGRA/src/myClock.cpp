#include "myClock.h"


myClock::myClock()
{
	activate=true;
	cilindro = new myCylinder(10,10,true);
	horas=new myClockHand();
	minutos=new myClockHand();
	segundos=new myClockHand();
	horas->setAngle(90);
	minutos->setAngle(180);
	segundos->setAngle(270);
}

void myClock::draw()
{
	glPushMatrix();
	glTranslated(7,7,0);
	glScaled(1,1,0.3);
	glRotated(90,1,0,0);
	cilindro->draw();
	glPopMatrix();


	//Ponteiros

	drawponteiros();
}


void myClock::drawponteiros()
{


		horas->draw(1);
		minutos->draw(2);
		segundos->draw(3);
	
}

void myClock::update(unsigned long timelocal)
{

  time_t rawtime=timelocal/1000;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  float anglesec=((timeinfo->tm_sec)*360)/60;
  float anglehr=(((timeinfo->tm_hour)%12)*360)/12;
  float anglemin=((timeinfo->tm_min)*360)/60;
  if(activate)
  {
		segundos->setAngle(anglesec);
		minutos->setAngle(anglemin);
		horas->setAngle(anglehr);
  }
  drawponteiros();

}