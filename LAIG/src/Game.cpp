#include "Game.h"

Game::Game(){
	createBoard();
	turn = 1;
	pickedAnything = false;
	idLastPick = 0;
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
	boardElements[id]->switchApp(1);
}

void Game::unhighlightId(int id){
	boardElements[id]->switchApp(0);
}