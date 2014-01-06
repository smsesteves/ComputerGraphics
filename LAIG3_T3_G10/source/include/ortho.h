#ifndef ORTHO_H
#define ORTHO_H

#include "cameras.h"

class Ortho : public Cameras{
private:
	float left;
	float right;
	float top;
	float bottom;
public:
	int cameraType(){ return 1; };
	
	void applyView();
	void setCFloatValues(float left, float right, float top, float bottom);
	void updateProjectionMatrix(int width, int height);
};

#endif