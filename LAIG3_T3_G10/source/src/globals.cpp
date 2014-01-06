#include "globals.h"

void Globals::setDrawmode(string newDrawmode){
	drawmode = newDrawmode;
}

void Globals::setShading(string newShading){
	shading = newShading;
}

void Globals::setCullface(string newCullface){
	cullface = newCullface;
}

void Globals::setCullorder(string newCullorder){
	cullorder = newCullorder;
}

void Globals::setBackground(float c1, float c2, float c3, float c4){
	this->background_c1 = c1;
	this->background_c2 = c2;
	this->background_c3 = c3;
	this->background_c4 = c4;
}