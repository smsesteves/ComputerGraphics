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

	void setX(int incX);
	void setY(int incY);

	int getY();
	void incX();
	void incY();
	void decX();
	void decY();
	int getDirsSize();
	Prong* getDirsAt(int pos);
	void addProng(string dir);
	void removeProng(string dir);

	int getId();
	void setId(int newid);
};

#endif