#ifndef _ms3d_H_
#define _ms3d_H_

#include "MS3DFile.h"

class ms3d{
private:
	CMS3DFile* _model;

public: 
	ms3d(char* filename);
	virtual ~ms3d();
	void draw();
	float* getJointPosition(char* jointName);
};
#endif
