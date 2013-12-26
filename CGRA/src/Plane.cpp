#include "Plane.h"
#include "myUnitCube.h"
#include <GL/GLU.h>


Plane::Plane(void)
{
	_numDivisions = 1;
}

Plane::Plane(int n)
{
	_numDivisions = n;
}


Plane::~Plane(void)
{
}

void Plane::draw()
{
	glPushMatrix();
		glRotatef(180.0,1,0,0);
		glTranslatef(-0.5,0.0,-0.5);
		glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
		glNormal3f(0,-1,0);

		for (float bx = 0; bx<_numDivisions; bx++)
		{
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(bx/_numDivisions,0);
				glVertex3f(bx, 0, 0);
				for (float bz = 0; bz<_numDivisions; bz++)
				{
					glTexCoord2f((bx+1)/_numDivisions,bz/_numDivisions);
					glVertex3f(bx + 1, 0, bz);
					glTexCoord2f((bx)/_numDivisions,(bz+1)/_numDivisions);
					glVertex3f(bx, 0, bz + 1);
				}
				glTexCoord2f((bx+1)/_numDivisions,1);
				glVertex3d(bx+ 1, 0, _numDivisions);

			glEnd();
		}
	glPopMatrix();

}

void Plane::draw(int width, int height)
{
	double ratio = (double)width/height;

	glPushMatrix();
		glRotatef(180.0,1,0,0);
		glTranslatef(-0.5,0.0,-0.5);
		glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
		glNormal3f(0,-1,0);

		for (float bx = 0; bx<_numDivisions; bx++)
		{
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f((bx/_numDivisions)*ratio,0);
				glVertex3f(bx, 0, 0);
				for (float bz = 0; bz<_numDivisions; bz++)
				{
					glTexCoord2f((bx+1)*ratio/_numDivisions,bz*ratio/_numDivisions);
					glVertex3f(bx + 1, 0, bz);
					glTexCoord2f((bx)*ratio/_numDivisions,(bz+1)*ratio/_numDivisions);
					glVertex3f(bx, 0, bz + 1);
				}
				glTexCoord2f((bx+1)*ratio/_numDivisions,1*ratio);
				glVertex3d(bx+ 1, 0, _numDivisions);

			glEnd();
		}
	glPopMatrix();

}

void Plane::drawT(int s, int t)
{

	glPushMatrix();
		glRotatef(180.0,1,0,0);
		glTranslatef(-0.5,0.0,-0.5);
		glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
		glNormal3f(0,-1,0);

		for (float bx = 0; bx<_numDivisions; bx++)
		{
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f((bx/_numDivisions)*s,0);
				glVertex3f(bx, 0, 0);
				for (float bz = 0; bz<_numDivisions; bz++)
				{
					glTexCoord2f((bx+1)*s/_numDivisions,bz*t/_numDivisions);
					glVertex3f(bx + 1, 0, bz);
					glTexCoord2f((bx)*s/_numDivisions,(bz+1)*t/_numDivisions);
					glVertex3f(bx, 0, bz + 1);
				}
				glTexCoord2f((bx+1)*s/_numDivisions,1*t);
				glVertex3d(bx+ 1, 0, _numDivisions);

			glEnd();
		}
	glPopMatrix();

}

void Plane::drawCentered()
{
	glPushMatrix();
		glRotatef(180.0,1,0,0);
		glTranslatef(-0.5,0.0,-0.5);
		glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
		glNormal3f(0,-1,0);

		for (float bx = 0; bx<_numDivisions; bx++)
		{
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(((bx/_numDivisions)*3)-1,-1);
				glVertex3f(bx, 0, 0);
				for (float bz = 0; bz<_numDivisions; bz++)
				{
					glTexCoord2f(((bx+1)*3/_numDivisions) -1,(bz*3/_numDivisions) -1);
					glVertex3f(bx + 1, 0, bz);
					glTexCoord2f(((bx)*3/_numDivisions) -1,((bz+1)*3/_numDivisions) -1);
					glVertex3f(bx, 0, bz + 1);
				}
				glTexCoord2f(((bx+1)*3/_numDivisions) -1,2);
				glVertex3d(bx+ 1, 0, _numDivisions);

			glEnd();
		}
	glPopMatrix();

}

void Plane::drawHole() 
{
	_numDivisions = 3;

	glPushMatrix();
	glRotatef(180.0,1,0,0);
	glTranslatef(-0.5,0.0,-0.5);
	glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
	glNormal3f(0,-1,0);

	for (int bx = 0; bx<_numDivisions; bx++)
	{
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(texCoordX(bx),-1);
			glVertex3f(bx, 0, 0);
			for (float bz = 0; bz<_numDivisions; bz++)
			{
				
				glTexCoord2f(texCoordX(bx+1),texCoordZ(bz));
				glVertex3f(bx + 1, 0, bz);
				if(bx == 1 && bz == 1) {
					glEnd();
					glBegin(GL_TRIANGLE_STRIP);
				}
				glTexCoord2f(texCoordX(bx),texCoordZ(bz+1));
				glVertex3f(bx, 0, bz + 1);
			}
			glTexCoord2f(texCoordX(bx+1),2);
			glVertex3d(bx+ 1, 0, _numDivisions);

		glEnd();
	}
	glPopMatrix();
}

float Plane::texCoordX(int b) {
	switch (b)
	{
	case 0:	return -1;
	case 1: return 0.03;
	case 2: return 0.97;
	case 3: return 2;
	}
}

float Plane::texCoordZ(int b) {
	switch (b)
	{
	case 0:	return -1;
	case 1: return 0.05;
	case 2: return 0.95;
	case 3: return 2;
	}
}