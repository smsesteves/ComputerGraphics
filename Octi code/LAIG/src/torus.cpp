#include "torus.h"

Torus::Torus(float inner,float outer,int slices,int loops)
{
	this->inner=inner;
	this->outer=outer;
	this->slices=slices;
	this->loops=loops;
}


void Torus::draw()
{
	glutSolidTorus(inner,outer,slices,loops);
}