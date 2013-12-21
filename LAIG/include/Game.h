#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "utils.h"
#include <map>
#include "node.h"

class Game{
private:
	bool ended;
	Board* gameBoard;
public:
	int turn;
	int idLastPick;
	
	map<int,Node*> boardElements;
	vector<int> idsReceived;
	bool pickedAnything;
	Game();

	// Graphical
	void highlightId(int id);
	void unhighlightId(int id);


	// Logical
	bool getEnded();
	void createBoard();
	void displayBoard();
	void menu(int player);
	//void menuaddpod(int player);
	//void menuaddprong(int player);
	//void menumovepod(int player);
	void displayWin(int player){};
	void play(int op,int player);
	bool checkaddprong(int player, char pod, char dir);
	bool checkmovepod(int player, char pod, string dir);
	bool checkaddpod(int player, char idpod, string idcasa);
};

#endif