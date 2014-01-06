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
		gluLookAt(position[0], position[1], position[2], target[0], target[1], target[2], 0.0, 1.0, 0.0);
}
 
void Perspective::updateProjectionMatrix(int width, int height) {
        float aspect = (float) width / (float) height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(angle, aspect, near, far);
 
}

void Perspective::update(int turn){

	if(turn == 1){
		if(rotation[CG_CGFcamera_AXIS_Y] < 360){
			this->setRotation(CG_CGFcamera_AXIS_Y, rotation[CG_CGFcamera_AXIS_Y] + 15);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glRotated(15,0,1,0);
			glTranslated(position[0],position[1],position[2]);

			float matrix[16];
			glGetFloatv(GL_MODELVIEW_MATRIX,matrix);

			position[0] = ( matrix[12] );
			position[1] = ( matrix[13] );
			position[2] = ( matrix[14] );
		//	cout << "Positions: " << endl;
			//cout << position[0] << endl;
			//cout << position[1] << endl;
			//cout << position[2] << endl << endl;

			glPopMatrix();
		//	std::cout << "VAI EM " << rotation[CG_CGFcamera_AXIS_Y] << endl;
		}
		else{
			this->setRotation(CG_CGFcamera_AXIS_Y, 0);
			toanimate = false;
		}
	}

	if(turn == 2){
		if(rotation[CG_CGFcamera_AXIS_Y] < 180){
			this->setRotation(CG_CGFcamera_AXIS_Y, rotation[CG_CGFcamera_AXIS_Y] + 15);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glRotated(15,0,1,0);
			
			glTranslated(position[0],position[1],position[2]);
			float matrix[16];
			glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
			
			position[0] = ( matrix[12] );
			position[1] = ( matrix[13] );
			position[2] = ( matrix[14] );
        
        
		//	cout << "Positions: " << endl;
		//	cout << position[0] << endl;
		//	cout << position[1] << endl;
		//	cout << position[2] << endl << endl;

			glPopMatrix();
		//	std::cout << "VAI EM " << rotation[CG_CGFcamera_AXIS_Y] << endl;
		}
		else{
			this->setRotation(CG_CGFcamera_AXIS_Y, 180);
			toanimate = false;
		}
	}
	
}