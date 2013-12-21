#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "utils.h"

class Game{
private:
	bool ended;
	Board* gameBoard;
public:
	bool getEnded();
	void createBoard();
	void displayBoard();
	void menu(int player);
	//void menuaddpod(int player);
	//void menuaddprong(int player);
	//void menumovepod(int player);
	void displayWin(int player){};
	void play(int op,int player);
	bool addprong(int player, int pod, string dir);
	bool movepod(int player, int pod, string dir);
	bool addpod(int player, int idpod, int idcasa);


	string checkMovimentos(int player, int id);
	string checkProngs(int player, string dir);
	string checkandAdd(int player, int id);

	string executaOperacao(vector<int> valoresRecebidos);
	Board* getBoard();

	string checkAdd(int player, int id);
};

#endif