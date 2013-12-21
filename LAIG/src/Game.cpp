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
