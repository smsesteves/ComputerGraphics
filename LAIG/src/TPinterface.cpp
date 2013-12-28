#include "TPinterface.h"
TPinterface::TPinterface(Game* game, CGFapplication* app){
	this->octi = game;
	this->application = app;
}


// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

void TPinterface::processMouse(int button, int state, int x, int y) 
{
	//CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//cout << "Clicou em (" << x << ", " << y << ")\n";
		performPicking(x,y);
	}


}

void TPinterface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them

	GLint hits;
	hits = glRenderMode(GL_RENDER);

	processHits(hits, selectBuf);
}

void TPinterface::processHits(GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected=NULL;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}

	//cout << "TURN " << octi->turn << endl;


	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL && !((XMLScene*) scene)->doinganimations() && octi->turn == 1 )
	{
		clickHandler(selected, nselected);
	}
	else if(selected!=NULL && !((XMLScene*) scene)->doinganimations() && octi->dificuldade == -1 && octi->turn == 2){
		clickHandler(selected, nselected);
	}
	else{
		printf("Nothing selected while picking \n");	
	}
}


void TPinterface::clickHandler(GLuint* selected, GLint nselected){
	cout << endl << "Turno: " << octi->turn << endl;
	GLint idpicado;
	//octi->displayBoard(); cout << endl;


	for (int i=0; i<nselected; i++){
		printf("%d ",selected[i]);
		idpicado = selected[i];
		printf("\n");
	}


	char id[256];
	//*
	// ****************************************
	// UTILIZADOR CLICOU EM MENU
	// ****************************************
	if(idpicado > 500 && idpicado < 505 || idpicado == 511){
		if(idpicado == 501){
			string mensagem;
			mensagem = "PP";
			sendMessage(mensagem.c_str());
			cout << "Enviou : " << mensagem << endl;
			octi->dificuldade = -1;
			cout <<	"Recebeu: " << readMessage() << endl;;

			// RESET CENA
			// BoardElements
			// octi->reset()
			//octi = new Game();
			while(!octi->jogadas.empty()){
				octi->undoPlay(((XMLScene*)scene)->getScenePointer());
			}
			octi->createBoard();
			octi->dificuldade = -1;

			// Coloca Camera
			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camJogadorAzul"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}

		}
		if(idpicado == 502){
			string mensagem;
			mensagem = "PC";
			sendMessage(mensagem.c_str());
			cout << "Enviou : " << mensagem << endl;

			readMessage();

			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camComputador"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}
		}
		if(idpicado == 503){
			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camRegras"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}

		}
		if(idpicado == 511){
			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camMenu"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}
		}
	}
	if(idpicado > 520 && idpicado < 525){
		if(idpicado == 521){
			// EASY
			octi->setDificuldade(1);
			cout << "Selected EASY" << endl;

			string mensagem2;
			mensagem2 = "3";
			sendMessage(mensagem2.c_str());
			cout << "Enviou : " << mensagem2 << endl;
			readMessage();

			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camJogadorAzul"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}
		}
		if(idpicado == 522){
			// Normal
			octi->setDificuldade(2);
			cout << "Selected NORMAL" << endl;

			string mensagem2;
			mensagem2 = "2";
			sendMessage(mensagem2.c_str());
			cout << "Enviou : " << mensagem2 << endl;
			readMessage();

			// RESET CENA
			//octi = new Game();
			while(!octi->jogadas.empty()){
				octi->undoPlay(((XMLScene*)scene)->getScenePointer());
			}

			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camJogadorAzul"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}
		}
		if(idpicado == 523){
			// Dificil
			octi->setDificuldade(3);
			cout << "Selected HARD" << endl;

			string mensagem2;
			mensagem2 = "3";
			sendMessage(mensagem2.c_str());
			cout << "Enviou : " << mensagem2 << endl;
			readMessage();

			// RESET CENA
			//octi = new Game();
			while(!octi->jogadas.empty()){
				octi->undoPlay(((XMLScene*)scene)->getScenePointer());
			}

			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camJogadorAzul"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}
		}
		if(idpicado == 524){
			// Voltar
			vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
			for(unsigned int i= 0; i < aux.size(); i++){
				if(aux.at(i)->getid() == "camMenu"){
					((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
					((XMLScene*) scene)->refreshCameras();
					break;
				}
			}
		}
	}
	if(idpicado == 541){
		cout << "Acabou jogo!" << endl;
		// Voltar
		vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
		for(unsigned int i= 0; i < aux.size(); i++){
			if(aux.at(i)->getid() == "camMenu"){
				((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
				((XMLScene*) scene)->refreshCameras();
				return;
			}
		}
	}



	// ****************************************
	// UTILIZADOR CLICOU EM PECA DO JOGADOR 1
	// ****************************************
	if(idpicado > 10 && idpicado < 18){
		// TURNO ERRADO
		if(octi->turn == 2){
			cout << "Turno Errado. Turno atual e 1\n";
			octi->pickedAnything = false;
			octi->unhighlightAll();
			octi->idLastPick = -1;
		}
		// JA TEM SELCCIONADO UMA DIRECAO - ADICIONAR PRONG
		else if(octi->pickedAnything && octi->idLastPick > 210 && octi->idLastPick < 219){
			bool valid = false;
			for(int i = 0; i < octi->idsReceived.size(); i++){
				if (idpicado == octi->idsReceived[i]){
					valid = true;
				}

			}
			if(valid){
				string mensagem;
				mensagem = "1 " + to_string(idpicado);
				int dir = octi->idLastPick % 10;
				mensagem += " ";
				mensagem += to_string(dir);
				sendMessage(mensagem.c_str());
				octi->jogadas.push_back(mensagem);
				cout << "[ADD_PRONG] '" << mensagem << "'" << endl;

				readMessage();
				cout << "[ADD_PRONG] A logica nao respondeu nada\n";
				octi->addprong(1,idpicado%10,octi->getDir(dir));

				//prongReferencia
				octi->graph_addProngToPod(idpicado,dir,((XMLScene*) scene)->getScenePointer()) ;

				octi->unhighlightAll();
				octi->pickedAnything = false;
				octi->idLastPick = -1;
				octi->turn = 2; // muda de turno




				cout << "----------------- Fim do Turno de 1 -------------------" << endl;
			}
			else{
				cout << "Click num POD possivel\n";
			}
		}
		// MOSTRA PARA ONDE SE PODE MOVER - NAO TEM NADA PICADO OU TEM OUTRA PECA PICADA
		else if(octi->pickedAnything == false || (octi->pickedAnything == true && octi->idLastPick > 10 && octi->idLastPick < 18)){
			octi->pickedAnything = true;
			octi->unhighlightAll();

			octi->idLastPick = idpicado;
			octi->highlightId(idpicado); // highlight da peca que pickou

			string mensagem = "10 ";
			mensagem += to_string(idpicado);
			mensagem += " ";
			cout << "[MOVE POD] Enviou '" << mensagem << "'\n";
			sendMessage(mensagem.c_str());

			char* resposta = readMessage();
			cout << "[MOVE POD] Logica respondeu '" << resposta << "'" << endl;

			octi->idsReceived = divideStringEmInt(resposta);

			for(int i = 0; i < octi->idsReceived.size(); i++){
				octi->highlightId(octi->idsReceived[i]);
			}
		}

	}
	// Fim do Handler do clique na PECA 1





	// ****************************************
	// UTILIZADOR CLICOU EM PECA DO JOGADOR 2
	// ****************************************
	if(idpicado > 20 && idpicado < 28){
		// TURNO ERRADO
		if(octi->turn == 1){
			octi->pickedAnything = false;
			octi->unhighlightAll();
			octi->idLastPick = -1;
			cout << "Turno Invalido. Turno atual e 2\n";
		}
		// JA TEM SELCCIONADO UMA DIRECAO - ADICIONAR PRONG
		else if(octi->pickedAnything && octi->idLastPick > 220 && octi->idLastPick < 229){
			bool valid = false;
			for(int i = 0; i < octi->idsReceived.size(); i++){
				if (idpicado == octi->idsReceived[i]){
					valid = true;
				}
			}
			if(valid){
				string mensagem;
				mensagem = "1 " + to_string(idpicado);
				int dir = octi->idLastPick % 10;
				mensagem += " ";
				mensagem += to_string(dir);
				sendMessage(mensagem.c_str());
				cout << "[ADD_PRONG] '" << mensagem << "'" << endl;
				octi->jogadas.push_back(mensagem);
				readMessage();
				cout << "[ADD_PRONG] A logica nao respondeu nada\n";

				octi->addprong(2,idpicado%10,octi->getDir(dir));
				octi->graph_addProngToPod(idpicado,dir,((XMLScene*) scene)->getScenePointer());

				octi->unhighlightAll();
				octi->pickedAnything = false;
				octi->idLastPick = -1;
				octi->turn = 1; // muda de turno




				cout << "----------------- Fim do Turno de 2 -------------------" << endl;
			}
			else{
				cout << "Click num POD possivel\n";
			}

		}
		// MOSTRA PARA ONDE SE PODE MOVER - NAO TEM NADA PICADO OU TEM OUTRA PECA PICADA
		else if(octi->pickedAnything == false || (octi->pickedAnything == true && octi->idLastPick > 20 && octi->idLastPick < 28)){
			octi->pickedAnything = true;
			octi->unhighlightAll();
			octi->idLastPick = idpicado;
			octi->highlightId(idpicado); // highlight da peca que pickou

			string mensagem = "10 ";
			mensagem += to_string(idpicado);
			mensagem += " ";
			cout << "[MOVE POD] Enviou '" << mensagem << "'\n";
			sendMessage(mensagem.c_str());

			char* resposta = readMessage();
			cout << "[MOVE POD] Logica respondeu '" << resposta << "'" << endl;

			octi->idsReceived = divideStringEmInt(resposta);

			for(int i = 0; i < octi->idsReceived.size(); i++){
				octi->highlightId(octi->idsReceived[i]);
			}
		}
	}


	// ****************************************
	// UTILIZADOR CLICOU PRONGS JOGADOR 1
	// ****************************************
	if(idpicado > 210 && idpicado < 219){
		// TURNO ERRADO
		if(octi->turn == 2){
			octi->pickedAnything = false;
			octi->unhighlightAll();
			octi->idLastPick = -1;
			cout << "Nao pode clicar no Oct do adversario. Turno atual e 1\n";
		}
		// HIGHLIGHT DOS PODS POSSIVEIS - TEM OUTRO PRONG SELCCIONADO OU NAO TEM NADA SELECCIONADO
		else if(octi->pickedAnything == false || 
			(octi->pickedAnything && octi->idLastPick > 210 && octi->idLastPick < 219) ||
			(octi->pickedAnything && octi->idLastPick > 10 && octi->idLastPick < 18)){

				// Unhighlight do que ja estava
				if(octi->pickedAnything){
					octi->unhighlightId(octi->idLastPick);
					for(int i = 0; i < octi->idsReceived.size(); i++){
						octi->unhighlightId(octi->idsReceived[i]);
					}
				}

				// Highlight do Prong seleccionado
				octi->pickedAnything = true;
				octi->idLastPick = idpicado;
				octi->highlightId(idpicado); 

				// Envia mensagem para saber que pods pode meter highlight
				string mensagem = "11 ";
				mensagem += to_string(octi->turn);
				mensagem += " " + to_string(idpicado%10);
				cout << "[CHECK_ADD_PRONG] Enviou '" << mensagem << "'" << endl;
				cout << octi->turn << endl;
				sendMessage(mensagem.c_str());

				char* resposta = readMessage();
				cout << "[CHECK_ADD_PRONG] Resposta '" << resposta << "'" << endl;

				// Highlight dos ids que recebeu
				octi->idsReceived = divideStringEmInt(resposta);
				for(int i = 0; i < octi->idsReceived.size(); i++){
					cout << octi->idsReceived[i] << endl;
					octi->highlightId(octi->idsReceived[i]);
				}
		}
	}

	// ****************************************
	// UTILIZADOR CLICOU PRONGS JOGADOR 2
	// ****************************************
	if(idpicado > 220 && idpicado < 229){
		// TURNO ERRADO
		if(octi->turn == 1){
			octi->pickedAnything = false;
			octi->unhighlightAll();
			octi->idLastPick = -1;
			cout << "Nao pode clicar no Oct do adversario. Turno atual e 2\n";
		}
		// HIGHLIGHT DOS PODS POSSIVEIS - TEM OUTRO PRONG SELCCIONADO OU NAO TEM NADA SELECCIONADO
		else if(octi->pickedAnything == false ||
			(octi->pickedAnything && octi->idLastPick > 220 && octi->idLastPick < 229) ||
			(octi->pickedAnything && octi->idLastPick > 20 && octi->idLastPick < 28)){

				// Unhighlight do que ja estava
				if(octi->pickedAnything){
					octi->unhighlightId(octi->idLastPick);
					for(int i = 0; i < octi->idsReceived.size(); i++){
						octi->unhighlightId(octi->idsReceived[i]);
					}
				}

				// Highlight do Prong seleccionado
				octi->pickedAnything = true;
				octi->idLastPick = idpicado;
				octi->highlightId(idpicado); 

				// Envia mensagem para saber que pods pode meter highlight
				string mensagem = "11 ";
				mensagem += to_string(octi->turn);
				mensagem += " " + to_string(idpicado%10);
				cout << "[CHECK_ADD_PRONG] Enviou '" << mensagem << "'" << endl;
				sendMessage(mensagem.c_str());

				char* resposta = readMessage();
				cout << "[CHECK_ADD_PRONG] Resposta '" << resposta << "'" << endl;

				// Highlight dos ids que recebeu
				octi->idsReceived = divideStringEmInt(resposta);
				for(int i = 0; i < octi->idsReceived.size(); i++){
					cout << octi->idsReceived[i] << endl;
					octi->highlightId(octi->idsReceived[i]);
				}
		}
	}


	// ****************************************
	// UTILIZADOR CLICOU EM CELULA
	// ****************************************
	if(idpicado > 110 && idpicado < 178){
		cout << "[CELULA HANDLER] Cliclou em celula]"<<endl;
		if(octi->pickedAnything == false){
			octi->pickedAnything = false;
			octi->unhighlightAll();
			octi->idLastPick = -1;
		}
		// Jogador 1 vai mover peca
		else if(octi->pickedAnything == true && octi->pickedAnything && octi->idLastPick > 10 && octi->idLastPick < 18){
			bool isInGame = false;
			// verifica se a peca que clicou antes esta em jogo
			for(int i = 0; i < octi->getBoard()->Jogador1.size(); i++){
				if(octi->getBoard()->Jogador1.at(i)->getId()+10 == octi->idLastPick){
					isInGame = true;
					break;
				}
			}
			// Clicou em peca em jogo
			if(isInGame){
				bool valid = false;
				// Verifica se pode mover para a celula que clicou
				for(int i = 0; i < octi->idsReceived.size(); i++){
					if (idpicado == octi->idsReceived[i]){
						valid = true;
					}
				}
				if(valid){
					string mensagem;
					mensagem = "2 " + to_string(octi->idLastPick);
					mensagem += " ";

					int x=(idpicado-100)/10;
					int y=(idpicado-100)%10;
					mensagem += to_string(x);
					mensagem += " ";
					mensagem += to_string(y);

					sendMessage(mensagem.c_str());



					int lastx=octi->getBoard()->getXbyId(1,octi->idLastPick%10);

					int lasty=octi->getBoard()->getYbyId(1,octi->idLastPick%10);

					int incx=x-lastx;

					int incy=y-lasty;	


					mensagem += " ";
					mensagem += to_string(incx);
					mensagem += " ";
					mensagem += to_string(incy);


					octi->jogadas.push_back(mensagem);
					cout << "[MOVE_POD] INC X = " << incx << "; INCY = " << incy << ";" << endl;

					octi->movepod(1,octi->idLastPick,x,y,incx,incy,((XMLScene* )scene)->getScenePointer());	

					cout << "[MOVE_POD] '" << mensagem << "'" << endl;
					char* mensagem2 = readMessage();
					cout << "[MOVE_POD] Recebeu " << mensagem2 << endl;
					if(strcmp(mensagem2,"666") == 0){
						octi->setEnded(true);
						//sendMessage("100000");
					}


					// UNHIGLIGHT DE TUDO
					octi->unhighlightId(octi->idLastPick);
					for(int i = 0; i < octi->idsReceived.size(); i++){
						octi->unhighlightId(octi->idsReceived[i]);
					}

					// MUDA DE TURNO
					octi->pickedAnything = false;
					octi->idLastPick = -1;
					octi->turn = 2; // muda de turno

					cout << "----------------- Fim do Turno de 1 -------------------" << endl;
				}
				else{

					cout << "Jogada Invalida!" << endl;
				}
				// Clicou em peca que ta ao lado
			}
			else if(!isInGame){
				cout << "o que querias 1" << endl;

				// 3 IDPOD X Y (xi yi xf yf)
				string mensagem;
				mensagem = "3 " + to_string(octi->idLastPick);
				mensagem += " ";

				int x=(idpicado-100)/10;
				int y=(idpicado-100)%10;
				mensagem += to_string(x);
				mensagem += " ";
				mensagem += to_string(y);


				sendMessage(mensagem.c_str());
				mensagem += " ";

				//x inicial

				mensagem += to_string(octi->boardElements[octi->idLastPick]->getx()+50.0*1.0);
				mensagem += " ";
				//z inicial
				mensagem += to_string(octi->boardElements[octi->idLastPick]->getz()+50.0*1.0);
				mensagem += " ";
				//x final
				mensagem += to_string(octi->boardElements[idpicado]->getx()*1.0);
				mensagem += " ";
				mensagem += to_string(octi->boardElements[idpicado]->getz()*1.0);

				octi->jogadas.push_back(mensagem);

				octi->addpod(octi->idLastPick/10, octi->idLastPick%10, x,y);
				octi->graph_addPod(octi->idLastPick, idpicado, ((XMLScene*)scene)->getScenePointer());

				cout << "[ADD_POD] '" << mensagem << "'" << endl;
				readMessage();
				cout << "[ADD_POD] A logica nao respondeu nada\n";


				// UNHIGLIGHT DE TUDO
				octi->unhighlightId(octi->idLastPick);
				for(int i = 0; i < octi->idsReceived.size(); i++){
					octi->unhighlightId(octi->idsReceived[i]);
				}

				// MUDA DE TURNO
				octi->pickedAnything = false;
				octi->idLastPick = -1;
				octi->turn = 2; // muda de turno

				cout << "----------------- Fim do Turno de 1 -------------------" << endl;


			}
		}
		// Jogador 2 vai mover PEca
		else if(octi->pickedAnything == true && octi->pickedAnything && octi->idLastPick > 20 && octi->idLastPick < 28){
			bool isInGame = false;
			// verifica se a peca que clicou antes esta em jogo
			for(int i = 0; i < octi->getBoard()->Jogador2.size(); i++){
				if(octi->getBoard()->Jogador2.at(i)->getId()+20 == octi->idLastPick){
					isInGame = true;
					break;
				}
			}
			// Clicou em peca em jogo
			if(isInGame){
				bool valid = false;
				// Verifica se pode mover para a celula que clicou
				for(int i = 0; i < octi->idsReceived.size(); i++){
					if (idpicado == octi->idsReceived[i]){
						valid = true;
					}
				}
				if(valid){
					// Envia Info pa Mover POD
					// FORMATO : 2 IDPECA IDCELULA
					string mensagem;
					mensagem = "2 " + to_string(octi->idLastPick);
					mensagem += " ";

					int x=(idpicado-100)/10;
					int y=(idpicado-100)%10;

					mensagem += to_string(x);
					mensagem += " ";
					mensagem += to_string(y);



					sendMessage(mensagem.c_str());


					int lastx=octi->getBoard()->getXbyId(2,octi->idLastPick%10);
					int lasty=octi->getBoard()->getYbyId(2,octi->idLastPick%10);
					int incx=x-lastx;
					int incy=y-lasty;

					mensagem += " ";
					mensagem += to_string(incx);
					mensagem += " ";
					mensagem += to_string(incy);

					octi->jogadas.push_back(mensagem);


					cout << "[MOVE_POD] INC X = " << incx << "; INCY = " << incy << ";" << endl;
					octi->movepod(2,octi->idLastPick,x,y,incx,incy, ((XMLScene*)scene)->getScenePointer());

					//Knows increment

					cout << "[MOVE_POD] '" << mensagem << "'" << endl;

					char* mensagem2 = readMessage();
					cout << "[MOVE_POD] Recebeu " << mensagem2 << endl;
					if(strcmp(mensagem2,"666") == 0){
						octi->setEnded(true);
						//sendMessage("100000");
					}


					// UNHIGLIGHT DE TUDO
					octi->unhighlightId(octi->idLastPick);
					for(int i = 0; i < octi->idsReceived.size(); i++){
						octi->unhighlightId(octi->idsReceived[i]);
					}

					// MUDA DE TURNO
					octi->pickedAnything = false;
					octi->idLastPick = -1;
					octi->turn = 1; // muda de turno

					cout << "----------------- Fim do Turno de 2 -------------------" << endl;

				}
				else{

					cout << "Jogada Invalida!" << endl;
				}
			}
			else if(!isInGame){

				// 3 IDPOD X Y
				string mensagem;
				mensagem = "3 " + to_string(octi->idLastPick);
				mensagem += " ";

				int x=(idpicado-100)/10;
				int y=(idpicado-100)%10;
				mensagem += to_string(x);
				mensagem += " ";
				mensagem += to_string(y);

				sendMessage(mensagem.c_str());

				mensagem += " ";

				//x inicial

				mensagem += to_string(octi->boardElements[octi->idLastPick]->getx()+50.0*1.0);
				mensagem += " ";
				//z inicial
				mensagem += to_string(octi->boardElements[octi->idLastPick]->getz()+50.0*1.0);
				mensagem += " ";
				//x final
				mensagem += to_string(octi->boardElements[idpicado]->getx()*1.0);
				mensagem += " ";
				mensagem += to_string(octi->boardElements[idpicado]->getz()*1.0);

				octi->jogadas.push_back(mensagem);

				octi->addpod(octi->idLastPick/10, octi->idLastPick%10, x,y);
				octi->graph_addPod(octi->idLastPick, idpicado, ((XMLScene*)scene)->getScenePointer());


				cout << "[ADD_POD] '" << mensagem << "'" << endl;
				readMessage();
				cout << "[ADD_POD] A logica nao respondeu nada\n";


				// UNHIGLIGHT DE TUDO
				octi->unhighlightId(octi->idLastPick);
				for(int i = 0; i < octi->idsReceived.size(); i++){
					octi->unhighlightId(octi->idsReceived[i]);
				}

				// MUDA DE TURNO
				octi->pickedAnything = false;
				octi->idLastPick = -1;
				octi->turn = 1; // muda de turno

				cout << "----------------- Fim do Turno de 2 -------------------" << endl;

			}

		}
	}

	if(octi->getEnded()){

		Appearance* app = new Appearance();

		// GANHOU JOG 1
		if(octi->turn == 2){

			for(int i = 0; i < ((XMLScene*) scene)->getScenePointer()->appearancesComp.size(); i++){
				if( ((XMLScene*) scene)->getScenePointer()->appearancesComp[i]->getIdS() == "appJ1Venceu"){
					app = ((XMLScene*) scene)->getScenePointer()->appearancesComp[i];
					break;
				}
			}
		}
		// GANHOU JOG 2
		else if(octi->turn == 1 && octi->getDificuldade() == 0){
			Appearance* app;
			for(int i = 0; i < ((XMLScene*) scene)->getScenePointer()->appearancesComp.size(); i++){
				if( ((XMLScene*) scene)->getScenePointer()->appearancesComp[i]->getIdS() == "appJ2Venceu"){
					app = ((XMLScene*) scene)->getScenePointer()->appearancesComp[i];
					break;
				}
			}
		}
		// GANHOU COM
		else if(octi->turn == 1 && octi->getDificuldade() > 0){
			Appearance* app;
			for(int i = 0; i < ((XMLScene*) scene)->getScenePointer()->appearancesComp.size(); i++){
				if( ((XMLScene*) scene)->getScenePointer()->appearancesComp[i]->getIdS() == "appComputadorVenceu"){
					app = ((XMLScene*) scene)->getScenePointer()->appearancesComp[i];
					break;
				}
			}
		}

		// MOSTRA VENCEDOR
		((XMLScene*) scene)->getScenePointer()->menuVitoria->setAppearance(app);

		vector<Cameras*> aux = ((XMLScene*) scene)->getScenePointer()->camerasComp;
		for(unsigned int i= 0; i < aux.size(); i++){
			if(aux.at(i)->getid() == "camVencedor"){
				((XMLScene*) scene)->getScenePointer()->itActiveCamera = i;
				((XMLScene*) scene)->refreshCameras();
				break;
			}
		}
	}	

	



	//cout << "END " << octi->getEnded() << endl;

}

void TPinterface::initGUI()
{
	GLUI_Panel *painel1= addPanel("Accoes", 2);
	addButtonToPanel(painel1,"Anular Jogada",1);

	GLUI_Panel *painel2= addPanel("Cameras", 2);
	addButtonToPanel(painel2,"Rodar Camara",2);


	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("Configuracoes", 1);

	addColumnToPanel(varPanel);

	GLUI_RadioGroup * group1=addRadioGroupToPanel(varPanel,&(((XMLScene*) scene)->getScenePointer()->itActiveCamera),11);
	string cameraName;
	for(unsigned int i = 0; i < (((XMLScene*) scene)->getScenePointer()->camerasComp.size()); i++){
		cameraName = "Camera " + (((XMLScene*) scene)->getScenePointer()->camerasComp.at(i)->getid());
		addRadioButtonToGroup(group1,(char *)cameraName.c_str());
	}

}
void TPinterface::processGUI(GLUI_Control *ctrl)
{
	//printf ("GUI control id: %d\n  ",ctrl->user_id);

	if(ctrl->user_id == 11){
		((XMLScene*) scene)->refreshCameras();
	}

	if(ctrl->user_id == 1){
		if(octi->jogadas.size()>=1 && !((XMLScene*) scene)->doinganimations())
		{
			string toSend=octi->jogadas[octi->jogadas.size()-1];
			toSend="-1 "+toSend;
			sendMessage(toSend.c_str());
			readMessage();
			octi->undoPlay(((XMLScene*)scene)->getScenePointer());	

			if(octi->dificuldade == -1) octi->rotateCamera(((XMLScene*) scene)->getScenePointer(),octi->turn);


		}
	}

	if(ctrl->user_id == 2){
		cout << "ROTATE CAMERA!" << endl;
	}
}

void TPinterface::processPassiveMouseMoved (int x, int y){
	if(octi->turn == 2 && octi->dificuldade > 0 && !((XMLScene*) scene)->doinganimations()){
		octi->comTurn( ((XMLScene*) scene)->getScenePointer());
	}

}

void TPinterface::processKeyboard(unsigned char key, int x, int y)
{
	// Uncomment below if you would like to process the default keys (e.g. 's' for snapshot, 'Esc' for exiting, ...)
	CGFinterface::processKeyboard(key, x, y);

	switch(key)
	{
	case 't':
		{

			// This is an example of accessing the associated scene
			// To test, create the function toggleSomething in your scene to activate/deactivate something
			//((LightingScene *) scene)->toggleSomething();
			(((XMLScene*) scene)->getScenePointer()->switchTheme());
			break;
		}
	}
}