#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"
using namespace std;

class Plane: public Primitive
{
private:
	int parts;
public:
	Plane(int parts);
	~Plane();
	void draw();
};

#endif