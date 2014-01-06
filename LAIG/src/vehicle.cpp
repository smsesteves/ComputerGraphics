#include "vehicle.h"

#include "fstream"




Vehicle::Vehicle(){

	ifstream myfile;
	myfile.open ("vehicle.btp");
	int number;
	myfile>>number;
	
	for(int i=0;i<number;i++)
	{
		vector<ControlPoint> aux;
		aux.clear();
		int order1,order2;
		float x,y,z;
		myfile>>order1>>order2;
		
		for(int j=0;j<16;j++)
		{
			myfile>>x>>y>>z;
			aux.push_back(ControlPoint(x,y,z));
			
		}
	
		Patch* p1=new Patch(order1, 5,5, "fill", aux);
		patches.push_back(p1);

	}

	
}


void Vehicle::draw(){
	glPushMatrix();
	glRotated(-90,0,1,0);
	glRotated(-90,1,0,0);

	for(unsigned int i=0;i<patches.size();i++)
	{
			patches[i]->draw();
	}
	glPopMatrix();
	

}