#ifndef CYLINDER_H
#define CYLINDER_H


#include "primitive.h"

using namespace std;

class Cylinder : public Primitive
{
private:
	float base;
	float top;
	float height;
	int slices,stacks;
public:
	Cylinder(float base,float top,float height,int slices,int stacks);
	void draw();
	void move();
	Animation* ani;
};

#endif