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
		casa = valoresRecebidos[2];
		addpod(player,pod,casa);
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
				for(int j=0;j<gameBoard->getJogador1PodAt(i)->getDirsSize();j++)
				{

						Pod * aux = gameBoard->getJogador2PodAt(i);
						
						aux->setX(x);
						aux->setY(y);

						return true;
					
				}
				return false;
			}
		}
	
	}
	else
	{
		for(int i=0;i<gameBoard->getJogador2Size();i++)
		{
			if(gameBoard->getJogador2PodAt(i)->getId()==podnumber)
			{
				for(int j=0;j<gameBoard->getJogador2PodAt(i)->getDirsSize();j++)
				{
				
						Pod * aux = gameBoard->getJogador2PodAt(i);
						aux->setX(x);
						aux->setY(y);

						return true;
					
				}
				
				return false;
			}
		}
	}
	return false;
}

bool Game::addpod(int player, int idpod, int idcasa)
{
	int x=(idcasa-100)/10;
	int y=(idcasa-100)%10;
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
		int size=gameBoard->getJogador1Size();
		for(int i=0;i<size;i++)
		{
			Pod * aux=gameBoard->getJogador1PodAt(i);
			if(aux->getId()==id)
			{
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
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1)
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
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1)
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
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getX()*10)+aux->getY()-1);
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
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getX()*10)+aux->getY());
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
	}
	else
	{
		int size=gameBoard->getJogador2Size();
		for(int i=0;i<size;i++)
		{
			Pod * aux=gameBoard->getJogador2PodAt(i);
			if(aux->getId()==id)
			{
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
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()-1)
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
								if(gameBoard->getJogador1PodAt(z)->getX()==aux->getX()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getX()==aux->getX()+1)
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
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()+1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getX()*10)+aux->getY());
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
								if(gameBoard->getJogador1PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}
							//Pecas do 2
							for(int z=0;z<size3;z++)
							{
								if(gameBoard->getJogador2PodAt(z)->getY()==aux->getY()-1)
								{
									encontra=true;
								}
							}

							if(!encontra)
							{
								resultados.push_back(100+(aux->getY()*10)+aux->getY());
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

