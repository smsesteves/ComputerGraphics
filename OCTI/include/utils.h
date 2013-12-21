#ifndef UTILS_H
#define UTILS_H

#include "Pod.h"
#include "Board.h"
#include <string>
#include <sstream>
#include <string.h>
#include <vector>

struct Position
{
	int incx;
	int incy;
};

void processaDir(Pod* aux, string dir);
Position processaComer(Board* board, Pod* aux, string dir);

string criastring(vector<int> resultados);

vector<int> divideStringEmInt(char* mensagem);



#endif