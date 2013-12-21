
#include "utils.h"

float distanciapontos(float x1, float y1, float z1, float x2, float y2, float z2)
{
		return (float)sqrt( pow (x2 - x1, 2) + pow (y2 - y1, 2) + pow(z2-z1,2))*1.0;
}

float radiustodegrees(float angle)
{
	float newangle=angle*180.0/3.14159265;
	
	return newangle;
}

vector<int> divideStringEmInt(char* mensagem){
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