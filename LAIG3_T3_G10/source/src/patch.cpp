#include "patch.h"


GLfloat patch_textpoints[4][2] = {	
{ 0.0, 0.0},
{ 0.0, 1.0}, 
{ 1.0, 0.0},
{ 1.0, 1.0} };


Patch::Patch(int order, int partsU, int partsV, string compute, vector<ControlPoint> controlPoints){
	this->order = order+1;
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
	this->controlPoints = controlPoints;
	this->ctrlPoints = setControlPointsGL();
};

Patch::~Patch()
{
}


GLfloat* Patch::setControlPointsGL(){
	int dim = controlPoints.size();
	GLfloat* novospontos;
	novospontos = (GLfloat*)(malloc(dim * 3 * sizeof(GLfloat)));

	for(int i = 0; i < dim; i++){
		
		novospontos[i*3] = (GLfloat) controlPoints.at(i).x;
		novospontos[i*3+1] = (GLfloat) controlPoints.at(i).y;
		novospontos[i*3+2] = (GLfloat) controlPoints.at(i).z;

		cout << i*3 << "  "  << novospontos[i*3] << endl;
		cout << i*3+1 << "  "  << novospontos[i*3+1] << endl;
		cout << i*3+2 << "  "  << novospontos[i*3+2] << endl;
	};

	return novospontos;
}


void Patch::draw()
{


	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_TEXTURE_2D);
	GLint currentCullFace;
	glGetIntegerv(GL_CULL_FACE_MODE, &currentCullFace);
	glEnable(GL_CCW);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order,  0.0, 1.0, 3*order, order,  &ctrlPoints[0]);
	glEnable(GL_CW);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &patch_textpoints[0][0]);
	glMapGrid2f(partsU, 0.0,1.0, partsV, 0.0,1.0); 
		
	if(compute == "fill") glEvalMesh2(GL_FILL, 0,partsU, 0,partsV);	
	if(compute == "line") glEvalMesh2(GL_LINE, 0,partsU, 0,partsV);	
	if(compute == "point") glEvalMesh2(GL_POINT, 0,partsU, 0,partsV);	
	

	glEnable(currentCullFace);
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
}
