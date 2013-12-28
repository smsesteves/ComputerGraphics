#include "XMLScene.h"
#include <fstream>

using namespace std;

XMLScene::XMLScene(char *filename,CGFapplication* app, Game* game, int connecting)
{
	needConnection = connecting;

	this->octi=game;
	this->app=app;
	glMatrixMode(GL_MODELVIEW); 

	GLfloat transformationMatrix[16];

	// Read XML from file
	//map<string,Node*> graph;

	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		system("pause");
		exit( 1 );
	}

	TiXmlElement* yafElement= doc->FirstChildElement( "yaf" );

	if (yafElement == NULL)
	{
		printf("Main yaf block element not found! Exiting!\n");
		exit(1);
	}

	globalsElement = yafElement->FirstChildElement( "globals" );

	scene = new YAFScene();
	scene->nextTheme = 1;

	//--------- Animations Parsing -----------
	animationsElement = yafElement->FirstChildElement( "animations" );

	if (animationsElement == NULL)
		printf("Animations block not found!\n");
	else
	{
		printf("Processing Animations:\n");
		TiXmlElement* singleAnimationElement = animationsElement->FirstChildElement("animation");

		while(singleAnimationElement){

			printf("A new animation was found!\n");

			string id, type;
			float span;

			if (singleAnimationElement->QueryFloatAttribute("span",&span)==TIXML_SUCCESS &&
				singleAnimationElement->Attribute("id") != NULL &&
				singleAnimationElement->Attribute("type") != NULL)
			{
				id = singleAnimationElement->Attribute("id");
				type = singleAnimationElement->Attribute("type");

				printf("\tAnimation attributes:\n");
				printf("\t\t id: %s\n", id.c_str());
				printf("\t\t type: %s\n", type.c_str());
				printf("\t\t span: %f\n", span);

				if(type=="linear"){
					
					TiXmlElement* controlPointElement = singleAnimationElement->FirstChildElement("controlpoint");
					vector<ControlPoint> auxPoints;
					while(controlPointElement){
						float x,y,z;
						if (controlPointElement->QueryFloatAttribute("xx",&x)==TIXML_SUCCESS &&
							controlPointElement->QueryFloatAttribute("yy",&y)==TIXML_SUCCESS &&
							controlPointElement->QueryFloatAttribute("zz",&z)==TIXML_SUCCESS)
						{

						ControlPoint pontoAux(x,y,z);
						auxPoints.push_back(pontoAux);
						}
						controlPointElement = controlPointElement->NextSiblingElement();
					}

					Animation* aux = new LinearAnimation(id,span,auxPoints);
					scene->animationsComp.insert(pair<string,Animation*>(id,aux));
				}
				else{
					cout << "Other type different from Linear\n" << endl;
				}

										
			}
			else printf("Error parsing Animation Element\n");

			singleAnimationElement = singleAnimationElement->NextSiblingElement();
		}
	}

	//--------- Globals Parsing -----------
	if (globalsElement == NULL)
		printf("Globals block not found!\n");
	else
	{
		printf("Processing Globals:\n");

		string background, drawmode, cullface, shading, cullorder;

		if (globalsElement->Attribute("background")!=NULL &&
			globalsElement->Attribute("drawmode") != NULL &&
			globalsElement->Attribute("cullface") != NULL &&
			globalsElement->Attribute("shading") != NULL &&
			globalsElement->Attribute("cullorder") != NULL)
		{
			// TODO: Verificacoes dos valores de entrada

			background=globalsElement->Attribute("background");
			float a,b,c,d;
			sscanf(background.c_str(),"%f %f %f %f", &a, &b, &c, &d);
			scene->globalsComp.setBackground(a,b,c,d);
			printf("\tBackground: %s \n", background.c_str());

			drawmode=globalsElement->Attribute("drawmode");
			scene->globalsComp.setDrawmode(drawmode);
			printf("\tDrawmode: %s \n", drawmode.c_str());

			cullface=globalsElement->Attribute("cullface");
			scene->globalsComp.setCullface(cullface);
			printf("\tCullface: %s \n", cullface.c_str());

			cullorder=globalsElement->Attribute("cullorder");
			scene->globalsComp.setCullorder(cullorder);
			printf("\tCullorder: %s \n", cullorder.c_str());

			shading=globalsElement->Attribute("shading");
			scene->globalsComp.setShading(shading);
			printf("\tShading: %s \n", shading.c_str());

		}
		else
			printf("Error parsing background\n");
	}

	//--------- Cameras Parsing -----------
	camerasElement = yafElement->FirstChildElement( "cameras" );

	if (camerasElement == NULL)
		printf("Cameras block not found!\n");
	else
	{
		printf("Processing Cameras:\n");

		string initial;
		if (camerasElement->Attribute("initial")!=NULL)
		{
			// TODO: Verificacoes dos valores de entrada
			initial=camerasElement->Attribute("initial");
			printf("\tInitial: %s \n", initial.c_str());
		}

		TiXmlElement* cameraElement = camerasElement->FirstChildElement();
		while(cameraElement){

			if ((string)cameraElement->Value() == "perspective")
			{
				float near;
				float far;
				float angle;

				string pos,target;
				string id;

				Perspective* perspectiveAux = new Perspective();
				perspectiveAux->toanimate = false;

				if (cameraElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS &&
					cameraElement->Attribute("id") != NULL
					){
						id = cameraElement->Attribute("id");
						pos = cameraElement->Attribute("pos");
						target = cameraElement->Attribute("target");

						if(initial==id)
							perspectiveAux->setCInitial(true);
						printf("\tPerspective attributes:\n");
						printf("\t\tnear: %f far: %f angle: %f \n", near, far, angle);
						printf("\t\tpos: %s target: %s id: %s\n", pos.c_str(), target.c_str(),id.c_str());

						float pa,pb,pc;
						float ta,tb,tc;
						sscanf(pos.c_str(),"%f %f %f", &pa, &pb, &pc);
						sscanf(target.c_str(),"%f %f%f", &ta, &tb, &tc);
						perspectiveAux->setX(pa);
						perspectiveAux->setY(pb);
						perspectiveAux->setZ(pc);

						perspectiveAux->setCTarget(ta,tb,tc);
						perspectiveAux->setCPrimary(id, near, far);
						perspectiveAux->setCAngle(angle);

						if(initial == perspectiveAux->getid()){
							perspectiveAux->setInitial(true);
						}
						else perspectiveAux->setInitial(false);

						scene->camerasComp.push_back(perspectiveAux);
				}
				else
					printf("Error parsing Perspective Element\n");
			}
			else if ((string)cameraElement->Value() == "ortho")
			{
				float near,far,left,right,top,bottom;
				string id;

				Ortho* orthoAux = new Ortho();

				if (cameraElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("left",&left)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("right",&right)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("top",&top)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("bottom",&bottom)==TIXML_SUCCESS &&
					cameraElement->Attribute("id") != NULL
					){
						id = cameraElement->Attribute("id");
						printf("\tOrtho attributes:\n");
						printf("\t\tnear: %f, far: %f, angle: %f \n", near, far, left);
						printf("\t\tpos: %f, target: %f, bottom: %f\n", right, top, bottom);
						printf("\t\tid: %s\n", id.c_str());

						if(initial==id)
							orthoAux->setCInitial(true);
						orthoAux->setCPrimary(id,near,far);
						orthoAux->setCFloatValues(left,right,top,bottom);


						if(initial == orthoAux->getid()){
							orthoAux->setInitial(true);
						}
						else orthoAux->setInitial(false);

						scene->camerasComp.push_back(orthoAux);

				}
				else
					printf("Error parsing Ortho Element\n");
			}
			else
				printf("Invalid Camera type.\n");

			cameraElement = cameraElement->NextSiblingElement();
		}
	}

	//--------- Lighting Parsing -----------
	lightingElement = yafElement->FirstChildElement( "lighting" );

	if (lightingElement == NULL)
		printf("Lighting block not found!\n");
	else
	{
		printf("Processing Lighting:\n");

		string doublesided, local, enabled; //boolean
		string ambient;
		if (lightingElement->Attribute("doublesided") != NULL &&
			lightingElement->Attribute("local") != NULL &&
			lightingElement->Attribute("enabled") != NULL &&
			lightingElement->Attribute("ambient") != NULL)
		{
			// TODO: Verificacoes dos valores de entrada
			ambient = lightingElement->Attribute("ambient");
			doublesided = lightingElement->Attribute("doublesided");
			local = lightingElement->Attribute("local");
			enabled = lightingElement->Attribute("enabled");

			float x,y,z,p;


			Lighting* lightingConfig = new Lighting();

			if(doublesided == "true") lightingConfig->setDoublesided(true);
			else lightingConfig->setDoublesided(false);

			if(local == "true") lightingConfig->setLocal(true);
			else lightingConfig->setLocal(false);

			//if(enabled == "true") lightingConfig->setEnabled(true);
			//else lightingConfig->setEnabled(false);

			if(enabled== "true")
			{
				sscanf(ambient.c_str(),"%f %f %f %f",&x,&y,&z,&p);
			}
			else
			{
				x=0;
				y=0;
				z=0;
				p=0;
			}

			lightingConfig->setLightingAmbient(x,y,z,p);

			scene->setLightConfig(lightingConfig);

			printf("\tDoublesided: %s \n", doublesided.c_str());
			printf("\tLocal: %s \n", local.c_str());
			printf("\tEnabled: %s \n", enabled.c_str());
			printf("\tAmbient: %s \n", ambient.c_str());
		}

		int lightId = GL_LIGHT0;
		TiXmlElement* lightElement = lightingElement->FirstChildElement();
		while(lightElement){
			lightId++;
			//OMNI
			if ((string)lightElement->Value() == "omni"){

				string oenabled; //boolean
				string id;
				string location, oambient, odiffuse, ospecular;

				if (lightElement->Attribute("id") != NULL &&
					lightElement->Attribute("enabled") != NULL &&
					lightElement->Attribute("location") != NULL &&
					lightElement->Attribute("ambient") != NULL &&
					lightElement->Attribute("diffuse") != NULL &&
					lightElement->Attribute("specular") != NULL)
				{

					string location =  lightElement->Attribute("location");
					float omniLocation[4];
					omniLocation[3] = 1.0;
					sscanf(location.c_str(),"%f %f %f", &omniLocation[0], &omniLocation[1], &omniLocation[2]);

					float* dir = (float*) 0;
					Omni* omniAux = new Omni(lightId, omniLocation, NULL);

					id = lightElement->Attribute("id");
					oenabled = lightElement->Attribute("enabled");
					oambient = lightElement->Attribute("ambient");
					odiffuse = lightElement->Attribute("diffuse");
					ospecular = lightElement->Attribute("specular");

					omniAux->setIdS(id);

					omniAux->setIdI(lightId);

					if(oenabled == "true")  omniAux->enable();
					else omniAux->disable();

					float ambientArr[4];
					sscanf(oambient.c_str(),"%f %f %f %f", &ambientArr[0], &ambientArr[1], &ambientArr[2], &ambientArr[3]);
					omniAux->setAmbient(ambientArr);

					float specularArr[4];
					sscanf(ospecular.c_str(),"%f %f %f %f", &specularArr[0], &specularArr[1], &specularArr[2], &specularArr[3]);
					omniAux->setSpecular(specularArr);

					float diffuseArr[4];
					sscanf(odiffuse.c_str(),"%f %f %f %f", &diffuseArr[0], &diffuseArr[1], &diffuseArr[2], &diffuseArr[3]);
					omniAux->setDiffuse(diffuseArr);

					scene->lightsComp.push_back(omniAux);

				}
				else
					printf("Error parsing Omni Element\n");
			}
			else if ((string)lightElement->Value() == "spot")
			{
				string senabled; // boolean
				float angle, exponent;
				string id, direction;

				if (lightElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS &&
					lightElement->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS &&
					lightElement->Attribute("direction") != NULL &&
					lightElement->Attribute("enabled") != NULL &&
					lightElement->Attribute("ambient") != NULL &&
					lightElement->Attribute("diffuse") != NULL &&
					lightElement->Attribute("specular") != NULL &&
					lightElement->Attribute("id") != NULL &&
					lightElement->Attribute("location") !=NULL
					){

						string location;
						location = lightElement->Attribute("location");
						float locationArr[4];
						locationArr[3] = 1.0;
						sscanf(location.c_str(),"%f %f %f", &locationArr[0], &locationArr[1], &locationArr[2]);

						Spot* spotAux = new Spot(lightId, locationArr, NULL);

						id = lightElement->Attribute("id");
						spotAux->setIdS(id);
						spotAux->setIdI(lightId);

						direction = lightElement->Attribute("direction");
						float directionSpot[3];
						sscanf(direction.c_str(),"%f %f %f", &directionSpot[0], &directionSpot[1], &directionSpot[2]);
						spotAux->setSDirection(directionSpot);

						senabled = lightElement->Attribute("enabled");
						if(senabled == "true") spotAux->enable();
						else spotAux->disable();


						spotAux->setSExponent(exponent);
						spotAux->setSAngle(angle);
						spotAux->setAngle(angle);

						string sspecular, sdiffuse, sambient;
						sspecular = lightElement->Attribute("specular");
						sdiffuse = lightElement->Attribute("diffuse");
						sambient = lightElement->Attribute("ambient");

						float specular[4];
						sscanf(sspecular.c_str(),"%f %f %f %f", &specular[0], &specular[1], &specular[2], &specular[3]);
						spotAux->setSpecular(specular);

						float diffuse[4];
						sscanf(sdiffuse.c_str(),"%f %f %f %f", &diffuse[0], &diffuse[1], &diffuse[2], &diffuse[3]);
						spotAux->setDiffuse(diffuse);

						float ambient[4];
						sscanf(sambient.c_str(), "%f %f %f %f", &ambient[0], &ambient[1], &ambient[2], &ambient[3]); 
						spotAux->setAmbient(ambient);

						scene->lightsComp.push_back(spotAux);

				}
				else
					printf("Error parsing Spot Element\n");
			}
			else
				printf("Invalid Light type\n");

			lightElement = lightElement->NextSiblingElement();
		}
	}


	//--------- Textures Parsing -----------
	texturesElement = yafElement->FirstChildElement( "textures" );

	if (texturesElement == NULL)
		printf("Textures block not found!\n");
	else
	{
		printf("Processing Textures:\n");
		TiXmlElement* textureElement = texturesElement->FirstChildElement("texture");
		while(textureElement)
		{
			string id, file;
			if (textureElement->Attribute("id") != NULL &&
				textureElement->Attribute("file") != NULL
				){
					id = textureElement->Attribute("id");
					file = textureElement->Attribute("file");
					printf("\tTexture attributes:\n");
					printf("\t\tId: %s\n\t\tFile: %s\n", id.c_str(), file.c_str());

					//Texture* textureAux = new Texture();
					//ofstream fin("ola.txt");
					//fin.close();
					file =  file;
					Texture* textureAux = new Texture(file);
					textureAux->setTId(id);
					textureAux->setTPath(file);
					scene->texturesComp.push_back(textureAux);
			}
			else
				printf("Error parsing Texture Element\n");

			textureElement = textureElement->NextSiblingElement();
		}
	}

	//--------- Appearances Parsing -----------
	appearancesElement = yafElement->FirstChildElement( "appearances" );

	if (appearancesElement == NULL)
		printf("Appearances block not found!\n");
	else
	{
		printf("Processing Appearances:\n");
		TiXmlElement* appearanceElement = appearancesElement->FirstChildElement("appearance");
		while (appearanceElement)
		{

			Appearance* ap = new Appearance();
			string id, textureref;
			
			string emissiveS, ambientS, diffuseS, specularS;
			float shininess, texlength_s, texlength_t;

			if (appearanceElement->QueryFloatAttribute("shininess",&shininess)==TIXML_SUCCESS &&
				appearanceElement->Attribute("id") != NULL &&
				appearanceElement->Attribute("emissive") != NULL &&
				appearanceElement->Attribute("ambient") != NULL &&
				appearanceElement->Attribute("diffuse") != NULL &&
				appearanceElement->Attribute("specular") != NULL
				){
					id = appearanceElement->Attribute("id");
					ap->setIdS(id);

					emissiveS = appearanceElement->Attribute("emissive");
					float Aemissive[4];
					sscanf(emissiveS.c_str(),"%f %f %f %f", &Aemissive[0], &Aemissive[1], &Aemissive[2], &Aemissive[3]);
					ap->setEmissive(Aemissive);

					ambientS = appearanceElement->Attribute("ambient");
					float Aambient[4];
					sscanf(ambientS.c_str(),"%f %f %f %f", &Aambient[0], &Aambient[1], &Aambient[2], &Aambient[3]);
					ap->setAmbient(Aambient);

					diffuseS = appearanceElement->Attribute("diffuse");
					float Adiffuse[4];
					sscanf(diffuseS.c_str(),"%f %f %f %f", &Adiffuse[0], &Adiffuse[1], &Adiffuse[2], &Adiffuse[3]);
					ap->setDiffuse(Adiffuse);

					specularS = appearanceElement->Attribute("specular");
					float Aspecular[4];
					sscanf(specularS.c_str(),"%f %f %f %f", &Aspecular[0], &Aspecular[1], &Aspecular[2], &Aspecular[3]);
					ap->setSpecular(Aspecular);


					if(appearanceElement->Attribute("textureref") != NULL)
					{
						if(appearanceElement->QueryFloatAttribute("texlength_s",&texlength_s)==TIXML_SUCCESS &&
							appearanceElement->QueryFloatAttribute("texlength_t",&texlength_t)==TIXML_SUCCESS)
						{

							textureref = appearanceElement->Attribute("textureref");
							ap->setTextureReference(textureref);
							//ap->setTexture(textureref);

							ap->setTextureWrap(texlength_s,texlength_t);

							ap->setShininess(shininess);

							int itTexturesComp = 0;
							std::vector<Texture*>::iterator it = scene->texturesComp.begin();
							for(it; it != scene->texturesComp.end(); it++){
								if(textureref == scene->texturesComp.at(itTexturesComp)->getTId()){
									ap->setTexture((*it));
								}
								itTexturesComp++;
							}
						}
					}

					printf("\tApearance attributes:\n");
					printf("\t\tId: %s \n\t\tEmissive: %s \n\t\tAmbient: %s\n", id.c_str(), emissiveS.c_str(), ambientS.c_str());
					printf("\t\tDiffuse: %s \n\t\tSpecular: %s \n\t\tTextureRef: %s \n\t\tShininess: %f\n", diffuseS.c_str(), specularS.c_str(), textureref.c_str(), shininess);
					if(textureref.length()==0)
						printf("\t\tTexLength S: %f \n\t\tTexLength T: %f\n", texlength_s, texlength_t);

					scene->appearancesComp.push_back(ap);

			}
			else
				printf("Error parsing Appearance Element\n");

			appearanceElement = appearanceElement->NextSiblingElement();

		}
	}

	//--------- Graph Parsing -----------
	graphElement = yafElement->FirstChildElement( "graph" );
	scene->rootid=graphElement->Attribute("rootid");

	if (graphElement == NULL)
		printf("Graph block not found!\n");
	else
	{
		TiXmlElement *node=graphElement->FirstChildElement("node");
		string id,picking;
		string flagDL;
		while (node)
		{
			Node *no = new Node();

			if(node->Attribute("id") != NULL){
				id = node->Attribute("id");
				no->setId(id);


				printf("Node: %s\n", id.c_str());
			}
			if(node->Attribute("pickingid") != NULL){
				picking = node->Attribute("pickingid");
				int idInt = atoi(picking.c_str());
				no->setPicking(idInt);
				printf("\t %s\n", picking.c_str());

				
				std::vector<Appearance*>::iterator it = scene->appearancesComp.begin();
				for(it; it != scene->appearancesComp.end(); it++){
					if((*it)->getIdS() == "appSelected"){
						no->highlighted = (*it);
					}
				}  
				

				octi->boardElements[idInt] = no;
			}
			else no->setPicking(-1);

			if(node->Attribute("displaylist") != NULL){
				flagDL = node->Attribute("displaylist");
				if(flagDL == "true") no->setIsDL(true);

				cout << "DL: " << no->getIsDL() << endl;
			}

			// Transformacoes
			TiXmlElement* transformation = node->FirstChildElement("transforms");

			glPushMatrix(); 
			glLoadIdentity(); 
			glGetFloatv(GL_MODELVIEW_MATRIX, transformationMatrix);

			while(transformation){

				TiXmlElement* infoTrans = transformation->FirstChildElement();

				while(infoTrans){
					if((string)infoTrans->Value() == "translate"){
						string aux;

						float x,y,z;


						aux=infoTrans->Attribute("to");

						sscanf(aux.c_str(),"%f %f %f",&x,&y,&z);	

						glTranslated(x,y,z); 

						cout<<"Saí"<<endl;

						printf("\tEncontrou Translate\n");
					}
					else if((string)infoTrans->Value() == "rotate"){

						string aux;
						char x;
						float y;
						aux=infoTrans->Attribute("axis");

						sscanf(aux.c_str(),"%c",&x);
						aux=infoTrans->Attribute("angle");
						sscanf(aux.c_str(),"%f",&y);

						switch(x)
						{
						case 'x':
							glRotated(y,1,0,0);
							break;
						case 'y':

							glRotated(y,0,1,0);
							break;
						case 'z':
							glRotated(y,0,0,1);
							break;
						}

						printf("\tEncontrou Rotation\n");
					}
					else if((string)infoTrans->Value() == "scale"){

						string aux;
						float x,y,z;
						aux=infoTrans->Attribute("factor");
						sscanf(aux.c_str(),"%f %f %f",&x,&y,&z);	

						glScaled(x,y,z); 
						printf("\tEncontrou Scale\n");
					}

					infoTrans = infoTrans->NextSiblingElement();
				}

				transformation = transformation->NextSiblingElement();
			}
			glGetFloatv(GL_MODELVIEW_MATRIX, transformationMatrix);
			no->setmatrix(transformationMatrix);
			glPopMatrix();


			//Appearances
			string idAppearance;
			if(node->FirstChildElement("appearanceref") != NULL){
				TiXmlElement* appearanceRef = node->FirstChildElement("appearanceref");
				idAppearance = appearanceRef->Attribute("id");
				std::vector<Appearance*>::iterator it = scene->appearancesComp.begin();
				for(it; it != scene->appearancesComp.end(); it++){
					if((*it)->getIdS() == idAppearance){
						no->setAppearance((*it));
						no->notHighlighted = (*it);
					}
				}                     
				printf("\tAppearance: %s\n", idAppearance.c_str());
			}

			//Animation
			string idAnimation;
			if(node->FirstChildElement("animationref") != NULL){
				TiXmlElement* animationRef = node->FirstChildElement("animationref");
				idAnimation = animationRef->Attribute("id");
				no->setAnimationid(idAnimation);
				printf("\tAnimation: %s\n", idAnimation.c_str());
			}

			//Children
			TiXmlElement* children = node->FirstChildElement("children");
			while(children){
				TiXmlElement* infoChild = children->FirstChildElement();
				while(infoChild){
					if((string)infoChild->Value() == "noderef"){
						string idChild;
						idChild = infoChild->Attribute("id");
						no->insertstring(idChild);
						printf("\tInseriu RefNode: %s\n", idChild.c_str());
					}
					 //<plane parts=”ii” />
					else if((string)infoChild->Value() == "plane"){
						printf("\tEncontrou Plano\n");
						string partsAux;
						float parts;
						partsAux = infoChild->Attribute("parts");
						sscanf(partsAux.c_str(), "%i", &parts);

						Primitive* plane1 = new Plane(parts);
						no->insertprimitive(plane1);
						
					}
					else if((string)infoChild->Value() == "vehicle"){
						printf("\tEncontrou Veiculo\n");
						Primitive* v1 = new Vehicle();
						no->insertprimitive(v1);
						
					}
					else if((string)infoChild->Value() == "waterline"){
						string heightmap = infoChild->Attribute("heightmap");
						string texturemap = infoChild->Attribute("texturemap");
						string fragmentshader = infoChild->Attribute("fragmentshader");
						string vertexshader = infoChild->Attribute("vertexshader");

						Primitive* wLine1 = new Waterline(heightmap, texturemap, fragmentshader, vertexshader);
						no->insertprimitive(wLine1);

					} 
					else if((string)infoChild->Value() == "patch"){
						int order, partsU, partsV;
						string compute = infoChild->Attribute("compute");

						string orderAux = infoChild->Attribute("order");
						sscanf(orderAux.c_str(), "%i", &order);

						string partsUAux = infoChild->Attribute("partsU");
						sscanf(partsUAux.c_str(), "%i", &partsU);

						string partsVAux = infoChild->Attribute("partsV");
						sscanf(partsVAux.c_str(), "%i", &partsV);
						/*
						cout << "o: " << order << endl;
						cout << "partsU: " << partsU << endl;
						cout << "partsV: " << partsV << endl;
						cout << "compute: " << compute << endl;
						*/
						TiXmlElement* controlPointElement = infoChild->FirstChildElement("controlpoint");
						vector<ControlPoint> auxPoints;
						while(controlPointElement){
							float x,y,z;
							if (controlPointElement->QueryFloatAttribute("x",&x)==TIXML_SUCCESS &&
								controlPointElement->QueryFloatAttribute("y",&y)==TIXML_SUCCESS &&
								controlPointElement->QueryFloatAttribute("z",&z)==TIXML_SUCCESS)
							{
								cout << x << y << z << endl;
								ControlPoint pontoAux(x,y,z);
								auxPoints.push_back(pontoAux);
							}
							controlPointElement = controlPointElement->NextSiblingElement();
						}
						Primitive* patch1 = new Patch(order, partsU, partsV, compute, auxPoints);

						no->insertprimitive(patch1);
						
					}
					else if((string)infoChild->Value() == "hexagon"){

						printf("\tEncontrou Hexagono\n");

						//Primitive* h1 = new Hexagon();

						//no->insertprimitive(h1);

					}
					else if((string)infoChild->Value() == "triangle"){

						printf("\tEncontrou Triangulo\n");

						float p1x, p1y, p1z;
						string ponto1;
						ponto1 = infoChild->Attribute("xyz1");
						sscanf(ponto1.c_str(), "%f %f %f", &p1x, &p1y, &p1z);

						float p2x, p2y, p2z;
						string ponto2;
						ponto2 = infoChild->Attribute("xyz2");
						sscanf(ponto2.c_str(), "%f %f %f", &p2x, &p2y, &p2z);

						float p3x, p3y, p3z;
						string ponto3;
						ponto3 = infoChild->Attribute("xyz3");
						sscanf(ponto3.c_str(), "%f %f %f", &p3x, &p3y, &p3z);

						Primitive* t1 = new Triangle(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);

						no->insertprimitive(t1);

					}
					else if((string)infoChild->Value() == "cylinder"){

						printf("\tEncontrou Cilindro\n");
						// TODO: IF's

						float base, top, height, slices, stacks;

						string aux;
						aux = infoChild->Attribute("base");
						sscanf(aux.c_str(), "%f", &base);

						aux = infoChild->Attribute("top");
						sscanf(aux.c_str(), "%f", &top);
						aux = infoChild->Attribute("height");
						sscanf(aux.c_str(), "%f", &height);
						aux = infoChild->Attribute("slices");
						sscanf(aux.c_str(), "%f", &slices);
						aux = infoChild->Attribute("stacks");
						sscanf(aux.c_str(), "%f", &stacks);



						Primitive* c1 = new Cylinder(base, top, height, slices, stacks);
						no->insertprimitive(c1);

					}
					else if((string)infoChild->Value() == "rectangle"){
						printf("\tEncontrou Rectangulo\n");
						float x1, y1, x2, y2;
						string p1, p2;
						p1 = infoChild->Attribute("xy1");
						p2 = infoChild->Attribute("xy2");

						cout<<"P1: "<<p1<<" P2: "<<p2<<endl;

						sscanf(p1.c_str(), "%f %f", &x1, &y1);
						sscanf(p2.c_str(), "%f %f", &x2, &y2);

						cout<<"X1: "<<x1<<" X2: "<<x2<<" Y1: "<<y1<<" y2: "<<y2<<endl;

						Primitive* r1 = new Rectangle(x1,y1,x2,y2);
						no->insertprimitive(r1);
					}
					else if((string)infoChild->Value() == "sphere"){

						float radius, slices, stacks;

						string aux;

						aux = infoChild->Attribute("radius");
						sscanf(aux.c_str(), "%f", &radius);
						aux = infoChild->Attribute("slices");
						sscanf(aux.c_str(), "%f", &slices);
						aux = infoChild->Attribute("stacks");
						sscanf(aux.c_str(), "%f", &stacks);




						Sphere* e1 = new Sphere(radius, slices, stacks);
						no->insertprimitive(e1);
					}
					else if((string)infoChild->Value() == "torus")
					{
						float loops;
						float slices, inner,outer;



						string aux;

						aux = infoChild->Attribute("loops");
						sscanf(aux.c_str(), "%f", &loops);
						aux = infoChild->Attribute("slices");
						sscanf(aux.c_str(), "%f", &slices);
						aux = infoChild->Attribute("inner");
						sscanf(aux.c_str(), "%f", &inner);
						aux = infoChild->Attribute("outer");
						sscanf(aux.c_str(), "%f", &outer);



						Torus* t1 = new Torus(inner,outer,slices,loops);
						no->insertprimitive(t1);
					}

					infoChild = infoChild->NextSiblingElement();

				}

				children = children->NextSiblingElement();
			}

			
			int pickingId = (int)no->getPicking();
			if(pickingId > 10 && pickingId < 20){
				scene->bluePods.push_back(no);
			}
			else if(pickingId > 20 && pickingId < 30){
				scene->redPods.push_back(no);
			}
			else if(pickingId == 122 || pickingId == 124 || pickingId == 126 || pickingId == 162 || pickingId == 164 || pickingId == 166){
				scene->octiCells.push_back(no);
			}
			else if(pickingId > 110 && pickingId < 178){
				scene->tabCells.push_back(no);
			}
			else if(pickingId > 210 && pickingId < 219){
				scene->bPickProng.push_back(no);
			}
			else if(pickingId > 220 && pickingId < 229){
				scene->rPickProng.push_back(no);
			}
			if(no->getId() == "envolvente"){
				scene->envolente = no;
			}
			else if(no->getId() == "menuVitoria"){
				scene->menuVitoria = no;
			}

			scene->graph.insert(std::pair<string,Node*>(no->getId(),no));
			node=node->NextSiblingElement();
		}
	}

	
	//scene->setappearancesherity(scene->rootid);
	printf("");
	
}


void XMLScene::init()
{

	scene->initGlobals();
	scene->initCameras();
	scene->switchTheme();
	scene->initLights();
	//scene->initAnimations();
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	scene->initposition(scene->rootid);
	glPopMatrix();
	scene->defaultGraph = scene->graph;
	char * host = "Leonel";
	connectToSocket(host);
	setUpdatePeriod(30);
	app->forceRefresh();
	vector<Appearance*> appearancesStack;
	scene->createdisplays(scene->rootid,appearancesStack);
	//octi = new Game();
	octi->createBoard();
	//octi->displayBoard();
	
}
	

void XMLScene::update(unsigned long	tempo)
{
		
	bool doingcenas=false;
	vector<Appearance*> appearancesStack;
	

	for (map<Animation*,vector<Node*> >::iterator it=scene->graphanimation.begin(); it!=scene->graphanimation.end(); ++it)
	{
		for(unsigned int i=0;i<it->second.size();i++)
		{
			//cout<<"X "<<((LinearAnimation*)it->first)->x<<"Y "<<((LinearAnimation*)it->first)->y<<"Z "<<((LinearAnimation*)it->first)->z<<endl;
			//cout<<"VX "<<((LinearAnimation*)it->first)->vx<<"VY "<<((LinearAnimation*)it->first)->vy<<"VZ "<<((LinearAnimation*)it->first)->vz<<endl;
			//cout<<"Control Point "<<((LinearAnimation*)it->first)->numbercontrol<<endl;
			if(it->second[i]->toanimate)
			{
				it->second[i]->move(it->first,tempo);
				doingcenas=true;
			}
			else
			{
				//cout<<"ELIMINOU"<<endl;
				it->second.erase(it->second.begin()+i);
			}
			
		}
		
	}


	if(!doingcenas && octi->lastturn!=octi->turn)
	{
		if(octi->dificuldade == -1){
			octi->rotateCamera(getScenePointer(), octi->turn);
			octi->lastturn=octi->turn;
		}

	}
	for(int i = 0; i < scene->camerasComp.size(); i++){
		if(scene->camerasComp[i]->getid() == "camJogadorAzul"){
			if(((Perspective *)scene->camerasComp[i])->toanimate == true){
				cout << octi->turn << endl;
				((Perspective *)scene->camerasComp[i])->update(octi->turn);
				scene->itActiveCamera = i;
				
				//cout << "Encontrei! " << endl;
			}
		}
	}
	
	scene->draw(scene->rootid,appearancesStack);


}



void XMLScene::refreshCameras(){

	cout<<"Alterou Camera: "<<scene->itActiveCamera<<endl;
	activeCamera = scene->camerasComp.at(scene->itActiveCamera);
	
}

void XMLScene::setLightState(int pos)
{ 

	if(scene->lightsState.at(pos) == 0)
	{ 
		scene->lightsComp.at(pos)->disable(); 
		//cout<<"NAO"<<GL_LIGHT0<<endl;
		//lightsComp.at(pos)->setEnabled(false);
	} 
	else{ 
		scene->lightsComp.at(pos)->enable();
		//cout<<"SIM"<<lightsComp.at(pos)->enable()<<endl;
		//lightsComp.at(pos)->setEnabled(true); 
	} 
	//app->forceRefresh();
}



void XMLScene::display(){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation)
	// Apply transformations corresponding to the camera position relative to the origin

	switch(scene->mode){
	case 0: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case 1: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case 2: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;

	}

	
	//app->forceRefresh();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Lights Processing
	std::vector<Light*>::iterator it = scene->lightsComp.begin();
	for(it; it != scene->lightsComp.end(); it++){
		if((*it)->getEnabled() == true){
			(*it)->enable();
			(*it)->draw();
		}
		(*it)->update();
	}


	scene->camerasComp.at(scene->itActiveCamera)->applyView();
	//CGFscene::activateCamera(0);
	//CGFscene::activeCamera->applyView();
	//cout << "IT    : " << scene->itActiveCamera << endl;
	//cout << "CAMARA: " << scene->camerasComp.at(scene->itActiveCamera)->getid() << endl;
	
	
	

	
	// Draw axis
	//axis.draw();

	
	vector<Appearance*> appearancesStack;



	scene->draw(scene->rootid,appearancesStack);




	// We have been drawing in a memory area that is not visible - the back buffer,
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}


XMLScene::~XMLScene()
{
	delete(doc);
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
	// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
	// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}




bool XMLScene::doinganimations()
{
		
	bool doingcenas=false;
	vector<Appearance*> appearancesStack;
	

	for (map<Animation*,vector<Node*> >::iterator it=scene->graphanimation.begin(); it!=scene->graphanimation.end(); ++it)
	{
		for(unsigned int i=0;i<it->second.size();i++)
		{
			//cout<<"X "<<((LinearAnimation*)it->first)->x<<"Y "<<((LinearAnimation*)it->first)->y<<"Z "<<((LinearAnimation*)it->first)->z<<endl;
			//cout<<"VX "<<((LinearAnimation*)it->first)->vx<<"VY "<<((LinearAnimation*)it->first)->vy<<"VZ "<<((LinearAnimation*)it->first)->vz<<endl;
			//cout<<"Control Point "<<((LinearAnimation*)it->first)->numbercontrol<<endl;
			if(it->second[i]->toanimate)
			{
				
				return true;
			}

			
		}
		
	}
	

	for(int i = 0; i < scene->camerasComp.size(); i++){
		if(scene->camerasComp[i]->getid() == "camJogadorAzul"){
			if(((Perspective *)scene->camerasComp[i])->toanimate == true){
				return true;
				
				//cout << "Encontrei! " << endl;
			}
		}
	}
	
	return false;


}
