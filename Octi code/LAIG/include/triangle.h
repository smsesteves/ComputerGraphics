#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "primitive.h"
using namespace std;

class Triangle : public Primitive
{
private:
	float x1,y1,z1;
	float x2,y2,z2;
	float x3,y3,z3;
	float n1,n2,n3;
	float texture3,texture2,texture1;
public:
	Triangle(float x1,float y1,float z1,float x2, float y2,float z2,float x3,float y3,float z3);
	void draw();
	void newellsNormal();
};

#endif