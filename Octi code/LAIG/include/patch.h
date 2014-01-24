#ifndef PATCH_H
#define PATCH_H


#include "primitive.h"
#include "animation.h"
using namespace std;

class Patch : public Primitive
{
private:
	int order, partsU, partsV;
	string compute;
	vector<ControlPoint> controlPoints;
	GLfloat* ctrlPoints;
	

public:
	Patch(int order, int partsU, int partsV, string compute, vector<ControlPoint> controlPoints);
	
	~Patch();
	GLfloat* setControlPointsGL();
	void draw();
};

#endif