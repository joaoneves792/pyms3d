
#include "ms3d.h"

ms3d::ms3d(char* filename, bool overrideAmbient, bool overrideSpecular, bool overrideDiffuse, bool overrideEmissive){
	_model = new CMS3DFile();
	_model->LoadFromFile(filename);
	_model->setOverrideAmbient(overrideAmbient);
	_model->setOverrideDiffuse(overrideDiffuse);
	_model->setOverrideSpecular(overrideSpecular);
	_model->setOverrideEmissive(overrideEmissive);
}

ms3d::~ms3d(){
	_model->Clear();
	delete _model;
}

void ms3d::draw(){
	_model->draw();
}

void ms3d::drawGL3(){
	_model->drawGL3();
}

void ms3d::prepare(GLuint shader){
	_model->prepareModel(shader);
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

void ms3d::changeTexture(char* groupName, char* textureFile){
	ms3d_group_t* group = NULL;
	int newTexture = LoadGLTexture(textureFile);
	int groupId = _model->FindGroupByName(groupName);
	_model->GetGroupAt(groupId, &group);
	_model->setMaterial(newTexture, group);
}
