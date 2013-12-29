#include "Game.h"

Game::Game(){
	createBoard();
	turn = 1;
	lastturn =1;
	ended = false;
	pickedAnything = false;
	idLastPick = -1;
	idsReceived.clear();
}

void Game::rotateCamera(YAFScene* scene, int turn){
	cout << "Rotating Camera " << endl;

	if(turn == 1){

		for(int i = 0; i < scene->camerasComp.size(); i++){
			if(scene->camerasComp[i]->getid() == "camJogadorAzul"){
				scene->camerasComp[i]->setRotation(CG_CGFcamera_AXIS_Y, 180);
				((Perspective *)scene->camerasComp[i])->toanimate = true;
			}
		}
	}
	else if(turn == 2){
		for(int i = 0; i < scene->camerasComp.size(); i++){
			if(scene->camerasComp[i]->getid() == "camJogadorAzul"){
				scene->camerasComp[i]->setRotation(CG_CGFcamera_AXIS_Y, 0);
				((Perspective *)scene->camerasComp[i])->toanimate = true;
			}
		}

	}

}


void Game::setEnded(bool newBool){
	ended = newBool;
}


void Game::setDificuldade(int dif){
	this->dificuldade = dif;
}

int Game::getDificuldade(){
	return this->dificuldade;
}

bool Game::getEnded()
{
	//ended=gameBoard->checkend();
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
			aux->addChildren("prongAzulSudoeste");


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
			aux->addChildren("prongVermelhoSudoeste");

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


bool Game::movepod(int player, int podnumber, int x,int y, int incx, int incy, YAFScene* scene)
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

				graph_movePod(podnumber,incx,incy,scene);

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

				graph_movePod(podnumber,incx,incy,scene);

				return true;



			}
		}
	}
	return false;
}

void Game::graph_movePod(int podnumber,int incx,int incy, YAFScene* scene)
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

	aux->setAnimationid("movePod");
	((LinearAnimation*)scene->animationsComp["movePod"])->setSignalControlPoints(incx,incy);
	aux->toanimate=true;
	((LinearAnimation*)scene->animationsComp["movePod"])->started=false;
	scene->graphanimation[scene->animationsComp["movePod"]].push_back(aux);



	return;
}

bool Game::addpod(int player, int idpod, int x,int y)
{

	if(player==1)
	{

		gameBoard->addJogador1PodAt(x,y,idpod);

	}
	else
	{
		gameBoard->addJogador2PodAt(x,y,idpod);
	}
	return true;

}


void Game::graph_addPod(int podnumber, int idocti, YAFScene* scene){
	cout << "POD " << podnumber << " para pos " << idocti << endl;
	glMatrixMode(GL_MODELVIEW); 
	Node* pod = boardElements[podnumber];
	Node* celula = boardElements[idocti];
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glTranslated(celula->getx()-50,celula->gety()+1,celula->getz()-50); //casa octi
	glTranslated(-pod->getx(),-pod->gety(),-pod->getz());
	glMultMatrixf(pod->getmatrix());
	glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0]);
	pod->setmatrix(&matrix[0]);
	glPopMatrix();


	vector<ControlPoint> c1;
	c1.push_back(ControlPoint(50+pod->getx()-celula->getx(),-1,50+pod->getz()-celula->getz()));
	c1.push_back(ControlPoint(0,1,0));


	LinearAnimation* l1= new LinearAnimation("addPod",1,c1);

	pod->setAnimationid("addPod");
	scene->animationsComp[l1->getId()]=l1;
	pod->toanimate=true;
	((LinearAnimation*)scene->animationsComp["addPod"])->started=false;
	scene->graphanimation[scene->animationsComp["addPod"]].push_back(pod);



	return;
}

void Game::undoPlay(YAFScene* scene)
{
	vector<float> resultado=divideStringEmFloat(jogadas[jogadas.size()-1].c_str());

	int a=resultado[0];

	switch(a)
	{
	case 1: removeProng(resultado[1],resultado[2],scene); break;//anula prong
	case 2: unmovePod(resultado[1],resultado[2],resultado[3],resultado[4],resultado[5]);break;//anula move
	case 3: unaddPod(resultado[1],resultado[4],resultado[5],resultado[6],resultado[7]);break;              
	}
	jogadas.erase(jogadas.end()-1);
}

void Game::removeProng(int podnumber, int dir,YAFScene* scene)
{
	map<string,Node*>::iterator it;
	string s;
	int player= podnumber/10;
	cout << "Entrou" << endl;
	switch(dir){
	case 1: 
		s="ProngSul"+intToString(podnumber);
		break;
	case 2:
		s="ProngSudeste"+intToString(podnumber);
		break;
	case 3:
		s="ProngEste"+intToString(podnumber);
		break;
	case 4:
		s="ProngNordeste"+intToString(podnumber);
		break;
	case 5:
		s="ProngNorte"+intToString(podnumber);
		break;
	case 6:
		s="ProngNoroeste"+intToString(podnumber);
		break;
	case 7:
		s="ProngOeste"+intToString(podnumber);
		break;
	case 8:
		s="ProngSudoeste"+intToString(podnumber);
		break;
	}
	it=scene->graph.find(s);
	scene->graph.erase(it);
	boardElements[podnumber]->removeChildren(s);
	this->turn=player;

}

void Game::unmovePod(int podnumber,int x, int y,int incx,int incy)
{
	int player= podnumber/10;
	int id=podnumber%10;
	glMatrixMode(GL_MODELVIEW); 
	Node* aux=boardElements[podnumber];
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glTranslated(+incx*1.5,0,-incy*1.5);	
	glMultMatrixf(aux->getmatrix());
	glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0]);
	aux->setmatrix(&matrix[0]);
	glPopMatrix();

	gameBoard->setXbyId(player , id, gameBoard->getXbyId(player,id)-incx);
	gameBoard->setYbyId(player , id, gameBoard->getYbyId(player,id)-incy);

	this->turn=player;
}

void Game::unaddPod (int podnumber,float xi,float yi,float xf,float yf)
{
		int player= podnumber/10;
	glMatrixMode(GL_MODELVIEW); 
	Node* pod = boardElements[podnumber];
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glTranslated(xi-xf,-1,yi-yf);
	glMultMatrixf(pod->getmatrix());
	glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0]);
	pod->setmatrix(&matrix[0]);
	glPopMatrix();

	removePod(podnumber/10,podnumber%10);

		this->turn=player;

}



void Game::removePod(int player,int podnumber)
{
	if(player==1)
	{
		for(int i=0;i<gameBoard->getJogador1Size();i++)
		{
			if(gameBoard->getJogador1PodAt(i)->getId()==podnumber)
			{
				gameBoard->removeJogador1PodAt(i);
			}

		}
	}
	else
	{
		for(int i=0;i<gameBoard->getJogador2Size();i++)
		{
			if(gameBoard->getJogador2PodAt(i)->getId()==podnumber)
			{
				gameBoard->removeJogador2PodAt(i);
			}

		}
	}

}

void Game::comHandler(vector<float> valores,YAFScene* scene){
	int op = valores[0];

	switch(op){
	case 1: // add prong 
		com_addProng(valores, scene);
		break; 
	case 2:  // move pod
		com_movePod(valores, scene);
		break; 
	case 3:  // add pod
		com_addPod(valores, scene);
		break;

	}

}

void Game::com_addProng(vector<float> valores, YAFScene* scene){

	
	int dir = valores[2];
	
	addprong(2, (int)valores[1] %10 , getDir(dir));

	graph_addProngToPod(valores[1],dir,scene);
	
	pickedAnything = false;
	idLastPick = -1;
}


void Game::com_movePod(vector<float> valores, YAFScene* scene){
	
		// 2 IDPOD CELX CELY INCX INCY

		movepod(2,valores[1],valores[2],valores[3],valores[4],valores[5], scene);
				
	
}

void Game::com_addPod(vector<float> valores, YAFScene* scene){

	
	addpod(valores[1]/10, (int)valores[1]%10, valores[2],valores[3]);
	graph_addPod(valores[1], 100 + valores[2] * 10 + valores[3], scene);


	//readMessage();
	//cout << "[ADD_POD] A logica nao respondeu nada\n";


				
		pickedAnything = false;
		idLastPick = -1;
		turn = 1; // muda de turno
}


// ****************************************
//    COMPUTADOR A JOGAR
// ****************************************
void Game::comTurn(YAFScene* scene){

	if(dificuldade > 0 && turn == 2){

		if(turn==2 && getDificuldade() > 0){
			cout << "COMPUTADOR !! " << endl;
			// COMPUTADOR A JOGAR
			string mensagem1;
			mensagem1 = "gerar";
			sendMessage(mensagem1.c_str());
			char* resposta = readMessage();


			if(resposta[0] == '2'){


				// 2 IDPOD X Y
				vector<float> respostas = divideStringEmFloat(resposta);
				string resposta1(resposta);

				int xf= respostas[2];
				int yf= respostas[3];

				int xi=getBoard()->getXbyId(2,(int)respostas[1]%10);
				int yi=getBoard()->getYbyId(2,(int)respostas[1]%10%10);


				int incx=xf-xi;
				int incy=yf-yi;


				resposta1 += " ";
				resposta1 += to_string(incx);
				resposta1 += " ";
				resposta1 += to_string(incy);

				jogadas.push_back(resposta1);
				comHandler(divideStringEmFloat(resposta1.c_str()), scene);

				char* mensagem2 = readMessage();
				cout << "[MOVE_POD] Recebeu " << mensagem2 << endl;
				if(strcmp(mensagem2,"666") == 0){
					setEnded(true);
					//sendMessage("100000");
				}

				pickedAnything = false;
				idLastPick = -1;
				turn = 1; // muda de turno
			}
			else if(resposta[0] == '3'){
				// 3 IDPOD X Y
				vector<float> respostas = divideStringEmFloat(resposta);
				string resposta1(resposta);

				resposta1 = "3 " + to_string(respostas[1]);
				resposta1 += " ";

				int x= respostas[2];
				int y= respostas[3];

				resposta1 += to_string(x);
				resposta1 += " ";
				resposta1 += to_string(y);

				resposta1 += " ";

				//x inicial

				resposta1 += to_string(boardElements[respostas[1]]->getx()+50.0*1.0);
				resposta1 += " ";
				//z inicial
				resposta1 += to_string(boardElements[respostas[1]]->getz()+50.0*1.0);
				resposta1 += " ";
				//x final
				resposta1 += to_string(boardElements[100 + respostas[2] * 10 + respostas[3]]->getx()*1.0);
				resposta1 += " ";
				resposta1 += to_string(boardElements[100 + respostas[2] * 10 + respostas[3]]->getz()*1.0);

				jogadas.push_back(resposta1);
				
				comHandler(divideStringEmFloat(resposta1.c_str()), scene);
				
			}
			else{
				jogadas.push_back(resposta);
				comHandler(divideStringEmFloat(resposta), scene);
				cout << "Jogada: '" << resposta << "'" << endl;

			}
			turn = 1;
			//TODO : verifcar end
		}

	}
}


void Game::reset(YAFScene* scene)
{
	
}