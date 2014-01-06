#ifndef PRONG_H
#define PRONG_H

using namespace std;

#include <string>

class Prong{
private:
	string dir;
public:
	Prong(string dir);
	string getDir();

};

#endif