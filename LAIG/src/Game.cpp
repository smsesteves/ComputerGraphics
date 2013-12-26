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


Board* Game::getBoard()
{
	return gameBoard;
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

void Game::graph_addProngToPod(int idpicado,int dir,YAFScene* scene){
	cout << "IDPICADO: " << idpicado << endl;
	cout << "DIR     : " << dir << endl;

	string s;
			
	Node* aux = new Node();

	if(turn == 1){
		cout << "Entrou" << endl;
		switch(dir){
		case 1: 
			s="ProngSul"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongAzulSul");

			break;
		case 2:


			s="ProngSudeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);

			aux->addChildren("prongAzulSudeste");

			break;
		case 3:
			s="ProngEste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongAzulEste");
		
			
			break;
		case 4:


			s="ProngNordeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongAzulNordeste");

			
			break;
		case 5:
			s="ProngNorte"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongAzulNorte");

			break;
		case 6:

			s="ProngNoroeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongAzulNoroeste");
			break;
		case 7:

			s="ProngOeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongAzulOeste");
		
		
			break;
		case 8:
			s="ProngSudoeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongAzulSudoste");
		
			
			break;
		}
	}
	else if(turn == 2){
		switch(dir){
		case 1: 
			s="ProngSul"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoSul");
		
			break;
		case 2:
			s="ProngSudeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoSudeste");

			break;
		case 3:
			s="ProngEste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoEste");
	
			break;
		case 4:
			s="ProngNordeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoNordeste");

			break;
		case 5:
			s="ProngNorte"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoNorte");
		
			break;
		case 6:
			s="ProngNoroeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoNoroeste");
		
			break;
		case 7:
			s="ProngOeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoOeste");
	
			break;
		case 8:
			s="ProngSudoeste"+intToString(idpicado);
			aux->setId(s);
			aux->setAnimationid("moveProng");
			aux->toanimate=true;
			((LinearAnimation*)scene->animationsComp["moveProng"])->started=false;
			scene->graphanimation[scene->animationsComp["moveProng"]].push_back(aux);
			scene->graph.insert(pair<string,Node*>(s,aux));
			boardElements[idpicado]->addChildren(s);
			aux->addChildren("prongVermelhoSudoste");

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




bool Game::movepod(int player, int podnumber, int x,int y, int incx, int incy)
{
	
	if(player==1)
	{
		for(int i=0;i<gameBoard->getJogador1Size();i++)
		{
			if(gameBoard->getJogador1PodAt(i)->getId()==podnumber%10)
			{
				

						Pod * aux = gameBoard->getJogador1PodAt(i);
						
						aux->setX(x);
						aux->setY(y);

						graph_movePod(podnumber,incx,incy);

						return true;
					
				
				
			}
		}
	
	}
	else
	{
		for(int i=0;i<gameBoard->getJogador2Size();i++)
		{
			if(gameBoard->getJogador2PodAt(i)->getId()==podnumber%10)
			{
				
				
						Pod * aux = gameBoard->getJogador2PodAt(i);
						aux->setX(x);
						aux->setY(y);
						
						graph_movePod(podnumber,incx,incy);

						return true;
					
				
				
			}
		}
	}
	return false;
}

void Game::graph_movePod(int podnumber,int incx,int incy)
{
	glMatrixMode(GL_MODELVIEW); 
	Node* aux=boardElements[podnumber];
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glTranslated(-incx*1.5,0,incy*1.5);	
	glMultMatrixf(aux->getmatrix());

	glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0]);
	aux->setmatrix(&matrix[0]);
	glPopMatrix();
	return;
}