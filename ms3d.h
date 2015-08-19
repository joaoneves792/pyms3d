#ifndef _ms3d_H_
#define _ms3d_H_

#include "MS3DFile.h"
#include "Textures.h"

class ms3d{
private:
	CMS3DFile* _model;

public: 
	ms3d(char* filename, bool overrideAmbient=false, bool overrideSpecular=false, bool overrideDiffuse=false, bool overrideEmissive=false);
	virtual ~ms3d();
	void draw();
	float* getJointPosition(char* jointName);
	void changeTexture(char* groupName, char* textureFile);
};

class Tex{
private:
	int _tex;
public:
	Tex(char* filename);
	int getTexture();
};
#endif
