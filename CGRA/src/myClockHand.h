#ifndef MYCLOCKHAND_H
#define MYCLOCKHAND_H

#include "CGFobject.h"
#include "myUnitCube.h"

class myClockHand: public CGFobject {

	myUnitCube* ponteiro;
	float angle;
	public:
		myClockHand();
		void draw(int type);
		void setAngle(float angle);
};

#endif