#include <iostream>
#include "socket.h"
#include <vector>
#include "Game.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main()
{

	//criarSocket();
	Game g1=Game();
	g1.createBoard();
	char* recebido;
	vector<int> valoresRecebidos;

	/*recebido=leMensagem();

	int dificuldade;

	if(strcmp(recebido,"pp")==0)
	{

	}else if(strcmp(recebido,"pcom")==0)
	{
	srand (time(NULL));
	recebido=leMensagem();
	dificuldade=divideStringEmInt(recebido)[0];
	}
	*/
	int count=0;
	while(1)
	{

		char recebido2[256];
		fgets(recebido2, sizeof(recebido2), stdin);
		//recebido = leMensagem();





		valoresRecebidos = divideStringEmInt(recebido2);
		string aEnviar = g1.executaOperacao(valoresRecebidos);
		g1.displayBoard();

		if(g1.getBoard()->checkend() && valoresRecebidos[0]==2)
		{
			aEnviar="666";
			//g1=Game();
			//g1.createBoard();
		}
		cout<<aEnviar<<endl;
		//enviaMensagem(aEnviar.c_str());
		cout << "Enviou '" << aEnviar << "'"<< endl;

		aEnviar.clear();







		string toSend;

		//TODO: nao possibilidade 
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
		if(count==12){
		printf("");
		}
		int first=geraRandom(possibilidades);

		int second;
		int third;
		int x;
		int y;
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
		system("cls");
		cout<<"O COM SUGERE:"<<toSend.c_str()<<endl;

		valoresRecebidos = divideStringEmInt(toSend.c_str());
		aEnviar = g1.executaOperacao(valoresRecebidos);
		g1.displayBoard();
		count++;
	}




	system("pause");

	return 0;
}