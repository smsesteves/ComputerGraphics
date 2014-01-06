#include <iostream>
#include "socket.h"
#include <vector>
#include "Game.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main()
{

	criarSocket();
	Game g1=Game();
	g1.createBoard();
	char* recebido;
	vector<int> valoresRecebidos;

	recebido=leMensagem();
	cout << "P: " << recebido << endl;

	int dificuldade;

	if(strcmp(recebido,"PP")==0)
	{
		dificuldade = -1;
		enviaMensagem("recebidopp");
	}
	else if(strcmp(recebido,"PC")==0)
	{
		enviaMensagem("recebidopc");
		srand ((int)(time(NULL)));
		recebido=leMensagem();
		cout << "DIFICULDADE: " << recebido << endl;
		dificuldade=divideStringEmInt(recebido)[0];
		enviaMensagem("recebidodif");
	}
	
	bool entrou = false;
	int count=0;
	while(1)
	{

		//char recebido2[256];
		//fgets(recebido2, sizeof(recebido2), stdin);
		recebido = leMensagem();
		cout << "RECEBEU : '" << recebido << endl;

		valoresRecebidos = divideStringEmInt(recebido);
		string aEnviar = g1.executaOperacao(valoresRecebidos);
		//g1.displayBoard();

		if(g1.getBoard()->checkend() && valoresRecebidos[0]==2)
		{
			aEnviar="666";
			g1=Game();
			g1.createBoard();
			entrou = true;

		}
		cout<<aEnviar<<endl;
		enviaMensagem(aEnviar.c_str());
		cout << "Enviou '" << aEnviar << "'"<< endl;

		aEnviar.clear();


		string toSend;

		//TODO: nao possibilidade 
		if(dificuldade != -1 && (valoresRecebidos[0] == 1 || valoresRecebidos[0] == 2 || valoresRecebidos[0] == 3) && !entrou){
			char* recebido2=leMensagem();

			cout << "PRIMEIRA RECECAO: " << recebido2 << endl;
			
			bool one=g1.checkcomprong();
			bool two=g1.checkcommove();
			bool three=g1.checkcomadd();

			vector<int>possibilidades; 

			if(one==true)
			{
				possibilidades.push_back(1);
			}
			if(two==true)
			{
				possibilidades.push_back(2);

			}
			if(three==true)
			{
				possibilidades.push_back(3);
			}

			int first=geraRandom(possibilidades);

			int second;
			int third;
			//int x;
			//int y;
			vector<int> possibilidades2;
			vector<int> possibilidades3;
			vector<int> resultados;
			resultados.push_back(first);
			switch(first)
			{
			case 1: 
				possibilidades2 = g1.getPodsToAddProng();
				second=geraRandom(possibilidades2);
				resultados.push_back(second+20);
				possibilidades3 = g1.getDirsToAddProng(second);
				third=geraRandom(possibilidades3);
				resultados.push_back(third);
				toSend=criastring(resultados);
				break;
			case 2: //pode move pod        || IDPECA(2) X Y
				possibilidades2 = g1.getPodsWithProng();
				second=geraRandom(possibilidades2);
				possibilidades3 = g1.getHousesToMove(second);
				resultados.push_back(second+20);
				third=geraRandom(possibilidades3);
				resultados.push_back(third/10);
				resultados.push_back(third%10);
				toSend=criastring(resultados);
				break;
			case 3: //pod adicionar pod    || IDPECA(2) X Y
				possibilidades2 = g1.getPodsToAdd();
				second=geraRandom(possibilidades2);
				resultados.push_back(second+20);
				possibilidades3 = g1.getOctiPlaces();
				third=geraRandom(possibilidades3);
				resultados.push_back(third/10);
				resultados.push_back(third%10);
				toSend=criastring(resultados);
				break;
			}
			//system("cls");
			enviaMensagem(toSend.c_str());
			cout<<"O COM SUGERE:"<<toSend.c_str()<<endl;

			if(first==2){
				string aEnviar2 = "";
				if(g1.getBoard()->checkend())
				{
					aEnviar2="666";
					
					g1=Game();
					g1.createBoard();
					entrou = false;
				}
				enviaMensagem(aEnviar2.c_str());
			}
			valoresRecebidos = divideStringEmInt(toSend.c_str());
			aEnviar = g1.executaOperacao(valoresRecebidos);
		}
		//g1.displayBoard();
		//count++;
	}




	system("pause");

	return 0;
}