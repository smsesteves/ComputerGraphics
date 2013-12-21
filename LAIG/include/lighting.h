#ifndef LIGHTING_H
#define LIGHTING_H

#include <string>
#include "CGFlight.h"
using namespace std;

struct lightingComp{
		float a;
		float b;
		float c;
		float d;
};

struct locationCoord{
		float x;
		float y;
		float z;
};

class Lighting
{
private:
	bool doublesided;
	bool local;
	//bool enabled;
	lightingComp ambient;
public:
	void setDoublesided(bool doublesided);
	void setLocal(bool local);
	void setLightingAmbient(float a, float b, float c, float d);

	bool getLocal();
	bool getDoublesided();
	lightingComp getLightingAmbient(){return ambient;};
};

class Light: public CGFlight
{
private:
	string idS;
public:
	Light(unsigned int lightid, float* pos, float *dir=NULL):CGFlight(lightid, pos, dir){};
	virtual int lightingType(){return -1;};
	bool getEnabled(){ return enabled;};
	void setIdS(string id){ idS = id; };
	string getIdS(){return idS;};

};

#endif