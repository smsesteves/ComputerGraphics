#ifndef MY_CYLINDER
#define MY_CYLINDER

#include "CGF/CGFobject.h"

class myCylinder : public CGFobject {

	int slices, stacks;
	double angle, height;
	bool smooth;

	public:
		myCylinder(int slices, int stacks, bool smooth = true);
		void draw();
		

};



#endif
