#include "myRobot.h"
#include <iostream>


myRobot::myRobot(int Stacks)
{
    rotation = x = y = z = 0;
	stacks = Stacks;

	double pi = acos(-1);

	double tmp = 5*pi/4;

	Coordenadas ponto;	

	// Base posicao 0

	for(double i = 0; i < 3; i++) {
		ponto.x = -0.5;
		ponto.y = 0;
		ponto.z = -0.5 + (i/3);
		pontos_base.push_back(ponto);
	}

	for(double i = 0; i < 3; i++) {
		ponto.x = -0.5 + (i/3);
		ponto.y = 0;
		ponto.z = 0.5;
		pontos_base.push_back(ponto);
	}

	for(double i = 0; i < 3; i++) {
		ponto.x = 0.5;
		ponto.y = 0;
		ponto.z = 0.5 - (i/3);
		pontos_base.push_back(ponto);
	}

	for(double i = 0; i < 3; i++) {
		ponto.x = 0.5 - (i/3);
		ponto.y = 0;
		ponto.z = -0.5;
		pontos_base.push_back(ponto);
	}

	
	//TOPO posicao 1
	
	ponto.x = 0.25*cos(tmp);
	ponto.y = 1;
	ponto.z = 0.25*sin(tmp);
	pontos_circulo.push_back(ponto);

	for(int i = 1; i < 12; i++) {
		tmp -= pi/6;
		ponto.x = 0.25*cos(tmp);
		ponto.y = 1;
		ponto.z = 0.25*sin(tmp);
		pontos_circulo.push_back(ponto);
	}

	// STACKS

	for(int i=0;i<pontos_base.size();i++)
		figura.push_back(calculateReta(pontos_base[i],pontos_circulo[i]));

	//  NORMAIS

	for(int i = 0; i < figura.size(); i++) {

		// Base 

		vector<Coordenadas> points;

		if(i == 0)
			points.push_back(figura[figura.size()-1][0].coord);
		else
			points.push_back(figura[(i-1)][0].coord);

		points.push_back(figura[(i+1)%figura.size()][0].coord);

		if(figura.size() > 1) {
			points.push_back(figura[(i+1)%figura.size()][1].coord);
			if(i == 0)
				points.push_back(figura[figura.size()-1][1].coord);
			else
				points.push_back(figura[(i-1)][0].coord);
		}

		figura[i][0].normalFinal = newellsNormal(points);

		// Topo

		points.clear();

		if(figura.size() > 1) {
			if(i == 0) {
				points.push_back(figura[figura.size()-1][figura[i].size()-1].coord);
				points.push_back(figura[figura.size()-1][figura[i].size()-2].coord);
			} else {
				points.push_back(figura[(i-1)][figura[i].size()-1].coord);
				points.push_back(figura[(i-1)][figura[i].size()-2].coord);

			}

			points.push_back(figura[(i+1)%figura.size()][figura[i].size()-2].coord);
			points.push_back(figura[(i+1)%figura.size()][figura[i].size()-1].coord);

			figura[i][figura[i].size()-1].normalFinal = newellsNormal(points);
		}


		// Restantes

		for(int j = 1; j < figura[i].size()-1; j++) {

			points.clear();

			// 1
			if(i == 0)
				points.push_back(figura[figura.size()-1][j].coord);
			else
				points.push_back(figura[(i-1)][j].coord);

			// 6 e 5
			points.push_back(figura[i][j-1].coord);
			points.push_back(figura[(i+1)%figura.size()][j-1].coord);
			
			// 4
			points.push_back(figura[(i+1)%figura.size()][j].coord);

			// 3 e 2
			if(j < (figura[i].size()-1)) {
				points.push_back(figura[i][j+1].coord);
				if(i == 0)
					points.push_back(figura[figura.size()-1][j+1].coord);
				else
					points.push_back(figura[(i-1)][j+1].coord);
			}

			figura[i][j].normalFinal = newellsNormal(points);

		}
	}
	
	// TESTES

	//for(int i = 0; i < figura.size(); i++) {
	//	for(int j = 0; j < figura[i].size(); j++) {
	//		std::cout << "x: " << figura[i][j].coord.x << " | y: " << figura[i][j].coord.y << " | z: " << figura[i][j].coord.z << std::endl;
	//	}
	//	std::cout << std::endl;
	//}


}

vector< Vertice > myRobot::calculateReta(Coordenadas point1, Coordenadas point2)
{
	Coordenadas scales;
	vector< Vertice > res;

	scales.x = point2.x - point1.x;
	scales.y = point2.y - point1.y;
	scales.z = point2.z - point1.z;

	for(double i=0;i<=stacks;i++)
	{
		Vertice resultado;
		double t = ( i/stacks - point1.y ) / scales.y; 

		resultado.coord.x = t*scales.x + point1.x;
		resultado.coord.y = t*scales.y + point1.y;
		resultado.coord.z = t*scales.z + point1.z;

		//std::cout << "x: " << resultado.coord.x << " | y: " << resultado.coord.y << " | z: " << resultado.coord.z << std::endl;

		res.push_back(resultado);
	}
	//std::cout << std::endl;
	return res;
}

void myRobot::draw(int mode)
{
	glPushMatrix();
	if(mode==0)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glTranslated(x,y,z);
	glRotated(rotation,0,1,0);

	for(int j = 0; j < figura.size(); j++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int i = 0; i < figura[j].size(); i++) {

			glTexCoord2f(figura[j][i].coord.x + 0.5  ,-figura[j][i].coord.z + 0.5);

			glNormal3d(figura[j][i].normalFinal.x,figura[j][i].normalFinal.y,figura[j][i].normalFinal.z);
			glVertex3d(figura[j][i].coord.x, figura[j][i].coord.y, figura[j][i].coord.z);

			if(j == figura.size()-1) {
				glTexCoord2f(figura[0][i].coord.x + 0.5, -figura[0][i].coord.z + 0.5);

				glNormal3d(figura[0][i].normalFinal.x,figura[0][i].normalFinal.y,figura[0][i].normalFinal.z);
				glVertex3d(figura[0][i].coord.x, figura[0][i].coord.y, figura[0][i].coord.z);
			} else {
				glTexCoord2f(figura[j+1][i].coord.x + 0.5, -figura[j+1][i].coord.z + 0.5);

				glNormal3d(figura[j+1][i].normalFinal.x,figura[j+1][i].normalFinal.y,figura[j+1][i].normalFinal.z);
				glVertex3d(figura[j+1][i].coord.x, figura[j+1][i].coord.y, figura[j+1][i].coord.z);
			}
		}
		glEnd();
	}


	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	for(int i = 0; i < figura.size(); i++) {
		glVertex3d(figura[i][figura[i].size()-1].coord.x, figura[i][figura[i].size()-1].coord.y, figura[i][figura[i].size()-1].coord.z);
	}
	glEnd();

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glPopMatrix();

}

Coordenadas myRobot::surfacenormal(Coordenadas point1, Coordenadas point2, Coordenadas point3)
{

	Coordenadas resultado;
	Coordenadas vector1;
	Coordenadas vector2;

	vector1.x = point2.x-point1.x;
	vector1.y = point2.y-point1.y;
	vector1.z = point2.z-point1.z;

	vector2.x = point3.x-point1.x;
	vector2.y = point3.y-point1.y;
	vector2.z = point3.z-point1.z;

	resultado.x = vector1.y*vector2.z - vector1.z*vector2.y;
	resultado.y = vector1.z*vector2.x - vector1.x*vector2.z;
	resultado.z = vector1.x*vector2.y - vector1.y*vector2.x;

	double norma = sqrt( resultado.x * resultado.x + resultado.y * resultado.y + resultado.z * resultado.z);

	if(norma != 0) {
		resultado.x /= norma;
		resultado.y /= norma;
		resultado.z /= norma;
	}

	return resultado;
}

Coordenadas myRobot::newellsNormal(vector<Coordenadas> points) {

	Coordenadas normal;
	normal.x = normal.y = normal.z = 0;

	for(int i = 0; i < points.size(); i++) {

		Coordenadas current = points[i];
		Coordenadas next = points[(i+1)%points.size()];

		normal.x += (current.y - next.y) * (current.z + next.z);
		normal.y += (current.z - next.z) * (current.x + next.x);
		normal.z += (current.x - next.x) * (current.y + next.y);
	}

	double norma = sqrt( normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	if(norma != 0) {
		normal.x /= norma;
		normal.y /= norma;
		normal.z /= norma;
	}

	return normal;
}

/*void myRobot::update()
{

}*/