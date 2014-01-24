#ifndef OMNI_H
#define OMNI_H

#include "lighting.h"

class Omni : public Light{
private:
	int idI;
	//bool oEnabled;
public:
	Omni(unsigned int lightid, float* pos, float *dir=NULL):Light(lightid, pos, dir){};
	int lightingType(){ return 0; };
	
	void setAngle(float angle){ this->angle = angle;};
	void setIdI(int id);
};

#endif