#ifndef MYSPHERE_H
#define MYSPHERE_H

#include "CGFobject.h"

class mySphere: public CGFobject {

	int slices, stacks;
	double angle, height, stackHeight;

	public:
		mySphere(int slices, int stacks);
		void draw();
};

#endif