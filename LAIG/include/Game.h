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
	int dificuldade;
	void setDificuldade(int dif);
	int getDificuldade();

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
	void graph_movePod(int podnumber,int incx,int incy, YAFScene* scene);
	void graph_addPod(int podnumber, int idocti, YAFScene* scene);


	// Logical
	string getDir(int dir);
	bool getEnded();
	Board* getBoard();
	void createBoard();
	void displayBoard();
	void menu(int player);

	bool addprong(int player, int pod, string dir);
	bool movepod(int player, int podnumber, int x,int y, int incx, int incy, YAFScene* scene);
	bool addpod(int player, int idpod, int x,int y);

	void displayWin(int player){};
	void play(int op,int player);

	void setEnded(bool newValue);
	

};

#endif