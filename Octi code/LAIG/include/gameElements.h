#ifndef GELEMENTS_H
#define GELEMENTS_H

#include <string>
#include "primitive.h"

using namespace std;

class Pod: public Primitive
{
private:
	float x;
	float y;
public:
	Pod(float x, float y);
	void draw();
	
};

#endif