#include <iostream>
#include "socket.h"
#include <vector>
#include "Game.h"


int main()
{

	criarSocket();
	Game g1=Game();
	g1.createBoard();
	char* recebido;
	vector<int> valoresRecebidos;
	while(1)
	{
		
		//char recebido2[256];
		//fgets(recebido2, sizeof(recebido2), stdin);
		recebido = leMensagem();
		valoresRecebidos = divideStringEmInt(recebido);
		
		string aEnviar = g1.executaOperacao(valoresRecebidos);
		g1.displayBoard();

		if(g1.getBoard()->checkend() && valoresRecebidos[0]==2)
		{
			aEnviar="666";
			//g1=Game();
			//g1.createBoard();
		}
		cout<<aEnviar<<endl;
		enviaMensagem(aEnviar.c_str());
		cout << "Enviou '" << aEnviar << "'"<< endl;
		
		aEnviar.clear();
	}
	

	system("pause");

	return 0;
}