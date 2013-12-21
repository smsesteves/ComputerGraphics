#ifndef WATERLINE_H
#define WATERLINE_H


#include "primitive.h"
#include "plane.h"
#include "CGFshader.h"
#include <GL/glut.h>
using namespace std;

class Waterline : public Primitive, public CGFshader
{
private:
	string heightmap, texturemap, fragmentshader, vertexshader;
	Plane* p1;
	float normScale;
	CGFtexture * baseTexture;
	CGFtexture * secTexture;

	GLint baseImageLoc;
	GLint secImageLoc;

	float t;

public:
	Waterline(string hm, string tm, string fshader, string vshader);

	~Waterline(void);
	void setScale(float s);
	void draw();
	void bind();

};

#endif