
#include "ms3d.h"

ms3d::ms3d(char* filename){
	_model = new CMS3DFile();
	_model->LoadFromFile(filename);
}

ms3d::~ms3d(){
	_model->Clear();
	delete _model;
}

void ms3d::draw(){
	_model->draw();
}
