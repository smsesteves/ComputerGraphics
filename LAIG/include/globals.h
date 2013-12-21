#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
using namespace std;

class Globals
{
private:
	string drawmode;
	string shading;
	string cullface;
	string cullorder;
	float background_c1;
	float background_c2;
	float background_c3;
	float background_c4;

public:
	void setDrawmode(string newDrawmode);
	void setShading(string newShading);
	void setCullface(string newCullface);
	void setCullorder(string newCullorder);
	void setBackground(float c1, float c2, float c3, float c4);
	string getCullface(){return cullface;};
	string getCullorder(){return cullorder;};
	
	string getShading(){return shading;};
	string getDMode(){ return drawmode;};
	 float getBG1(){ return background_c1;};
    float getBG2(){ return background_c2;};
    float getBG3(){ return background_c3;};
        float getBG4(){ return background_c4;};
};

#endif