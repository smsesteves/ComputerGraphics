#include "node.h"

Node::Node()
{
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
	glPopMatrix();
	visited = false;
	app=NULL;
	isDisplayList = false;
	displayid=-1;
	hasdisplaylist=false;
	anim.clear();
	position[0]=0.0;
	position[1]=0.0;
	position[2]=0.0;
}


string Node::getId()
{
	return id;
}

void Node::createDisplayList(){
	//dList = new DisplayList(this);
}

void Node::setId(string newId)
{
	id=newId;
}

float* Node::getmatrix()
{
	return matrix;
}

void Node::setmatrix(float* nova)
{
	for(int i=0;i<16;i++)
	{
		matrix[i]=nova[i];
	}
}


string Node::getstringat(int n)
{
	return children.at(n);
}

void Node::insertstring(string aux)
{
	children.push_back(aux);
}

vector<string> Node::getchildren()
{
	return children;
}

void Node::insertprimitive(Primitive* primitiva)
{
	primitives.push_back(primitiva);
}


void Node::move(Animation* aux,unsigned long t)
{
	if(!((LinearAnimation*)aux)->started){aux->init(t);};
	aux->updatePosition(t);
}