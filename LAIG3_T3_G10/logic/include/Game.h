#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "utils.h"
#include <algorithm>
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
	bool movepod(int player, int pod, int x, int y);
	bool addpod(int player, int idpod, int x,int y);

	void processaDir(Pod* aux, string dir, int player);

	string checkMovimentos(int player, int id);
	string checkProngs(int player, string dir);
	string checkandAdd(int player, int id);
	vector<int> getOctiPlaces();
	string executaOperacao(vector<int> valoresRecebidos);
	Board* getBoard();
	void removeSomeCenas(vector<int> valores);


	void removeProng(int player, int podnumber, int dir);
	void unmovePod(int player, int podnumber, int incx, int incy);
	void unaddPod(int player,int podnumber);
	string checkAdd(int player, int id);

	vector<int> getPodsToAddProng();
	vector<int> getDirsToAddProng(int pod);
	vector<int> getPodsToAdd();

	bool checkcomprong();
	bool checkcommove();
	bool checkcomadd();


	vector<int> getPodsWithProng();

	vector<int> getHousesToMove(int podnumber);

};

#endif