#ifndef CAMERAS_H
#define CAMERAS_H

#include <string>
#include "CGFcamera.h"
#include "glut.h"
#include "glui.h"
using namespace std;

class Cameras: public CGFcamera
{
protected:
	bool initial;
	string id;
	float near;
	float far;
public:
	virtual int cameraType(){return -1;};
	virtual void applyView(){};
	virtual void updateProjectionMatrix(int width, int height){};
	void setCInitial(bool initial);
	void setCPrimary(string id, float near, float far);
	string getid();
	void setInitial(bool newcenas){initial=newcenas;};
	bool getInitial(){return initial;};
};

#endif