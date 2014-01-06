#ifndef SPHERE_H
#define SPHERE_H


#include "primitive.h"
using namespace std;

class Sphere : public Primitive
{
private:
	float radius;
	int slices; 
	int stacks;
public:
	Sphere(float radius,int slices,int stacks);
	void draw();
};

#endif