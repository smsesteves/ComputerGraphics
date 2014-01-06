#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <iostream>

class ControlPoint{
public:
	float x,y,z;
	ControlPoint(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	};
	ControlPoint(){};
};


class Animation{
protected:
	string id;
	float span;
public:
	virtual int animationType(){return -1;};
	Animation(string id, float span){
		this->id = id;
		this->span = span;
	};
	string getId(){ return id;};
	float getSpan(){ return span;};
	virtual void init(unsigned long t){return;};
	virtual void updatePosition(unsigned long t){cout << "update position da animation ):!" << endl;};
};


#endif