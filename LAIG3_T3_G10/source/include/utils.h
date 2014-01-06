#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <string>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

float distanciapontos(float x1, float y1, float z1, float x2, float y2, float z2);

float radiustodegrees(float angle);

vector<int> divideStringEmInt(const char* mensagem);

string intToString(int i);

vector<float> divideStringEmFloat(const char* mensagem);


#endif