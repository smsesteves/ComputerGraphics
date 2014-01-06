#include "displaylist.h"

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

DisplayList::DisplayList()
{
}

void DisplayList::draw()
{
	if (usingDL)
		glCallList(dl);
	else
		generateGeometry();
}


DisplayList::~DisplayList(void)
{
	glDeleteLists(dl, 1);
}




void DisplayList::generateGeometry()
{
}
