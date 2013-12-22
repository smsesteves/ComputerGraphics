#include "Game.h"

Game::Game(){
	createBoard();
	turn = 1;
	pickedAnything = false;
	idLastPick = -1;
}

bool Game::getEnded()
{
	ended=gameBoard->checkend();
	return ended;
}

void Game::createBoard()
{
	gameBoard=new Board();
}

void Game::displayBoard()
{
	gameBoard->display();
}

void Game::highlightId(int id){
	if(id != -1) boardElements[id]->switchApp(1);
	else return;
}

void Game::unhighlightId(int id){
	if(id != -1) boardElements[id]->switchApp(0);
	else return;
}

void Game::unhighlightAll(){
	unhighlightId(idLastPick);
	for(int i = 0; i < idsReceived.size(); i++){
		unhighlightId(idsReceived[i]);
	}
}

void Game::graph_addProngToPod(int idpicado,int dir){
	cout << "IDPICADO: " << idpicado << endl;
	cout << "DIR     : " << dir << endl;
	if(turn == 1){
		cout << "Entrou" << endl;
		switch(dir){
		case 1: 
			boardElements[idpicado]->addChildren("prongAzulSul");
			break;
		case 2:
			boardElements[idpicado]->addChildren("prongAzulSudeste");
			break;
		case 3:
			boardElements[idpicado]->addChildren("prongAzulEste");
			break;
		case 4:
			boardElements[idpicado]->addChildren("prongAzulNordeste");
			break;
		case 5:
			boardElements[idpicado]->addChildren("prongAzulNorte");
			break;
		case 6:
			boardElements[idpicado]->addChildren("prongAzulNoroeste");
			break;
		case 7:
			boardElements[idpicado]->addChildren("prongAzulOeste");
			break;
		case 8:
			boardElements[idpicado]->addChildren("prongAzulSudoste");
			break;
		}
	}
	else if(turn == 2){
		switch(dir){
		case 1: 
			boardElements[idpicado]->addChildren("prongVermelhoSul");
			break;
		case 2:
			boardElements[idpicado]->addChildren("prongVermelhoSudeste");
			break;
		case 3:
			boardElements[idpicado]->addChildren("prongVermelhoEste");
			break;
		case 4:
			boardElements[idpicado]->addChildren("prongVermelhoNordeste");
			break;
		case 5:
			boardElements[idpicado]->addChildren("prongVermelhoNorte");
			break;
		case 6:
			boardElements[idpicado]->addChildren("prongVermelhoNoroeste");
			break;
		case 7:
			boardElements[idpicado]->addChildren("prongVermelhoOeste");
			break;
		case 8:
			boardElements[idpicado]->addChildren("prongVermelhoSudoste");
			break;
		}
	}

}

string Game::getDir(int dirI){
	string dir;
	switch(dirI){
		case 1: dir="s";break;
		case 2:dir="se";break;
		case 3:dir="e";break;
		case 4:dir="ne";break;
		case 5:dir="n";break;
		case 6:dir="no";break;
		case 7:dir="o";break;
		case 8:dir="so";break;
	}

	return dir;

}

bool Game::addprong(int player, int podnumber, string dir)
{
	if(player==1)
	{
		for(int i=0;i<gameBoard->getJogador1Size();i++)
		{
			if(gameBoard->getJogador1PodAt(i)->getId()==podnumber)
			{
				gameBoard->getJogador1PodAt(i)->addProng(dir);
				return true;
			}
		}
	}
	else
	{
		for(int i=0;i<gameBoard->getJogador2Size();i++)
		{
			if(gameBoard->getJogador2PodAt(i)->getId()==podnumber)
			{
				gameBoard->getJogador2PodAt(i)->addProng(dir);
				return true;
			}
		}
		return false;
	}
}
