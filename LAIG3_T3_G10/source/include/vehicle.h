#ifndef VEHICLE_H
#define VEHICLE_H


#include "primitive.h"
#include "patch.h"

#define VORDER 10
#define CORDER 10
#define TORDER 3

#define VMAJOR_ORDER 2
#define VMINOR_ORDER 3

#define CMAJOR_ORDER 2
#define CMINOR_ORDER 2

#define TMAJOR_ORDER 2
#define TMINOR_ORDER 2

#define VDIM 4
#define CDIM 4
#define TDIM 2

#define ONE_D 1
#define TWO_D 2

#define EVAL 3
#define MESH 4


using namespace std;

class Vehicle : public Primitive
{
public:
	Vehicle();
	vector<Patch*> patches;
	void draw();

};

#endif