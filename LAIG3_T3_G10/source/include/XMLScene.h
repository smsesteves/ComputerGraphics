#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "YAFscene.h"
#include "tinyxml.h"
#include "CGFscene.h"
#include "Game.h"
#include "socket.h"
#include "TPinterface.h"
#include "TextObject.h"

class XMLScene: public CGFscene
{
public:
	XMLScene(char *filename,CGFapplication* app, Game* game, int connecting);
	~XMLScene();
	void init();
	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	void display();
	void refreshLights();
	void refreshCameras();
	YAFScene* getScenePointer(){return scene;};
	void setLightState(int pos);
	void update(unsigned long tempo);
	int initSocket(char* host, int port);
	bool doinganimations();
	bool inMovie; 
	int needConnection;
	int seleccao;
	int tempoJogada;
	int ultimoTempo; 
	int numeroJogadas;
	TextObject* marcador;
	
protected:
	
	CGFapplication* app;
	TiXmlDocument* doc;
	Game* octi;

	TiXmlElement* globalsElement; //com que cgf?
	TiXmlElement* camerasElement; // ortho- onde meto valores? como alterar o campo target
	TiXmlElement* lightingElement; //tick
	TiXmlElement* texturesElement; // contrutor problemas com a string parametro?
	TiXmlElement* appearancesElement; //tick
	TiXmlElement* graphElement; //esteves
	TiXmlElement* animationsElement;

	YAFScene* scene;


};

#endif