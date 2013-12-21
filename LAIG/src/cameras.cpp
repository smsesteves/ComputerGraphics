#include "cameras.h"

void Cameras::setCInitial(bool initial){
	this->initial = initial;
}

void Cameras::setCPrimary(string id, float near, float far){
	this->id = id;
	this->near = near;
	this->far = far;
}

string Cameras::getid()
{
	return id;
}