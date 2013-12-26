#include "Pod.h"


Pod::Pod(int player,int x,int y,int id)
{
	this->player=player;
	this->x=x;
	this->y=y;
	this->id=id;
	dirs.clear();
}

int Pod::getPlayer()
{
	return player;
}

int Pod::getX()
{
	return x;
}

int Pod::getY()
{
	return y;
}

void Pod::incX()
{
	x++;
}

void Pod::incY()
{
	y++;
}

void Pod::decX()
{
	x--;
}

void Pod::decY()
{
	y--;
}

int Pod::getDirsSize()
{
	return dirs.size();
}

Prong* Pod::getDirsAt(int pos)
{
	return dirs[pos];
}


void Pod::addProng(string dir)
{ 
	Prong* aux= new Prong(dir);
	dirs.push_back(aux);
}

void Pod::setId(int newid)
{
	id=newid;
}

int Pod::getId()
{
	return id;

}

void Pod::setX(int incX)
{
	x=incX;
}
void Pod::setY(int incY)
{
	y=incY;
}