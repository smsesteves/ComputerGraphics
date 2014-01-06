#include "GL/glew.h"
#include "waterline.h"
#include "ctime"


Waterline::~Waterline(){}

Waterline::Waterline(string hm, string tm, string fshader, string vshader){

	this->heightmap = hm;
	this->texturemap = tm;
	this->fragmentshader = fshader;
	this->vertexshader = vshader;

	p1 = new Plane(5);
	t=0;
	init(vshader.c_str(),fshader.c_str());
	baseTexture=new CGFtexture(this->texturemap);
	secTexture=new CGFtexture(this->heightmap);


	CGFshader::bind();

	
	baseImageLoc = glGetUniformLocation(id(), "tImage");
	glUniform1i(baseImageLoc, 0);
	secImageLoc = glGetUniformLocation(id(), "hImage");
	glUniform1i(secImageLoc, 1);



}



void Waterline::bind()
{
	CGFshader::bind();

	t+=0.003;
	update(t);
	
	glActiveTexture(GL_TEXTURE0);
	baseTexture->apply();
	glActiveTexture(GL_TEXTURE1);
	secTexture->apply();
	glActiveTexture(GL_TEXTURE0);
	


	p1->draw();	
	unbind();

}

void Waterline::draw(){
	this->bind();

}