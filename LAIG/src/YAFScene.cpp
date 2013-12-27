#include "YAFScene.h"
#include "CGFscene.h"
using namespace std;

void YAFScene::setLightConfig(Lighting* lightConfig){
	this->lightConfig = lightConfig;
}

void YAFScene::initLights(){

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	//ambient light
	float globalAmbientLight[4];
	globalAmbientLight[0]=lightConfig->getLightingAmbient().a;
	globalAmbientLight[1]=lightConfig->getLightingAmbient().b;
	globalAmbientLight[2]=lightConfig->getLightingAmbient().c;
	globalAmbientLight[3]=lightConfig->getLightingAmbient().d;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);
	
	//doublesided
	if(lightConfig->getDoublesided()){
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	}
	else if(lightConfig->getDoublesided() == false){
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	}

	//lights
	std::vector<Light*>::iterator it = lightsComp.begin();
	for(it; it != lightsComp.end(); it++){
		// SPOT
		if((*it)->lightingType() == 1){
			glLightf( ((Spot*)(*it))->getIdI(), GL_SPOT_EXPONENT, ((Spot*)(*it))->getSExponent());
			glLightf( ((Spot*)(*it))->getIdI(), GL_SPOT_CUTOFF, ((Spot*)(*it))->getSAngle());
		}
		//ORTHO
		//ALL
		if((*it)->getEnabled()) lightsState.push_back(1);
		else lightsState.push_back(0);

		(*it)->update();
	}
}

void YAFScene::initCameras(){

	std::vector<Cameras*>::iterator it = camerasComp.begin();

	for(unsigned int i= 0; i < camerasComp.size(); i++){
		if(camerasComp.at(i)->getInitial()){
			itActiveCamera = i;
			//activeCamera = camerasComp.at(itActiveCamera);
			break;
		}
	}
}

void YAFScene::draw(string node,vector<Appearance*> &appstack)
{


	glPushMatrix();
	glMultMatrixf(graph[node]->getmatrix());
	if(!graph[node]->getAnimationid().empty())
	{
		if(graph[node]->toanimate)
		{
			float incx=((LinearAnimation*)animationsComp[graph[node]->getAnimationid()])->x;
			float incy=((LinearAnimation*)animationsComp[graph[node]->getAnimationid()])->y;
			float incz=((LinearAnimation*)animationsComp[graph[node]->getAnimationid()])->z;
		

			float matrix[16] ;
			glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0]);
			glTranslated(incx,incy,incz);
		}

		//glTranslated(-graph[node]->getx(),-graph[node]->gety(),-graph[node]->getz());

		//cout<<" X: "<<graph[node]->getx()<<" Y: "<<graph[node]->gety()<<" Z: "<<graph[node]->getz()<<endl;
		//cout<<" Angle: "<<((LinearAnimation*)animationsComp[graph[node]->getAnimationid()])->ry<<endl;
		//cout<<" X: "<<incx<<" Y: "<<incy<<" Z: "<<incz<<endl;
	}
	if(graph[node]->getIsDL())
	{
		glCallList(graph[node]->displayid);
		glPopMatrix();
		return;
	}


	bool newAppearance = false;

	if (graph[node]->getAppearance()) {
		appstack.push_back(graph[node]->getAppearance());
		newAppearance = true;
	}
	
	if(!appstack.empty())
	{
		appstack[appstack.size() - 1]->apply();
	}
	
	int i = 0;
	vector<Primitive*>::iterator it = graph[node]->primitives.begin();
	for(it; it !=  graph[node]->primitives.end(); it++){
		(*it)->draw();	
	}
	vector<string> children=graph[node]->getchildren();

	for(unsigned int i=0;i<children.size();i++)
	{
		
		if((int)graph[children[i]]->getPicking() > -1){
			glPushName(graph[children[i]]->getPicking());
			draw(graph[children[i]]->getId(),appstack);
			glPopName();
		}
		else
		{
			draw(graph[children[i]]->getId(),appstack);
		}
	}
	
	if (newAppearance && !appstack.empty())
		appstack.pop_back();
	
	glPopMatrix();
	
	return;
}

void YAFScene::resetvisited()
{
	/*
	for (auto& x: graph) {
		x.second->setvisited(false);
	}
	*/
	for (std::map<string,Node*>::iterator it=graph.begin(); it!=graph.end(); ++it){
		(*it).second->setvisited(false);
	}
	 
}

void YAFScene::initGlobals(){

	
	string cFace = globalsComp.getCullface();
	if(cFace != "none"){
		glEnable(GL_CULL_FACE);
		if(cFace == "front") glCullFace(GL_FRONT);
		else if(cFace == "back") glCullFace(GL_BACK);
		else if(cFace == "both") glCullFace(GL_FRONT_AND_BACK);
	}
	else glDisable(GL_CULL_FACE);

	
	string cOrder = globalsComp.getCullorder();
	if(cOrder == "CCW") glFrontFace(GL_CCW);
	else if(cOrder == "CW") glFrontFace(GL_CW);
	


	
	string cShade = globalsComp.getShading();
	if(cShade == "flat") glShadeModel(GL_FLAT);
	else if(cShade == "smooth") glShadeModel(GL_SMOOTH);

	
	string cDMode = globalsComp.getDMode();
	if(cDMode == "fill"){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mode = 0;
	}
	else if(cDMode == "line"){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mode = 1;

	}
	else if(cDMode == "point"){
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mode = 2;
	}
	glClearColor(globalsComp.getBG1(),globalsComp.getBG2(), globalsComp.getBG3(), globalsComp.getBG4());

}


void YAFScene::createdisplays(string node,vector<Appearance*>appstack)
{
	
	int maxChil=graph[node]->getchildren().size();

	bool newAppearance = false;

	if (graph[node]->getAppearance()) {
		appstack.push_back(graph[node]->getAppearance());
		newAppearance = true;
	}
	
	if(!graph[node]->getIsDL())
	{
		glMultMatrixf(graph[node]->getmatrix());
		if(!appstack.empty())
		{
			appstack[appstack.size() - 1]->apply();
		}
		vector<Primitive*>::iterator it = graph[node]->primitives.begin();

		for(it; it !=  graph[node]->primitives.end(); it++){
			(*it)->draw();	
		}

		vector<string> children=graph[node]->getchildren();

		for(unsigned int i=0;i<children.size();i++)
		{
			glPushMatrix();
			createdisplays(graph[children[i]]->getId(),appstack);
			glPopMatrix();
		}
	}
	else
	{
		if(graph[node]->getIsDL() && !graph[node]->hasdisplaylist)
		{
			if(maxChil == 0)
			{
				graph[node]->hasdisplaylist=true;
				graph[node]->displayid = glGenLists(1);
				glNewList(graph[node]->displayid, GL_COMPILE);
				glMultMatrixf(graph[node]->getmatrix());
				if(!appstack.empty())
				{
					appstack[appstack.size() - 1]->apply();
				}
				vector<Primitive*>::iterator it = graph[node]->primitives.begin();

				for(it; it !=  graph[node]->primitives.end(); it++){
					(*it)->draw();	
				}
				glEndList();
			}
			else
			{
				glPushMatrix();
				glMultMatrixf(graph[node]->getmatrix());
				if(!appstack.empty())
				{
					appstack[appstack.size() - 1]->apply();
				}
				vector<Primitive*>::iterator it = graph[node]->primitives.begin();

				for(it; it !=  graph[node]->primitives.end(); it++){
					(*it)->draw();	
				}

				vector<string> children=graph[node]->getchildren();

				for(unsigned int i=0;i<children.size();i++)
				{
					glPushMatrix();
					createdisplays(graph[children[i]]->getId(),appstack);
					glPopMatrix();
				}
				glPopMatrix();
				
				graph[node]->displayid= glGenLists(1) ;
				glNewList(graph[node]->displayid, GL_COMPILE);
				graph[node]->hasdisplaylist=true;
				glPushMatrix();
				glMultMatrixf(graph[node]->getmatrix());
				if(!appstack.empty())
				{
					appstack[appstack.size() - 1]->apply();
				}
				
				it = graph[node]->primitives.begin();
				for(it; it !=  graph[node]->primitives.end(); it++){
					(*it)->draw();	
				}
				
				children=graph[node]->getchildren();

				for(unsigned int i=0;i<children.size();i++)
				{
					glPushMatrix();
					createdisplays(graph[children[i]]->getId(),appstack);
					glPopMatrix();
				}
				glPopMatrix();
				glEndList();

			}
		}
		else if(graph[node]->getIsDL() && graph[node]->hasdisplaylist)
		{
			glCallList( graph[node]->displayid);
		}
	}
	if (newAppearance && !appstack.empty())
		appstack.pop_back();
	return;
}

void YAFScene::initInterfaceAnim(int ida){
	int i=0;
	for (map<string,Animation*>::iterator it=animationsComp.begin(); it!=animationsComp.end(); ++it, i++)
	{
		if(i == ida){
			((LinearAnimation*)(it->second))->started = false;
		}


	}
}

void YAFScene::initAnimations()
{
	for (map<string,Animation*>::iterator it=animationsComp.begin(); it!=animationsComp.end(); ++it)
	{
		for (map<string,Node*>::iterator it2=graph.begin(); it2!=graph.end(); ++it2)
		{

			if(it->first==it2->second->getAnimationid())
			{

				//Verifica se existe
				bool encontra=false;
			
				for(map<Animation*,vector<Node*> >::iterator novo=graphanimation.begin(); novo!=graphanimation.end();++novo)
				{
					if(novo->first==it->second)
					{
						encontra=true;
						break;
					}
					
				}
				if(!encontra)
				{
					if(it->second->animationType() == 0){
			

						
						float tempoTotal = it->second->getSpan();
						float distanciatotal=0;
						vector<ControlPoint> aux= ((LinearAnimation*)(it->second))->controlPoints;
						for(unsigned int j = 0; j < ((LinearAnimation*)(it->second))->controlPoints.size() -1 ; j++){
							//cout << "\tde " << j << " a " << j+1 << endl;
							distanciatotal+=distanciapontos(aux[j].x,aux[j].y,aux[j].z,aux[j+1].x,aux[j+1].y,aux[j+1].z);
							
						}



						
						for(unsigned int j = 0; j < ((LinearAnimation*)(it->second))->controlPoints.size() -1 ; j++){
							//cout << "\tde " << j << " a " << j+1 << endl;
							velocidadescomp v1;
							v1.number1=j;
							v1.number2=j+1;
							v1.time=tempoTotal*distanciapontos(aux[j].x,aux[j].y,aux[j].z,aux[j+1].x,aux[j+1].y,aux[j+1].z)/distanciatotal;
							v1.vx=abs(aux[j+1].x-aux[j].x)/v1.time;
							v1.vy=abs(aux[j+1].y-aux[j].y)/v1.time;
							v1.vz=abs(aux[j+1].z-aux[j].z)/v1.time;
							
							((LinearAnimation*)(it->second))->velocidades.push_back(v1);
						}
						
						vector<Node*> aux2;
						aux2.push_back(it2->second);
						graphanimation.insert(pair<Animation*,vector<Node*> >(it->second,aux2));	
					}
			
				}
				else
				{
					graphanimation[it->second].push_back(it2->second);
				}
			}
		}
	}
}


void YAFScene::initposition(string node)
{       
	
		vector<string> children=graph[node]->getchildren();
        for(unsigned int i=0;i<children.size();i++)
        {
			glPushMatrix();
                initposition(graph[children[i]]->getId());
			glPopMatrix();
        }


        glMultMatrixf(graph[node]->getmatrix());
        float matrix[16] ;//=graph[node]->getmatrix();
        glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0]);

        float resX = graph[node]->incposx( matrix[0], matrix[4], matrix[8], matrix[12] );
        float resY = graph[node]->incposy( matrix[1], matrix[5], matrix[9], matrix[13] );
        float resZ = graph[node]->incposz( matrix[2], matrix[6], matrix[10], matrix[14] );
        

        graph[node]->setx(resX);
        graph[node]->sety(resY);
        graph[node]->setz(resZ);

        

        return;

}

void YAFScene::resetScene(){
	this->graph = this->defaultGraph;
	this->graphanimation.clear();

	

	vector<Appearance*> appearancesStack;
	this->createdisplays(this->rootid,appearancesStack);
	//octi = new Game();
}

void YAFScene::switchTheme(){
	Appearance* aux_hl = new Appearance();
	Appearance* aux_hl_outro = new Appearance();
	/*********
	// FOREST
	**********/
	if(nextTheme == 1){ 
		for(int i = 0; i < this->appearancesComp.size(); i++){
			if(appearancesComp[i]->getIdS() == "forest_highlight"){
				aux_hl = appearancesComp[i];
			}
			if(appearancesComp[i]->getIdS() == "forest_hl_peca"){
				aux_hl_outro = appearancesComp[i];
			}
			if(appearancesComp[i]->getIdS() == "bg_Forest"){
				envolente->setAppearance(appearancesComp[i]);
				envolente->notHighlighted = appearancesComp[i];
			}
		}

		for(int i = 0; i < this->appearancesComp.size(); i++){
			// Tabuleiro
			if(appearancesComp[i]->getIdS() == "forest_celula"){
				for(int j = 0; j < this->tabCells.size(); j++){
					tabCells[j]->setAppearance(appearancesComp[i]);
					tabCells[j]->notHighlighted = appearancesComp[i];
					tabCells[j]->highlighted = aux_hl;
				}
			}
			if(appearancesComp[i]->getIdS() == "forest_casa_octi"){
				for(int j = 0; j < this->octiCells.size(); j++){
					octiCells[j]->setAppearance(appearancesComp[i]);
					octiCells[j]->notHighlighted = appearancesComp[i];
					octiCells[j]->highlighted = aux_hl;
				}
			}
			if(appearancesComp[i]->getIdS() == "forest_red"){
				for(int j = 0; j < this->redPods.size(); j++){
					redPods[j]->setAppearance(appearancesComp[i]);
					redPods[j]->notHighlighted = appearancesComp[i];
					redPods[j]->highlighted = aux_hl_outro;
				}
				for(int j = 0; j < this->rPickProng.size(); j++){
					rPickProng[j]->setAppearance(appearancesComp[i]);
					rPickProng[j]->notHighlighted = appearancesComp[i];
					rPickProng[j]->highlighted = aux_hl_outro;
				}
			}
			if(appearancesComp[i]->getIdS() == "forest_blue"){
				for(int j = 0; j < this->bluePods.size(); j++){
					bluePods[j]->setAppearance(appearancesComp[i]);
					bluePods[j]->notHighlighted = appearancesComp[i];
					bluePods[j]->highlighted = aux_hl_outro;
				}
				for(int j = 0; j < this->bPickProng.size(); j++){
					bPickProng[j]->setAppearance(appearancesComp[i]);
					bPickProng[j]->notHighlighted = appearancesComp[i];
					bPickProng[j]->highlighted = aux_hl_outro;
				}
			}
		}
		nextTheme = 2;
	}
	/*********
	// CBBLE
	**********/
	else if(nextTheme == 2){ 
		for(int i = 0; i < this->appearancesComp.size(); i++){
			if(appearancesComp[i]->getIdS() == "cbble_highlight"){
				aux_hl = appearancesComp[i];
			}
			if(appearancesComp[i]->getIdS() == "cbble_hl_peca"){
				aux_hl_outro = appearancesComp[i];
			}
			if(appearancesComp[i]->getIdS() == "bg_Cobble"){
				envolente->setAppearance(appearancesComp[i]);
				envolente->notHighlighted = appearancesComp[i];
			}
		}
		for(int i = 0; i < this->appearancesComp.size(); i++){
			// Tabuleiro
			if(appearancesComp[i]->getIdS() == "cbble_celula"){
				for(int j = 0; j < this->tabCells.size(); j++){
					tabCells[j]->setAppearance(appearancesComp[i]);
					tabCells[j]->notHighlighted = appearancesComp[i];
					tabCells[j]->highlighted = aux_hl;
				}
			}
			if(appearancesComp[i]->getIdS() == "cbble_octi"){
				for(int j = 0; j < this->octiCells.size(); j++){
					octiCells[j]->setAppearance(appearancesComp[i]);
					octiCells[j]->notHighlighted = appearancesComp[i];
					octiCells[j]->highlighted = aux_hl;
				}
			}
			if(appearancesComp[i]->getIdS() == "cbble_appPecaVermelha"){
				for(int j = 0; j < this->redPods.size(); j++){
					redPods[j]->setAppearance(appearancesComp[i]);
					redPods[j]->notHighlighted = appearancesComp[i];
					redPods[j]->highlighted = aux_hl_outro;
				}
				for(int j = 0; j < this->rPickProng.size(); j++){
					rPickProng[j]->setAppearance(appearancesComp[i]);
					rPickProng[j]->notHighlighted = appearancesComp[i];
					rPickProng[j]->highlighted = aux_hl_outro;
				}
			}
			if(appearancesComp[i]->getIdS() == "cbble_appPecaAzul"){
				for(int j = 0; j < this->bluePods.size(); j++){
					bluePods[j]->setAppearance(appearancesComp[i]);
					bluePods[j]->notHighlighted = appearancesComp[i];
					bluePods[j]->highlighted = aux_hl_outro;
				}
				for(int j = 0; j < this->bPickProng.size(); j++){
					bPickProng[j]->setAppearance(appearancesComp[i]);
					bPickProng[j]->notHighlighted = appearancesComp[i];
					bPickProng[j]->highlighted = aux_hl_outro;
				}
			}
		}


		nextTheme = 1;
	}
	else if(nextTheme == 3){

	}
}