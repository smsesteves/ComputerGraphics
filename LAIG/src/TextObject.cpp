#include "TextObject.h"
#include <GL/glut.h>

void TextObject::draw()
{
	// Texto 3D, GLUT
	// void glutStrokeCharacter(void *font, int character);	// GLUT_STROKE_ROMAN
	// int glutStrokeWidth(GLUTstrokeFont font, int character);

	// desativa cálculo de iluminação para usar cores diretamente
	glDisable(GL_LIGHTING);

	glPushMatrix();
	if(this->text.size()!=1)
	{
		glTranslated(1,0,0);
	}
	glTranslated(1,3.8,7.4);
	glScalef(0.5, 0.5, 0.5);
	glScalef(0.025, 0.025, 0.025);
	glRotated(180,0,1,0);

	glColor3f(1.0,1.0,1.0);		// azul

	if(this->text.size()==1)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[0]);
	else
	{

		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, '.');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, '.');
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);

}