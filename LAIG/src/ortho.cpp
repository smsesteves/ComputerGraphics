#include "ortho.h"

void Ortho::setCFloatValues(float left, float right, float top, float bottom){
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

void Ortho::applyView(){ 

}

void Ortho::updateProjectionMatrix(int width, int height) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(left, right, bottom, top, near, far);
}