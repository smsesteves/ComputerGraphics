#include "TPinterface.h"
TPinterface::TPinterface(Game* game){
	this->octi = game;
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
	GLuint nselected;

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
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		clickHandler(selected, nselected);
	}
	else{
		printf("Nothing selected while picking \n");	
	}
}


void TPinterface::clickHandler(GLuint* selected, GLint nselected){
		cout << endl << "ClickHandler: " << octi->turn << endl;
		GLint idpicado;
		cout << "LAST PICK : " << octi->idLastPick << endl;
		cout << "IDS RECEIVED : " << endl;
		for(int i = 0; i < octi->idsReceived.size(); i++){
			cout << "[" << i << "] " << octi->idsReceived[i] << endl;
		}

		for (int i=0; i<nselected; i++){
			//printf("%d ",selected[i]);
			idpicado = selected[i];
			//printf("\n");
		}
		

		char id[256];
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
			else if(octi->pickedAnything && octi->idLastPick > 210 && octi->idLastPick < 218){
				bool valid = false;
				for(int i = 0; i < octi->idsReceived.size(); i++){
					if (idpicado == octi->idsReceived[i]){
						valid = true;
					}

				}
				if(valid){
					string mensagem;
					mensagem = "1 " + intToString(idpicado);
					int dir = octi->idLastPick % 10;
					mensagem += " ";
					mensagem += intToString(dir);
					sendMessage(mensagem.c_str());
					cout << "[ADD_PRONG] '" << mensagem << "'" << endl;

					readMessage();
					cout << "[ADD_PRONG] A logica nao respondeu nada\n";
					octi->addprong(1,idpicado,octi->getDir(dir));
					octi->unhighlightId(octi->idLastPick); // Unlight do PRONG
					//prongReferencia
					octi->boardElements[idpicado]->addChildren("prongReferenciaAzul");
					for(int i = 0; i < octi->idsReceived.size(); i++){
						octi->unhighlightId(octi->idsReceived[i]);
					}

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
			else if(octi->pickedAnything && octi->idLastPick > 220 && octi->idLastPick < 228){
				bool valid = false;
				for(int i = 0; i < octi->idsReceived.size(); i++){
					if (idpicado == octi->idsReceived[i]){
						valid = true;
					}
				}
				if(valid){
					string mensagem;
					mensagem = "1 " + intToString(idpicado);
					int dir = octi->idLastPick % 10;
					mensagem += " ";
					mensagem += intToString(dir);
					sendMessage(mensagem.c_str());
					cout << "[ADD_PRONG] '" << mensagem << "'" << endl;

					readMessage();
					cout << "[ADD_PRONG] A logica nao respondeu nada\n";

					octi->addprong(2,idpicado,octi->getDir(dir));
					octi->boardElements[idpicado]->addChildren("prongReferenciaVermelho");
					octi->unhighlightId(octi->idLastPick); // Unlight do PRONG
					for(int i = 0; i < octi->idsReceived.size(); i++){
						octi->unhighlightId(octi->idsReceived[i]);
					}

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
		if(idpicado > 210 && idpicado < 218){
			// TURNO ERRADO
			if(octi->turn == 2){
				octi->pickedAnything = false;
				octi->unhighlightAll();
				octi->idLastPick = -1;
				cout << "Nao pode clicar no Oct do adversario. Turno atual e 1\n";
			}
			// HIGHLIGHT DOS PODS POSSIVEIS - TEM OUTRO PRONG SELCCIONADO OU NAO TEM NADA SELECCIONADO
			else if(octi->pickedAnything == false || 
							(octi->pickedAnything && octi->idLastPick > 210 && octi->idLastPick < 218) ||
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
		if(idpicado > 220 && idpicado < 228){
			// TURNO ERRADO
			if(octi->turn == 1){
				octi->pickedAnything = false;
				octi->unhighlightAll();
				octi->idLastPick = -1;
				cout << "Nao pode clicar no Oct do adversario. Turno atual e 2\n";
			}
			// HIGHLIGHT DOS PODS POSSIVEIS - TEM OUTRO PRONG SELCCIONADO OU NAO TEM NADA SELECCIONADO
			else if(octi->pickedAnything == false ||
							(octi->pickedAnything && octi->idLastPick > 220 && octi->idLastPick < 228) ||
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
				bool valid = false;
				// Verifica se pode mover para a celula que clicou
				for(int i = 0; i < octi->idsReceived.size(); i++){
					if (idpicado == octi->idsReceived[i]){
						valid = true;
					}
				}
				if(valid){
					// TODO: move peca graf lado LAIG
					// RODO: move peca logica lado LAIG

					// Envia Info pa Mover POD
					// FORMATO : 3 IDPECA IDCELULA
					string mensagem;
					mensagem = "3 " + intToString(octi->idLastPick);
					mensagem += " ";
					mensagem += intToString(idpicado);
					sendMessage(mensagem.c_str());
					cout << "[MOVE_POD] '" << mensagem << "'" << endl;

					readMessage();
					cout << "[MOVE_POD] A logica nao respondeu nada\n";

					
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
					cout << "[MOVE_POD] Click Invalido\n";
				}
			}
			// Jogador 2 vai mover PEca
			else if(octi->pickedAnything == true && octi->pickedAnything && octi->idLastPick > 20 && octi->idLastPick < 28){
				bool valid = false;
				// Verifica se pode mover para a celula que clicou
				for(int i = 0; i < octi->idsReceived.size(); i++){
					if (idpicado == octi->idsReceived[i]){
						valid = true;
					}
				}
				if(valid){
					// TODO: move peca graf lado LAIG
					// RODO: move peca logica lado LAIG

					// Envia Info pa Mover POD
					// FORMATO : 3 IDPECA IDCELULA
					string mensagem;
					mensagem = "3 " + intToString(octi->idLastPick);
					mensagem += " ";
					mensagem += intToString(idpicado);
					sendMessage(mensagem.c_str());
					cout << "[MOVE_POD] '" << mensagem << "'" << endl;

					readMessage();
					cout << "[MOVE_POD] A logica nao respondeu nada\n";

					
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
					cout << "[MOVE_POD] Click Invalido\n";
				}
			}
		}
}

void TPinterface::initGUI()
{
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("Configuracoes", 1);
	int lightCounter = 0;

	string lightName;
	for(unsigned int i = 0; i < (((XMLScene*) scene)->getScenePointer()->lightsComp.size()); i++){
		lightName = "Luz " + (((XMLScene*) scene)->getScenePointer()->lightsComp.at(i)->getIdS());
		addCheckboxToPanel(varPanel, (char *) lightName.c_str() , &(((XMLScene*) scene)->getScenePointer()->lightsState[i]), i);
		cout << (char *)lightName.c_str() << " adicionada." << endl;
		lightName.clear();
	}
	
	addColumnToPanel(varPanel);
	
	GLUI_RadioGroup * group1=addRadioGroupToPanel(varPanel,&(((XMLScene*) scene)->getScenePointer()->itActiveCamera),11);
	string cameraName;
	for(unsigned int i = 0; i < (((XMLScene*) scene)->getScenePointer()->camerasComp.size()); i++){
		cameraName = "Camera " + (((XMLScene*) scene)->getScenePointer()->camerasComp.at(i)->getid());
		addRadioButtonToGroup(group1,(char *)cameraName.c_str());
	}

	addColumnToPanel(varPanel);
	GLUI_RadioGroup * group2=addRadioGroupToPanel(varPanel,&(((XMLScene*) scene)->getScenePointer()->mode),12);
	addRadioButtonToGroup(group2,"Fill");
	addRadioButtonToGroup(group2,"Line");
	addRadioButtonToGroup(group2,"Point");

	GLUI_Panel *animPanel= addPanel("Animacoes", 1);
	char animationName[100];
	char nova[100];
	for(unsigned int i = 0; i < (((XMLScene*) scene)->getScenePointer()->animationsComp.size()); i++){

		itoa(i,&animationName[0],10);
		strcpy(nova,"Animacao ");
		strcat(nova,animationName);
	
		addButtonToPanel(animPanel,(char *)nova,i+12+(((XMLScene*) scene)->getScenePointer()->camerasComp.size()));
	}
	
	// You could also pass a reference to a variable from the scene class, if public
}
void TPinterface::processGUI(GLUI_Control *ctrl)
{
	//printf ("GUI control id: %d\n  ",ctrl->user_id);

	if(ctrl->user_id < 10){
		((XMLScene*) scene)->setLightState(ctrl->user_id);
		
	}
	
	if(ctrl->user_id == 11){
		((XMLScene*) scene)->refreshCameras();
	}
	
	if(ctrl->user_id >= (((XMLScene*) scene)->getScenePointer()->camerasComp.size())){
	
		//cout << "pressed : " << ctrl->user_id << endl;
		//cout << "cameras size: " << (((XMLScene*) scene)->getScenePointer()->camerasComp.size()) << endl;
		int itAnimation = ctrl->user_id -  (((XMLScene*) scene)->getScenePointer()->camerasComp.size()) - 12;
		cout << itAnimation << endl;
		((XMLScene*) scene)->getScenePointer()->initInterfaceAnim(itAnimation);
	}

}