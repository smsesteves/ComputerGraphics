#pragma once

#include "CGF\CGFobject.h"
class Plane
{
public:
	Plane(void);
	Plane(int);
	~Plane(void);
	void draw();
	void draw(int width, int height);
	void drawT(int s, int t);
	void drawCentered();
	void drawHole() ;
	float texCoordX(int b);
	float texCoordZ(int b);
private:
	int _numDivisions; // Number of triangles that constitute rows/columns
};

