
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

float* ms3d::getJointPosition(char* jointName){
	float* position = new float [3];
	
	int jointId = _model->FindJointByName(jointName);
	
	if( jointId == -1){ //Joint not found return 0s
		for(int i=0;i<3;i++)
			position[i] = 0;
		return position;	
	}

	ms3d_joint_t* joint;
	_model->GetJointAt(jointId, &joint);
	
	position[0] = joint->position[0];
	position[1] = joint->position[1];
	position[2] = joint->position[2];

	return position;	
}

