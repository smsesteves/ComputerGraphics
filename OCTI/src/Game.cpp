#include "Game.h"

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


string Game::executaOperacao(vector<int> valoresRecebidos){
	if(valoresRecebidos.size() < 1){
		cout << "Operacao Invalida" << endl;
	}
	int operacao = valoresRecebidos[0];
	string resposta;
	string dir;
	int d;
	int player;
	int pod;
	int casa;
	int x,y;
	switch(operacao)
	{
	case 1: 


		player = valoresRecebidos[1]/10;

		pod = valoresRecebidos[1]%10;

		d = valoresRecebidos[2];	

		switch(d)
		{
		case 1: dir="s";break;
		case 2:dir="se";break;
		case 3:dir="e";break;
		case 4:dir="ne";break;
		case 5:dir="n";break;
		case 6:dir="no";break;
		case 7:dir="o";break;
		case 8:dir="so";break;
		}


		addprong(player,pod,dir);
		//possible switch
		break;
	case 2:
		player = valoresRecebidos[1]/10;
		pod = valoresRecebidos[1]%10;
		x = valoresRecebidos[2];
		y = valoresRecebidos [3];
		movepod(player,pod,x,y);
		break;
	case 3:
		player = valoresRecebidos[1]/10;
		pod = valoresRecebidos[1]%10;
		x = valoresRecebidos[2];
		y = valoresRecebidos[3];
		addpod(player,pod,x,y);
		break;
	case 10:
		player = valoresRecebidos[1]/10;
		pod = valoresRecebidos[1]%10;
		cout << "Entrou com" << player << " e " << pod << endl;
		resposta = checkMovimentos(player,pod);
		cout << resposta << endl;
		break;


	case 11:
		player = valoresRecebidos[1];
		d = valoresRecebidos[2];

		switch(d)
		{
		case 1: dir="s";break;
		case 2:dir="se";break;
		case 3:dir="e";break;
		case 4:dir="ne";break;
		case 5:dir="n";break;
		case 6:dir="no";break;
		case 7:dir="o";break;
		case 8:dir="so";break;
		}

		resposta = checkProngs(player,dir);
		cout << resposta << endl;
		break;

	case 12:
		player = valoresRecebidos[1];
		d = valoresRecebidos[1];

	case -1:
		removeSomeCenas(valoresRecebidos);

	}



	return resposta;
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

bool Game::movepod(int player, int podnumber, int x,int y)
{

	if(player==1)
	{
		for(int i=0;i<gameBoard->getJogador1Size();i++)
		{
			if(gameBoard->getJogador1PodAt(i)->getId()==podnumber)
			{


				Pod * aux = gameBoard->getJogador1PodAt(i);

				aux->setX(x);
				aux->setY(y);

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
				Pod * aux = gameBoard->getJogador2PodAt(i);
				aux->setX(x);
				aux->setY(y);
				return true;
			}
		}
	}
	return false;
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



string Game::checkMovimentos(int player,int id)
{
	string res;
	vector<int> resultados;
	int number=0;
	if(player==1)
	{
		bool podfound=false;
		int size=gameBoard->getJogador1Size();
		for(int i=0;i<size;i++)
		{
			Pod * aux=gameBoard->getJogador1PodAt(i);
			if(aux->getId()==id)
			{
				podfound=true;
				int sizedir= aux->getDirsSize();
				for(int j=0;j<sizedir;j++)
				{
					if(aux->getDirsAt(j)->getDir()=="n")
					{
						if(aux->getX()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && aux->getY()==gameBoard->getJogador1PodAt(z)->getY())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && aux->getY()==gameBoard->getJogador2PodAt(z)->getY())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()+1)*10)+aux->getY());
							}
						}
					}
					else if(aux->getDirsAt(j)->getDir()=="s")
					{
						if(aux->getX()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && aux->getY()==gameBoard->getJogador1PodAt(z)->getY())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && aux->getY()==gameBoard->getJogador2PodAt(z)->getY())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()-1)*10)+aux->getY());
							}	
						}
					}
					else if(aux->getDirsAt(j)->getDir()=="e")
					{
						if(aux->getY()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1 && aux->getX()==gameBoard->getJogador1PodAt(z)->getX())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1 && aux->getX()==gameBoard->getJogador2PodAt(z)->getX())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getX()*10)+(aux->getY()-1));
							}	
						}

					}
					else if(aux->getDirsAt(j)->getDir()=="o")
					{
						if(aux->getY()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1 && aux->getX()==gameBoard->getJogador1PodAt(z)->getX())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1 && aux->getX()==gameBoard->getJogador2PodAt(z)->getX())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getX()*10)+(aux->getY()+1));
							}	
						}	

					}
					else if(aux->getDirsAt(j)->getDir()=="ne")
					{
						if(aux->getX()<=6 && aux->getY()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()+1)*10)+(aux->getY()-1));
							}
						}

					}
					else if(aux->getDirsAt(j)->getDir()=="no")
					{
						if(aux->getX()<=6 && aux->getY()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()+1)*10)+(aux->getY()+1));
							}
						}

					}
					else if(aux->getDirsAt(j)->getDir()=="se")
					{
						if(aux->getX()>=2 && aux->getY()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()-1)*10)+(aux->getY()-1));
							}	
						}


					}
					else if(aux->getDirsAt(j)->getDir()=="so")
					{
						if(aux->getX()>=2 && aux->getY()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()-1)*10)+(aux->getY()+1));
							}	
						}



					}
				}
				break;
			}

		}

		if(!podfound)
		{

			cout<<"NAO ENCONTROU TURNO 1"<<endl;

			bool encontra1=false;
			bool encontra2=false;
			bool encontra3=false;
			int sizeJogador1=gameBoard->getJogador1Size();
			for(int i=0;i<sizeJogador1;i++)
			{
				if(gameBoard->getJogador1PodAt(i)->getX()==2)
				{
					if(gameBoard->getJogador1PodAt(i)->getY()==2)
					{
						encontra1=true;
					}
					else if(gameBoard->getJogador1PodAt(i)->getY()==4)
					{
						encontra2=true;
					}
					else if(gameBoard->getJogador1PodAt(i)->getY()==6)
					{
						encontra3=true;
					}


				}


			}
			if(!encontra1)
			{
				resultados.push_back(100+2*10+2);
			}
			if(!encontra2)
			{
				resultados.push_back(100+2*10+4);
			}
			if(!encontra3)
			{
				resultados.push_back(100+2*10+6);
			}
		}

	}
	else
	{


		bool podfound=false;
		int size=gameBoard->getJogador2Size();
		for(int i=0;i<size;i++)
		{
			Pod * aux=gameBoard->getJogador2PodAt(i);
			if(aux->getId()==id)
			{
				podfound=true;
				int sizedir= aux->getDirsSize();
				for(int j=0;j<sizedir;j++)
				{
					if(aux->getDirsAt(j)->getDir()=="n")
					{


						if(aux->getX()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && aux->getY()==gameBoard->getJogador1PodAt(z)->getY())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && aux->getY()==gameBoard->getJogador2PodAt(z)->getY())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()-1)*10)+(aux->getY()));
							}
						}
					}
					else if(aux->getDirsAt(j)->getDir()=="s")
					{
						if(aux->getX()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && aux->getY()==gameBoard->getJogador1PodAt(z)->getY())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && aux->getY()==gameBoard->getJogador2PodAt(z)->getY())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()+1)*10)+aux->getY());
							}	
						}
					}
					else if(aux->getDirsAt(j)->getDir()=="e")
					{
						if(aux->getY()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1 && aux->getX()==gameBoard->getJogador1PodAt(z)->getX())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1 && aux->getX()==gameBoard->getJogador2PodAt(z)->getX())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getX()*10)+(aux->getY()+1));
							}	
						}

					}
					else if(aux->getDirsAt(j)->getDir()=="o")
					{
						if(aux->getY()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1 && aux->getX()==gameBoard->getJogador1PodAt(z)->getX())
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1 && aux->getX()==gameBoard->getJogador2PodAt(z)->getX())
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getX()*10)+(aux->getY()-1));
							}	
						}

					}
					else if(aux->getDirsAt(j)->getDir()=="ne")
					{

						if(aux->getX()>=2 && aux->getY()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()-1)*10)+(aux->getY()+1));
							}	
						}


					}
					else if(aux->getDirsAt(j)->getDir()=="no")
					{
						if(aux->getX()>=2 && aux->getY()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()-1)*10)+(aux->getY()-1));
							}	
						}

					}
					else if(aux->getDirsAt(j)->getDir()=="se")
					{
						if(aux->getX()<=6 && aux->getY()<=6)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()+1)*10)+(aux->getY()+1));
							}
						}

					}
					else if(aux->getDirsAt(j)->getDir()=="so")
					{
						if(aux->getX()<=6 && aux->getY()>=2)
						{
							int size2=gameBoard->getJogador1Size();
							int size3=gameBoard->getJogador2Size();


							//Pecas do 1
							bool encontra=false;
							for(int z=0;z<size2;z++)
							{
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+((aux->getX()+1)*10)+(aux->getY()-1));
							}
						}

					}
				}
				break;
			}

		}	

		if(!podfound)
		{


			cout<<"NAO ENCONTROU TURNO 2"<<endl;

			bool encontra1=false;
			bool encontra2=false;
			bool encontra3=false;
			int sizeJogador2=gameBoard->getJogador2Size();
			for(int i=0;i<sizeJogador2;i++)
			{
				if(gameBoard->getJogador2PodAt(i)->getX()==6)
				{
					if(gameBoard->getJogador2PodAt(i)->getY()==2)
					{
						encontra1=true;
					}
					else if(gameBoard->getJogador2PodAt(i)->getY()==4)
					{
						encontra2=true;
					}
					else if(gameBoard->getJogador2PodAt(i)->getY()==6)
					{
						encontra3=true;
					}


				}


			}
			if(!encontra1)
			{
				resultados.push_back(100+6*10+2);
			}
			if(!encontra2)
			{
				resultados.push_back(100+6*10+4);
			}
			if(!encontra3)
			{
				resultados.push_back(100+6*10+6);
			}
		}


	}
	if(resultados.size()>0)
		return criastring(resultados);
	else
		return "-1";
}

string Game::checkProngs(int player, string dir)
{
	vector<int> res;
	if(player==1)
	{
		for(int i=0;i<gameBoard->getJogador1Size();i++)
		{
			Pod* aux=gameBoard->getJogador1PodAt(i);

			bool encontra=false;
			for(int j=0;j<aux->getDirsSize();j++)
			{
				if(aux->getDirsAt(j)->getDir()==dir)
				{
					encontra=true;
					break;
				}
			}
			if(!encontra)
			{
				res.push_back(aux->getId()+10);
			}
		}

	}
	else
	{
		for(int i=0;i<gameBoard->getJogador2Size();i++)
		{
			Pod* aux=gameBoard->getJogador2PodAt(i);

			bool encontra=false;
			for(int j=0;j<aux->getDirsSize();j++)
			{
				if(aux->getDirsAt(j)->getDir()==dir)
				{
					encontra=true;
					break;
				}
			}
			if(!encontra)
			{
				res.push_back(aux->getId()+20);
			}
		}

	}
	return criastring(res);
}

string Game::checkandAdd(int player, int id)
{
	vector<int> resultado;
	if(player==1)
	{

		resultado.push_back(122);
		resultado.push_back(124);
		resultado.push_back(126);
		int size=gameBoard->getJogador1Size();
		for(int i=0;i<size;i++)
		{
			if(gameBoard->getJogador1PodAt(i)->getX() == 2 && (gameBoard->getJogador1PodAt(i)->getY()==2 || gameBoard->getJogador1PodAt(i)->getY()==4 || gameBoard->getJogador1PodAt(i)->getY()==6))
			{

				for(int z=0;z<resultado.size();z++)
				{
					if(resultado[i] == 100+(gameBoard->getJogador1PodAt(i)->getX()*10)+gameBoard->getJogador1PodAt(i)->getY())
					{
						resultado.erase(resultado.begin()+i);
					}
				}
			}
		}

	}
	else
	{

		resultado.push_back(162);
		resultado.push_back(164);
		resultado.push_back(166);
		int size=gameBoard->getJogador2Size();
		for(int i=0;i<size;i++)
		{
			if(gameBoard->getJogador2PodAt(i)->getX() == 2 && (gameBoard->getJogador2PodAt(i)->getY()==2 || gameBoard->getJogador2PodAt(i)->getY()==4 || gameBoard->getJogador2PodAt(i)->getY()==6))
			{

				for(int z=0;z<resultado.size();z++)
				{
					if(resultado[i] == 100+(gameBoard->getJogador2PodAt(i)->getX()*10)+gameBoard->getJogador2PodAt(i)->getY())
					{
						resultado.erase(resultado.begin()+i);
					}
				}

			}
		}

	}

	return criastring(resultado);
}


Board* Game::getBoard()
{
	return gameBoard;
}


void Game::processaDir(Pod* aux,string dir,int player)
{
	if((dir=="n" && player==2) || (dir=="s" && player==1))
	{
		aux->decX();
	}
	else if((dir=="s" && player==2) ||(dir=="n" && player==1) )
	{
		aux->incX();
	}
	else if((dir=="e" && player ==2) || (dir=="o" && player==1))
	{
		aux->incY();
	}
	else if((dir=="o" && player==2) || (dir=="e" && player==1))
	{
		aux->decY();
	}
	else if((dir=="ne" && player ==2)|| (dir=="so" && player==1))
	{
		aux->decX();
		aux->incY();
	}
	else if((dir=="no" && player ==2)|| (dir=="se" && player==1))
	{
		aux->decX();
		aux->decY();
	}
	else if((dir=="se" && player ==2)|| (dir=="no" && player==1))
	{
		aux->incX();
		aux->incY();
	}
	else if((dir=="so" && player ==2)|| (dir=="ne" && player==1))
	{
		aux->incX();
		aux->decY();
	}
}

void Game::removeSomeCenas(vector<int> valores)
{
	switch(valores[1])
	{
	case 1: removeProng(valores[2]/10,valores[2]%10,valores[3]); break;//removeProng
	case 2: unmovePod(valores[2]/10,valores[2]%10, valores[5],valores[6]); break;//remove modePod
	case 3: unaddPod(valores[2]/10,valores[2]%10);break;//anula pod
	}

}

void Game::unmovePod(int player, int podnumber, int incx, int incy)
{

	if(player==1)
	{
		for(int i=0;i<gameBoard->getJogador1Size();i++)
		{
			if(gameBoard->getJogador1PodAt(i)->getId()==podnumber)
			{
				gameBoard->getJogador1PodAt(i)->setX(gameBoard->getJogador1PodAt(i)->getX()-incx);
				gameBoard->getJogador1PodAt(i)->setY(gameBoard->getJogador1PodAt(i)->getY()-incy);

			}

		}
	}
	else
	{
		for(int i=0;i<gameBoard->getJogador2Size();i++)
		{
			if(gameBoard->getJogador2PodAt(i)->getId()==podnumber)
			{
				gameBoard->getJogador2PodAt(i)->setX(gameBoard->getJogador2PodAt(i)->getX()-incx);
				gameBoard->getJogador2PodAt(i)->setY(gameBoard->getJogador2PodAt(i)->getY()-incy);
			}

		}

	}




}



void Game::removeProng(int player, int podnumber, int s)
{
	string dir;
	if(player==1)
	{
		for(int i=0;i<gameBoard->getJogador1Size();i++)
		{
			if(gameBoard->getJogador1PodAt(i)->getId()==podnumber)
			{
				switch(s)
				{
				case 1:dir="s";break;
				case 2:dir="se";break;
				case 3:dir="e";break;
				case 4:dir="ne";break;
				case 5:dir="n";break;
				case 6:dir="no";break;
				case 7:dir="o";break;
				case 8:dir="so";break;
				}
				gameBoard->getJogador1PodAt(i)->removeProng(dir);
			}

		}
	}
	else
	{
		for(int i=0;i<gameBoard->getJogador2Size();i++)
		{
			if(gameBoard->getJogador2PodAt(i)->getId()==podnumber)
			{
				switch(s)
				{
				case 1:dir="s";break;
				case 2:dir="se";break;
				case 3:dir="e";break;
				case 4:dir="ne";break;
				case 5:dir="n";break;
				case 6:dir="no";break;
				case 7:dir="o";break;
				case 8:dir="so";break;
				}
				gameBoard->getJogador2PodAt(i)->removeProng(dir);
			}

		}

	}


}

void Game::unaddPod(int player,int podnumber)
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



bool Game::checkcomprong()
{
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		if(gameBoard->getJogador2PodAt(i)->getDirsSize()!=8)
		{
			return true;
		}

	}
	return false;
}
bool Game::checkcommove()
{
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		if(gameBoard->getJogador2PodAt(i)->getDirsSize()!=0)
		{
			if(getHousesToMove(gameBoard->getJogador2PodAt(i)->getId()).size()>0)
			{
				return true;
			}
		}

	}
	return false;

}
bool Game::checkcomadd()
{
	bool encontra1=false;
	bool encontra2=false;
	bool encontra3=false;
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		if(gameBoard->getJogador2PodAt(i)->getX()==6)
		{
			if(gameBoard->getJogador2PodAt(i)->getY()==2)
			{
				encontra1=true;
			}
			else if(gameBoard->getJogador2PodAt(i)->getY()==4)
			{
				encontra2=true;
			}
			else if(gameBoard->getJogador2PodAt(i)->getY()==6)
			{
				encontra3=true;
			}


		}


	}
	if(!encontra1)
	{

		return true;
	}else if(!encontra2)
	{
		return true;
	}else if(!encontra3)
	{
		return true;
	}else
	{
		return false;
	}
	return false;

}

vector<int> Game::getPodsToAddProng()
{
	vector<int> res;
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		if(gameBoard->getJogador2PodAt(i)->getDirsSize()!=8)
		{
			res.push_back(gameBoard->getJogador2PodAt(i)->getId());
		}

	}
	return res;

}


vector<int> Game::getDirsToAddProng(int pod)
{
	vector<string>::iterator it;
	vector<string> auxiliar;
	auxiliar.push_back("n");
	auxiliar.push_back("ne");
	auxiliar.push_back("no");
	auxiliar.push_back("o");
	auxiliar.push_back("e");
	auxiliar.push_back("so");
	auxiliar.push_back("se");
	auxiliar.push_back("s");

	vector<int> res;
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{

		if(gameBoard->getJogador2PodAt(i)->getId()==pod)
		{
			Pod* aux = gameBoard->getJogador2PodAt(i);
			int sizedir= aux->getDirsSize();
			for(int j=0;j<sizedir;j++)
			{
				if(aux->getDirsAt(j)->getDir()=="n")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"n");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="no")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"no");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="ne")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"ne");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="s")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"s");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="so")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"so");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="se")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"se");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="e")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"e");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="o")
				{
					it=find(auxiliar.begin(),auxiliar.end(),"o");
					if(it!=auxiliar.end())
					{
						auxiliar.erase(it);
					}
				}
			}
			break;
		}
	}

	for(int i=0;i<auxiliar.size();i++)
	{

		if(auxiliar[i]=="n") res.push_back(5);
		else if(auxiliar[i]=="ne")res.push_back(4);
		else if(auxiliar[i]=="no")res.push_back(6);
		else if(auxiliar[i]=="o")res.push_back(7);
		else if(auxiliar[i]=="e")res.push_back(3);
		else if(auxiliar[i]=="so")res.push_back(8);
		else if(auxiliar[i]=="se")res.push_back(2);
		else if(auxiliar[i]=="s")res.push_back(1);


	}

	return res;
}


vector<int> Game::getPodsToAdd()
{
	vector<int> res;
	res.push_back(1);
	res.push_back(2);
	res.push_back(3);
	res.push_back(4);
	res.push_back(5);
	res.push_back(6);
	res.push_back(7);

	vector<int>::iterator it;
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		it=find(res.begin(),res.end(),gameBoard->getJogador2PodAt(i)->getId());
		res.erase(it);
	}

	return res;

}

vector<int> Game::getOctiPlaces()
{

	bool encontra1=false;
	bool encontra2=false;
	bool encontra3=false;

	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		if(gameBoard->getJogador2PodAt(i)->getX()==6)
		{
			if(gameBoard->getJogador2PodAt(i)->getY()==2)
			{
				encontra1=true;
			}
			else if(gameBoard->getJogador2PodAt(i)->getY()==4)
			{
				encontra2=true;
			}
			else if(gameBoard->getJogador2PodAt(i)->getY()==6)
			{
				encontra3=true;
			}
		}
	}

	vector<int> resultados;
	if(!encontra1)
	{
		resultados.push_back(62);
	}

	if(!encontra2)
	{
		resultados.push_back(64);
	}
	if(!encontra3)
	{
		resultados.push_back(66);
	}
	return resultados;
}


vector<int> Game::getPodsWithProng()
{
	vector<int> res;
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		if((gameBoard->getJogador2PodAt(i)->getDirsSize()!=0) && (getHousesToMove(gameBoard->getJogador2PodAt(i)->getId()).size()>0))
		{
			//verificar as dirs ocup
			res.push_back(gameBoard->getJogador2PodAt(i)->getId());
		}

	}
	return res;
}


vector<int> Game::getHousesToMove(int podnumber)
{
	vector<int> resultados;
	for(int i=0;i<gameBoard->getJogador2Size();i++)
	{
		if(gameBoard->getJogador2PodAt(i)->getId()==podnumber)
		{
			//percorrer dirs
			Pod* aux = gameBoard->getJogador2PodAt(i);
			int sizedir= aux->getDirsSize();


			for(int j=0;j<sizedir;j++)
			{
				if(aux->getDirsAt(j)->getDir()=="n")
				{
					if(aux->getX()>=2)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && aux->getY()==gameBoard->getJogador1PodAt(z)->getY())
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && aux->getY()==gameBoard->getJogador2PodAt(z)->getY())
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back(((aux->getX()-1)*10)+(aux->getY()));
						}
					}
				}
				else if(aux->getDirsAt(j)->getDir()=="no")
				{
					if(aux->getX()>=2 && aux->getY()>=2)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back(((aux->getX()-1)*10)+(aux->getY()-1));
						} 
					}

				}
				else if(aux->getDirsAt(j)->getDir()=="o")
				{
					if(aux->getY()>=2)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1 && aux->getX()==gameBoard->getJogador1PodAt(z)->getX())
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1 && aux->getX()==gameBoard->getJogador2PodAt(z)->getX())
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back((aux->getX()*10)+(aux->getY()-1));
						} 
					}

				}
				else if(aux->getDirsAt(j)->getDir()=="so")
				{
					if(aux->getX()<=6 && aux->getY()>=2)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back(((aux->getX()+1)*10)+(aux->getY()-1));
						}
					}

				}
				else if(aux->getDirsAt(j)->getDir()=="s")
				{
					if(aux->getX()<=6)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && aux->getY()==gameBoard->getJogador1PodAt(z)->getY())
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && aux->getY()==gameBoard->getJogador2PodAt(z)->getY())
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back(((aux->getX()+1)*10)+aux->getY());
						} 
					}

				}
				else if(aux->getDirsAt(j)->getDir()=="se")
				{
					if(aux->getX()<=6 && aux->getY()<=6)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back(((aux->getX()+1)*10)+(aux->getY()+1));
						}
					}

				}
				else if(aux->getDirsAt(j)->getDir()=="e")
				{
					if(aux->getY()<=6)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1 && aux->getX()==gameBoard->getJogador1PodAt(z)->getX())
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1 && aux->getX()==gameBoard->getJogador2PodAt(z)->getX())
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back((aux->getX()*10)+(aux->getY()+1));
						} 
					}

				}
				else if(aux->getDirsAt(j)->getDir()=="ne")
				{
					if(aux->getX()>=2 && aux->getY()<=6)
					{
						int size2=gameBoard->getJogador1Size();
						int size3=gameBoard->getJogador2Size();


						//Pecas do 1
						bool encontra=false;
						for(int z=0;z<size2;z++)
						{
							if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
							{
								encontra=true;
							}
						}
						//Pecas do 2
						for(int z=0;z<size3;z++)
						{
							if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1 && gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
							{
								encontra=true;
							}
						}

						if(!encontra)
						{
							resultados.push_back(((aux->getX()-1)*10)+(aux->getY()+1));
						} 
					}
				}


			}
		}

	}
	return resultados;

}