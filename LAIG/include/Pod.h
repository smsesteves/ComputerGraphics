#ifndef POD_H
#define POD_H

#include "Prong.h"

using namespace std;
#include <vector>

class Pod{
	int player;
	int x,y;
	vector<Prong*> dirs;
	int id;
public:
	Pod(int player,int x,int y,int id);
	int getPlayer();
	int getX();
	int getY();
	void incX();
	void incY();
	void decX();
	void decY();

	void setX(int incX);
	void setY(int incY);


	int getDirsSize();
	Prong* getDirsAt(int pos);
	void addProng(string dir);
	int getId();
	void setId(int newid);
};

#endif