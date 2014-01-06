#include "lighting.h"

void Lighting::setDoublesided(bool doublesided){
	this->doublesided = doublesided;
}

bool Lighting::getDoublesided(){
	return doublesided;
}

void Lighting::setLocal(bool local){
	this->local = local;
}

bool Lighting::getLocal(){
	return local;
}

void Lighting::setLightingAmbient(float a, float b, float c, float d)
{
	ambient.a=a;
	ambient.b=b;
	ambient.c=c;
	ambient.d=d;
}