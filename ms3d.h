#ifndef _ms3d_H_
#define _ms3d_H_

#include <ms3d/MS3DFile.h>
#include <ms3d/Textures.h>
#include <GL/glut.h>

class ms3d{
private:
	CMS3DFile* _model;

public: 
	ms3d(char* filename, bool overrideAmbient=false, bool overrideSpecular=false, bool overrideDiffuse=false, bool overrideEmissive=false);
	virtual ~ms3d();
	void draw();
	void drawGL3();
	void prepare(GLuint shader);
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
