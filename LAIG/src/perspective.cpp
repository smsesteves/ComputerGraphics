#include "perspective.h"

void Perspective::setCAngle(float angle){
	this->angle = angle;
}

void Perspective::setCTarget(float t1, float t2, float t3){
	this->target[0] = t1;
	this->target[1] = t2;
	this->target[2] = t3;
}

void Perspective::applyView() {
        gluLookAt(position[0], position[1], position[2], target[0], target[1], target[2], 1, 0, 0);
}
 
void Perspective::updateProjectionMatrix(int width, int height) {
        float aspect = (float) width / (float) height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(angle, aspect, near, far);
 
}