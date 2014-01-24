#ifndef RECTANGLE_H
#define RECTANGLE_H


#include "primitive.h"
using namespace std;

class Rectangle : public Primitive
{
private:
	float x1,x2;
	float y1,y2;
public:
	Rectangle(float x1,float y1,float x2, float y2);
	void draw();
};

#endif