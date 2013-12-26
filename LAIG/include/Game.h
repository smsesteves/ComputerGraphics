#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "utils.h"
#include <map>
#include "node.h"
#include "YAFScene.h"


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
	void unhighlightAll();
	void graph_addProngToPod(int id, int dir,YAFScene * graph);
	void graph_movePod(int podnumber,int incx,int incy);
	void graph_addPod(int podnumber, int idocti);


	// Logical
	string getDir(int dir);
	bool getEnded();
	Board* getBoard();
	void createBoard();
	void displayBoard();
	void menu(int player);

	bool addprong(int player, int pod, string dir);
	bool movepod(int player, int podnumber, int x,int y, int incx, int incy);
	bool addpod(int player, int idpod, int x,int y);

	void displayWin(int player){};
	void play(int op,int player);
	

};

#endif