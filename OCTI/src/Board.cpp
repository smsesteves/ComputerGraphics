#include "Board.h"

Board::Board()
{

		Jogador1.push_back(new Pod(1,2,2,1));  //---------> y
		Jogador1.push_back(new Pod(1,2,4,2));
		Jogador1.push_back(new Pod(1,2,6,3));
				
		Jogador2.push_back(new Pod(2,6,2,1));
		Jogador2.push_back(new Pod(2,6,4,2));
		Jogador2.push_back(new Pod(2,6,6,3));
			
	
}

void Board::display()
{

	for(unsigned int i=1;i<=BOARDSIZE;i++)
	{
		cout<<"[";
		for(unsigned int j=1;j<=BOARDSIZE;j++)
		{ 
			cout<<"[";

			bool encontra=false;
			for(unsigned int z=0;z<Jogador1.size();z++)
			{
				if(i==Jogador1[z]->getX() && j==Jogador1[z]->getY())
				{
					cout<<"1"<<Jogador1[z]->getId();
					encontra=true;
				}
			
			}

			
			for(unsigned int z=0;z<Jogador2.size();z++)
			{
				if(i==Jogador2[z]->getX() && j==Jogador2[z]->getY())
				{
					cout<<"2"<<Jogador2[z]->getId();
					encontra=true;
				}
			}
			if(!encontra) {cout<<"  ";};
			
			
			cout<<"]";

		}
		cout<<"]"<<endl;
	}


	cout<<endl<<"Player 1 Pods"<<endl;
	for(unsigned int z=0;z<Jogador1.size();z++)
	{
		cout<<endl<<"Pod "<<z+1<<" x: "<<Jogador1[z]->getX()<<" y: "<<Jogador1[z]->getY()<<endl;

		cout<<"\tProngs: ";
		for(unsigned int i=0;i<Jogador1[z]->getDirsSize();i++)
		{
			cout<<Jogador1[z]->getDirsAt(i)->getDir()<<" ";
		}
		
	}

	cout<<endl<<"\nPlayer 2 Pods"<<endl;
	for(unsigned int z=0;z<Jogador2.size();z++)
	{
		cout<<endl<<"Pod "<<z+1<<" x: "<<Jogador2[z]->getX()<<" y: "<<Jogador2[z]->getY()<<endl;
		cout<<"\tProngs: ";
		for(unsigned int i=0;i<Jogador2[z]->getDirsSize();i++)
		{
			cout<<Jogador2[z]->getDirsAt(i)->getDir()<<" ";
		}
	}
				
}


bool Board::checkadd(int player)
{
	if(player==1)
	{
		int count=0;
		for(unsigned int z=0;z<Jogador1.size();z++)
		{
			if(Jogador1[z]->getX()==1 && (Jogador1[z]->getY()==1 || Jogador1[z]->getY()==3 || Jogador1[z]->getY()==5))
			{
				count++;
			}
		}
		if(count<3)
		{
			return true;
		}
		return false;
	}
	else if(player==2)
	{
		int count=0;
		for(unsigned int z=0;z<Jogador2.size();z++)
		{
			if(Jogador2[z]->getX()==5 && (Jogador2[z]->getY()==1 || Jogador2[z]->getY()==3 || Jogador2[z]->getY()==5))
			{
				count++;
			}
		}
		if(count<3)
		{
			return true;
		}
		return false;
	}
	return false;
}



bool Board::checkmove(int player)
{
	if(player==1)
	{
		
		for(unsigned int z=0;z<Jogador1.size();z++)
		{
			if(Jogador1[z]->getDirsSize()>0)
			{
				return true;
			}
		}
		return false;
	}
	else if(player==2)
	{
		int count=0;
		for(unsigned int z=0;z<Jogador2.size();z++)
		{
			if(Jogador2[z]->getDirsSize()>0)
			{
				count++;
			}
		}
		return false;
	}
	return false;
}

			

bool Board::checkend()
{
	for(unsigned int z=0;z<Jogador1.size();z++)
	{
		if(Jogador1[z]->getX()==6 && (Jogador1[z]->getY()==2 || Jogador1[z]->getY()==4 || Jogador1[z]->getY()==6))
		{
			return true;
		}
	}
	for(unsigned int z=0;z<Jogador2.size();z++)
	{
		if(Jogador2[z]->getX()==6 && (Jogador2[z]->getY()==2 || Jogador2[z]->getY()==4 || Jogador2[z]->getY()==6))
		{
			return true;
		}
	}
	return false;
}
			
int Board::getJogador1Size()
{
	return Jogador1.size();
}

int Board::getJogador2Size()
{
	return Jogador2.size();
}

Pod* Board::getJogador1PodAt(int pos)
{
	return Jogador1[pos];
}

Pod* Board::getJogador2PodAt(int pos)
{
	return Jogador2[pos];
}


void Board::addJogador1PodAt(int x,int y,int id)
{
	Jogador1.push_back(new Pod(1,x,y,id));
}
void Board::addJogador2PodAt(int x,int y,int id)
{
	Jogador2.push_back(new Pod(2,x,y,id));
}


int Board::getXbyId(int player, int id)
{
	if(player==1)
	{
		for(int i=0;i<Jogador1.size();i++)
		{
			if(getJogador1PodAt(i)->getId())
			{
				return getJogador1PodAt(i)->getX();
			}

		}
	}
	else
	{
		for(int i=0;i<Jogador2.size();i++)
		{
			if(getJogador2PodAt(i)->getId())
			{
				return getJogador2PodAt(i)->getX();
			}
		}
	}
}

int Board::getYbyId(int player , int id)
{
	if(player==1)
	{
		for(int i=0;i<Jogador1.size();i++)
		{
			if(getJogador1PodAt(i)->getId())
			{
				return getJogador1PodAt(i)->getY();
			}

		}
	}
	else
	{
		for(int i=0;i<Jogador2.size();i++)
		{
			if(getJogador2PodAt(i)->getId())
			{
				return getJogador2PodAt(i)->getY();
			}
		}
	}

}