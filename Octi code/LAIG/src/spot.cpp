#include "spot.h"
#include <iostream>

void Spot::setIdI(int id){
	this->idI = id;
}

void Spot::setSExponent(float exponent){
	this->exponent = exponent;
}

void Spot::setSAngle(float angle){
	this->angle = angle;
}

void Spot::setSDirection(float* dir){
	this->direction[0] = dir[0];
	this->direction[1] = dir[1];
	this->direction[2] = dir[2];
}

float* Spot::getSDirection(){
	return &direction[0];
}

float Spot::getIdI(){
	return idI;
}

float Spot::getSAngle(){
	return angle;
}

float Spot::getSExponent(){
	return exponent;
}