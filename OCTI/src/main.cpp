#include <iostream>
#include "socket.h"
#include <vector>
#include "Game.h"

int main()
{

	criarSocket();
		
	Game g1=Game();
	g1.createBoard();
		
	while(1)
	{
		char* recebido = leMensagem();
		vector<int> valoresRecebidos = divideStringEmInt(recebido);
		
		string aEnviar = g1.executaOperacao(valoresRecebidos);
		//g1.displayBoard();

		enviaMensagem(aEnviar.c_str());
		cout << "Enviou '" << aEnviar << "'"<< endl;
		
		aEnviar.clear();
	}
	system("pause");

	return 0;
}