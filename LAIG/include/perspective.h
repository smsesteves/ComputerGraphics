#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "cameras.h"
#include <iostream>

class Perspective : public Cameras{
private:
	float angle;
	//float target[3];
public:
	int cameraType(){ return 0; };
	void applyView();
	void updateProjectionMatrix(int width, int height);
	void setCAngle(float angle);
	void setCTarget(float t1, float t2, float t3);
	void update(int turn);
	bool toanimate;
};

#endif