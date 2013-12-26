#ifndef MY_ROBOT
#define MY_ROBOT

#include "CGF/CGFobject.h"
#include "myCylinder.h"
#include "myUnitCube.h"

#include <vector>

using std::vector;


struct Coordenadas {
    double x , y , z;
};

struct Vertice {

    Coordenadas coord;
    Coordenadas normalFinal;

};

class myRobot : public CGFobject {

	private:
		double rotation;
		double x, y, z;
		int stacks;

		vector< vector< Vertice > > figura;
		vector< Coordenadas > pontos_circulo;
		vector< Coordenadas > pontos_base;

	public:
		Coordenadas surfacenormal(Coordenadas point1, Coordenadas point2, Coordenadas point3);
		Coordenadas newellsNormal(vector<Coordenadas> points);
		myRobot(int Stacks = 10);
		void draw(int mode);
		double getRotation() { return rotation; }
		void setRotation(double Rotation) { rotation = Rotation; }
		void incrementRotation(double Rotation) { rotation += Rotation; }
		vector< Vertice > calculateReta(Coordenadas point1, Coordenadas point2);
		double getX() { return x; }
		double getY() { return y; }
		double getZ() { return z; }

		void setX(double X) { x = X; }
		void setY(double Y) { y = Y; }
		void setZ(double Z) { z = Z; }
};



#endif