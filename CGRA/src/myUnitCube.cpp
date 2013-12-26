#include "myUnitCube.h"

void myUnitCube::draw()
{
	glPushMatrix();
	glNormal3f(0,0,1);

	glTranslated(-0.5,-0.5,0);

	//LADO ESQUERDO

	glPushMatrix();

	glTranslated(0,0,0.5);

	glBegin(GL_QUADS);
	glVertex3d(0,0,0);
	glVertex3d(1,0,0);
	glVertex3d(1,1,0);
	glVertex3d(0,1,0);
	glEnd();

	glPopMatrix();
	
	//BOTTON
	glPushMatrix();

	glTranslated(0,0,0.5);
	glTranslated(0,0,-1);
	glRotated(-90,1,0,0);
	glRotated(180,1,0,0);

	glBegin(GL_QUADS);
		glTexCoord2d(0,0);		
		glVertex3d(0,0,0);
		glTexCoord2d(1,0);
		glVertex3d(1,0,0);
		glTexCoord2d(1,1);
		glVertex3d(1,1,0);
		glTexCoord2d(0,1);
		glVertex3d(0,1,0);
	glEnd();

	glPopMatrix();

	//LADO DIREITO

	glPushMatrix();

	glTranslated(0,1,-0.5);
	glRotated(180,1,0,0);

	glBegin(GL_QUADS);
		glTexCoord2d(0,0);		
		glVertex3d(0,0,0);
		glTexCoord2d(1,0);
		glVertex3d(1,0,0);
		glTexCoord2d(1,1);
		glVertex3d(1,1,0);
		glTexCoord2d(0,1);
		glVertex3d(0,1,0);
	glEnd();

	glPopMatrix();
	
	//LADO CIMA

	glPushMatrix();

	
	glTranslated(0,1,0);
	glTranslated(0,0,-0.5);
	glTranslated(0,0,1);
	glRotated(-90,1,0,0);

	glBegin(GL_QUADS);
		glTexCoord2d(0,0);		
		glVertex3d(0,0,0);
		glTexCoord2d(1,0);
		glVertex3d(1,0,0);
		glTexCoord2d(1,1);
		glVertex3d(1,1,0);
		glTexCoord2d(0,1);
		glVertex3d(0,1,0);
	glEnd();

	glPopMatrix();

	//LADO FRENTE

	glPushMatrix();
	
	glTranslated(1,0,0);
	glTranslated(0,0,0.5);
	glRotated(90,0,1,0);	

	glBegin(GL_QUADS);
		glTexCoord2d(0,0);		
		glVertex3d(0,0,0);
		glTexCoord2d(1,0);
		glVertex3d(1,0,0);
		glTexCoord2d(1,1);
		glVertex3d(1,1,0);
		glTexCoord2d(0,1);
		glVertex3d(0,1,0);
	glEnd();

	glPopMatrix();

	//LADO Tras

	glPushMatrix();
	
	//glTranslated(1,0,0);
	glTranslated(0,0,-0.5);
	glRotated(-90,0,1,0);

	glBegin(GL_QUADS);
		glTexCoord2d(0,0);		
		glVertex3d(0,0,0);
		glTexCoord2d(1,0);
		glVertex3d(1,0,0);
		glTexCoord2d(1,1);
		glVertex3d(1,1,0);
		glTexCoord2d(0,1);
		glVertex3d(0,1,0);
	glEnd();

	glPopMatrix();

	glPopMatrix();
}