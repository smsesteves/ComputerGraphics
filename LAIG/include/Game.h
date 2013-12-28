#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "utils.h"
#include <map>
#include "node.h"
#include "YAFScene.h"
#include "socket.h"



class Game{
private:
	bool ended;
	Board* gameBoard;
public:

	vector<string> jogadas;

	int dificuldade;
	void setDificuldade(int dif);
	int getDificuldade();
	int lastturn;
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
	void rotateCamera(YAFScene* scene,int turn);

	// PC
	void comHandler(vector<float> valores,YAFScene* scene);
	void com_addProng(vector<float> valores,YAFScene* scene);
	void com_movePod(vector<float> valores, YAFScene* scene);
	void com_addPod(vector<float> valores, YAFScene* scene);

	void comTurn(YAFScene* scene);

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
	
	void undoPlay(YAFScene* scene);

	void removeProng(int podnumber,int dir,YAFScene* scene);

	void unmovePod(int podnumber,int x, int y,int incx,int incy);
	void removePod(int player,int podnumber);
	void unaddPod (int podnumber,float xi,float yi,float xf,float yf);


};

#endif