#ifndef NODE_H
#define NODE_H

#include <string>
#include "appearance.h"

#include <vector>
#include "cylinder.h"
#include "triangle.h"
#include "rectangle.h"
#include "primitive.h"
#include "animation.h"
#include "displaylist.h"

using namespace std;

class Node
{

private:
	
	string id;
	Appearance* app;
	float matrix[16];
	vector<string> children;
	bool visited;
	bool isDisplayList;
	float position[3];
	string anim;
	GLint pickingid;
public:
	bool toanimate;

	void addChildren(string toAdd)
	{
		children.push_back(toAdd);
	}

	Appearance* notHighlighted;
	Appearance* highlighted;
	void switchApp(int next){		
		if(next == 0){
			app = notHighlighted;
		}
		else if(next == 1){
			app = highlighted;
		}

	}

	float incposx(float m0, float m1, float m2, float m3){ 
		float res = 0;
		res += position[0] * m0;
		res += position[0] * m1;
		res += position[0] * m2;
		res += m3;
		return res;
	};
	float incposy(float m0, float m1, float m2, float m3){ 
		float res = 0;
		res += position[1] * m0;
		res += position[1] * m1;
		res += position[1] * m2;
		res += m3;
		return res;
	};
	float incposz(float m0, float m1, float m2, float m3){ 
		float res = 0;
		res += position[2] * m0;
		res += position[2] * m1;
		res += position[2] * m2;
		res += m3;
		return res;
	};
	void setx(float x){ position[0] = x;};
	void sety(float y){ position[1] = y;};
	void setz(float z){ position[2] = z;};
	
	float getx(){return position[0];};
	float gety(){return position[1];};
	float getz(){return position[2];};
	Node();
	bool hasdisplaylist;
	GLuint displayid;
	void setIsDL(bool newValue){isDisplayList = newValue;};
	bool getIsDL(){ return isDisplayList;};
	vector<Primitive*> primitives;
	void createDisplayList();
	string getId();
	void setId(string newId);
	float* getmatrix();
	void setmatrix(float* nova);
	string getstringat(int n);
	void insertstring(string aux);
	vector<string> getchildren();
	void insertprimitive(Primitive* primitiva);
	void setAppearance(Appearance* newApp){ app = newApp;};
	void setAnimationid(string newcenas){anim=newcenas;};
	bool getvisited(){return visited;};
	void setvisited(bool newcenas){visited=newcenas;};
	int getprimitivessize(){return primitives.size();};
	Appearance* getAppearance(){return app;};
	string getAnimationid(){return anim;};
	
	vector<Primitive*> getprimitives()
	{
		return primitives;
	};

	void move(Animation *aux,unsigned long t);

	void setPicking(int picking){
		this->pickingid = (GLint)picking;
	};
	GLint getPicking(){return this->pickingid;};
};

#endif