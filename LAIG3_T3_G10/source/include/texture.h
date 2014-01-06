#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "CGFtexture.h"

class Texture: public CGFtexture
{
private:
	string id;
	string filePath;
public:
	Texture(string filePath):CGFtexture(filePath){};
	Texture(){};
	void setTId(string id);
	void setTPath(string filePath);
	string getTId(){ return id;};
};

#endif