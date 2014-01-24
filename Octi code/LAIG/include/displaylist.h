#ifndef DISPLAY_LIST_H
#define DISPLAY_LIST_H

#include "node.h"

class DisplayList
{
public:	
	DisplayList();
	~DisplayList();
	void draw();
	int usingDL;

private:
	void generateGeometry();
	unsigned int dl;
};

#endif
