#include "utils.h"



Position processaComer(Board* board,Pod* aux, string dir)
{
	int incx=0;
	int incy=0;
	//checkpods com posx + posy e incx + incy
	if(dir=="n")
	{
		incx=-1;
	}
	else if(dir=="s")
	{
		incx=1;
	}
	else if(dir=="e")
	{
		incy=1;
	}
	else if(dir=="o")
	{
		incy=-1;
	}
	else if(dir=="ne")
	{
		incx=-1;	
		incy=1;
	}
	else if(dir=="no")
	{
		incx=-1;
		incy=-1;
	}
	else if(dir=="se")
	{
		incx=1;
		incy=1;
	}
	else if(dir=="so")
	{
		incx=1;
		incy=-1;
	}
	Position pos;
	pos.incx=incx;
	pos.incy=incy;
	return pos;
}

string criastring(vector<int> vec){
	stringstream resultado;
	for(int i = 0; i < vec.size(); i++){
		resultado << vec[i];
		if(!(i == vec.size() -1)){
			resultado << " ";
		}
	}
	string res = resultado.str();
	return res;
}

vector<int> divideStringEmInt(const char* mensagem){
	vector<int> res;

	int posi = 0;
	int posf = 0;
	int i = 0;
	while(i<=strlen(mensagem)){
		if(mensagem[i] == ' ' || mensagem[i] == '\0'){
			//cout<<"aqui"<<endl;
			posf = i;
			char tmp[255];
			
			
			
				memcpy(tmp, &mensagem[posi], posf);
				tmp[posf-posi] = '\0';
			
			//cout<<posi<<" "<<posf<<endl;

			//printf("%s\n",tmp);
			res.push_back(atoi(tmp));
			posi=posf+1;
		}
		i++;

		// 2 3 4
		// 01234
	}

	return res;
}


int geraRandom(vector<int> resultados)
{
	return resultados[(rand() % resultados.size())]; 
}