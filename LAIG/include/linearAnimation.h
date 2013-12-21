#ifndef LINEAR_ANIMATION_H
#define LINEAR_ANIMATION_H

#include "animation.h"
#include "utils.h"
struct velocidadescomp
{
	int number1;
	int number2;
	float time;
	float vx;
	float vy;
	float vz;
};






class LinearAnimation: public Animation
{
public:
	bool started;
	vector<velocidadescomp> velocidades;
	unsigned long tempoanterior,tempoatual;
	int animationType(){ return 0; };
	vector<ControlPoint> controlPoints;
	ControlPoint primeiro;

	LinearAnimation(string id, float span, vector<ControlPoint> controlPoints):Animation(id,span){
		this->controlPoints = controlPoints;
		x = controlPoints.at(0).x*1.0;
		y = controlPoints.at(0).y*1.0;
		z = controlPoints.at(0).z*1.0;
		numbercontrol=0;
		started=false;
		animationEnded=false;
		xf = controlPoints.at(controlPoints.size()-1).x*1.0;
		yf = controlPoints.at(controlPoints.size()-1).y*1.0;
		zf = controlPoints.at(controlPoints.size()-1).z*1.0;
		ry=-1;
		primeiro.x=0.0;
		primeiro.y=0.0;
		primeiro.z=1.0;
	
	};
	
	float x,y,z;
	float xf, yf, zf;
	float incx,incy,incz;
	float ry;
	int numbercontrol;
	bool animationEnded;
	
	void updatePosition(unsigned long t){
		
		tempoatual=t;
		float vinc=(tempoatual-tempoanterior)/1000.0;
		//cout<<"Control Point"<< numbercontrol<<endl;
		if( !animationEnded){
			started=true;


			ControlPoint aux1;
			ControlPoint aux2;


			aux1=primeiro;
			aux2.x=controlPoints.at(numbercontrol+1).x-controlPoints.at(numbercontrol).x;
			aux2.y=controlPoints.at(numbercontrol+1).y-controlPoints.at(numbercontrol).y;
			aux2.z=controlPoints.at(numbercontrol+1).z-controlPoints.at(numbercontrol).z;				
			

		
			//cout<<" Vetor 1 :"<<aux2.x<<" "<<aux2.y<<" "<<aux2.z<<endl;
			//cout<<" Modulo 2:"<<distanciapontos(0,0,0,aux2.x,aux2.y,aux2.z);


			ry=acos(((aux1.x*aux2.x)+(aux1.y*aux2.y)+(aux1.z*aux2.z))/
					(distanciapontos(0,0,0,aux1.x,aux1.y,aux1.z)*distanciapontos(0,0,0,aux2.x,aux2.y,aux2.z)));
			
			//float i = (aux1.y * aux2.z)-(aux2.y* aux1.z);
			//float j = -((aux1.x * aux2.z)-(aux2.x* aux1.z));
			//float k = (aux1.x * aux2.y)-(aux2.x* aux1.y);
			//float dist=sqrt((i*i)+(j*j)+(k*k));
			//float scale=(distanciapontos(0,0,0,aux1.x,aux1.y,aux1.z)*distanciapontos(0,0,0,aux2.x,aux2.y,aux2.z));
			//float newangle=asin(dist/scale);
			//float newangle=asin(i/(scale*n.x));
			//cout<<"Angle:\n"<<ry<<endl;

			
			ry=radiustodegrees(ry);
			if(aux2.x<0){ry=-ry;};
			//newangle=radiustodegrees(newangle);
			//cout<<"Angle:\n"<<ry<<" "<<newangle<<endl;
			
			
		
			

			int pos=0;



			for(unsigned int i=0;i<velocidades.size();i++)
			{
				if(velocidades.at(i).number1==numbercontrol && velocidades.at(i).number2==numbercontrol+1)
				{
					
					pos=i;
					break;
				}
			}

			if(controlPoints.at(numbercontrol+1).x-controlPoints.at(numbercontrol).x<0 && velocidades.at(pos).vx>0)
			{
				
				velocidades.at(pos).vx=-velocidades.at(pos).vx;
			}
			else if(controlPoints.at(numbercontrol+1).x-controlPoints.at(numbercontrol).x>0 && velocidades.at(pos).vx<0)
			{
				velocidades.at(pos).vx=-velocidades.at(pos).vx;
			}
			if(controlPoints.at(numbercontrol+1).y-controlPoints.at(numbercontrol).y<0 && velocidades.at(pos).vy>0)
			{
				velocidades.at(pos).vy=-velocidades.at(pos).vy;
			}
			else if(controlPoints.at(numbercontrol+1).y-controlPoints.at(numbercontrol).y>0 && velocidades.at(pos).vy<0)
			{
				velocidades.at(pos).vy=-velocidades.at(pos).vy;
			}
			if(controlPoints.at(numbercontrol+1).z-controlPoints.at(numbercontrol).z<0 && velocidades.at(pos).vz>0)
			{
				velocidades.at(pos).vz=-velocidades.at(pos).vz;
			}
			else if(controlPoints.at(numbercontrol+1).z-controlPoints.at(numbercontrol).z>0 && velocidades.at(pos).vz<0)
			{
				velocidades.at(pos).vz=-velocidades.at(pos).vz;
			}
			
				
				//verificar nova posição				
			
			x=x+vinc*velocidades.at(pos).vx;
			y=y+vinc*velocidades.at(pos).vy;
			z=z+vinc*velocidades.at(pos).vz;	

			bool isX=false;
			bool isY=false;
			bool isZ=false;

			if(x>=controlPoints.at(numbercontrol+1).x && velocidades.at(pos).vx>=0)
			{
				x=controlPoints.at(numbercontrol+1).x;
				isX=true;
			}
			else if(x<=controlPoints.at(numbercontrol+1).x && velocidades.at(pos).vx<=0)
			{
				x=controlPoints.at(numbercontrol+1).x;
				isX=true;
			}

			if(y>=controlPoints.at(numbercontrol+1).y && velocidades.at(pos).vy>=0)
			{
				y=controlPoints.at(numbercontrol+1).y;
				isY=true;
			}
			else if(y<=controlPoints.at(numbercontrol+1).y && velocidades.at(pos).vy<=0)
			{
				y=controlPoints.at(numbercontrol+1).y;
				isY=true;
			}

			if(z>=controlPoints.at(numbercontrol+1).z && velocidades.at(pos).vz>=0)
			{
				z=controlPoints.at(numbercontrol+1).z;
				isZ=true;
			}
			else if(z<=controlPoints.at(numbercontrol+1).z && velocidades.at(pos).vz<=0)
			{
				z=controlPoints.at(numbercontrol+1).z;
				isZ=true;
			}

			if(isX && isY && isZ)
			{
				numbercontrol++;
			}
			if(numbercontrol==controlPoints.size()-1)
			{
				animationEnded=true;
			}
			
			//system("pause");
		}
		else
		{
			//cout<<"Reinicia"<<endl;
			
			animationEnded=true;
			x=0;
			y=0;
			ry=0;
			

		}
		tempoanterior=t;
		
	};


	void init(unsigned long t)
	{
		numbercontrol=0;
		x=controlPoints.at(0).x*1.0;
		y=controlPoints.at(0).y*1.0;
		z=controlPoints.at(0).z*1.0;
		ry=-1;
		animationEnded=false;
		tempoanterior=t;
		started=false;
	}
};

#endif