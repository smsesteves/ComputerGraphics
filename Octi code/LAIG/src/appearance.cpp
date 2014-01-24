#include "appearance.h"

void Appearance::setIdS(string newId){
	idS = newId;
}
void Appearance::setEmissive(float* newEmissive){
	this->emissive[0] = newEmissive[0];
	this->emissive[1] = newEmissive[1];
	this->emissive[2] = newEmissive[2];
	this->emissive[3] = newEmissive[3];
}

void Appearance::setTextureReference(string newTextRef){
	textureReference = newTextRef;
}
