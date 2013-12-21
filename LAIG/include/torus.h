#ifndef TORUS_H
#define TORUS_H


#include "primitive.h"
using namespace std;

class Torus : public Primitive
{
private:
	float inner;
	float outer; 
	int slices;
	int loops;
public:
	Torus(float inner,float outer,int slices,int loops);
	void draw();
};

#endif