#ifndef BOARD_H
#define BOARD_H

using namespace std;

#include <iostream>
#include <vector>
#include "Pod.h"
#include <stdlib.h>
#include "types.h"

    
class Board{

private:
	vector<Pod *> Jogador1;
	vector<Pod *> Jogador2;
	//Pod boardGame[BOARDSIZE][BOARDSIZE][BOARDSIZE];

public:
	Board();
	void display();
	bool checkmove(int player);
	bool checkadd(int player);
	bool checkend();
	int getJogador1Size();
	int getJogador2Size();
	Pod* getJogador1PodAt(int pos);
	Pod* getJogador2PodAt(int pos);
	void addJogador1PodAt(int x,int y,int id);
	void addJogador2PodAt(int x,int y,int id);
	void removeJogador1PodAt(int i);
	void removeJogador2PodAt(int i);
	int getXbyId(int player,int id);
	int getYbyId(int player,int id);

};

#endif
