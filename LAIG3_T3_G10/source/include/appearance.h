#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <string>
#include "CGFappearance.h"
using namespace std;

class Appearance: public CGFappearance
{
private:
	string idS;	
	float emissive[4];
	string textureReference;
public:
	void setIdS(string newID);
	void setEmissive(float* newEmissive);
	void setTextureReference(string newTextRef);
	string getIdS(){ return idS;};

};

#endif