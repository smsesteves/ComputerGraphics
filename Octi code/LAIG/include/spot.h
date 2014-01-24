#ifndef SPOT_H
#define SPOT_H

#include "lighting.h"

class Spot : public Light{
private:
	int idI;
	//bool sEnabled;
	float angle;
	float exponent;

public:
	Spot(unsigned int lightid, float* pos, float *dir=NULL):Light(lightid, pos, dir){};
	int lightingType(){ return 1; };
	void setIdI(int id);
	//void setSEnabled(bool enabled);
	void setSExponent(float exponent);
	void setSDirection(float* dir);
	void setSAngle(float angle);

	float getSExponent();
	float getSAngle();
	float* getSDirection();
	float getIdI();
};

#endif