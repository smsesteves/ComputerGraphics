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
	string getDir(int dir);
	bool getEnded();
	void createBoard();
	void displayBoard();
	void menu(int player);

	bool addprong(int player, int pod, string dir);

	void displayWin(int player){};
	void play(int op,int player);


};

#endif