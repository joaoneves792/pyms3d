#ifndef _ms3d_H_
#define _ms3d_H_

#include <ms3d/MS3DFile.h>
#include <ms3d/Textures.h>
#include <ms3d/Shader.h>
#include <GL/glut.h>

class shader{
private:
	Shader* _shader;
public:
	shader(char* vertShader, char* fragShader);
	virtual ~shader();
	GLuint getShader();
};

class ms3d{
private:
	CMS3DFile* _model;

public: 
	ms3d(char* filename, bool overrideAmbient=false, bool overrideSpecular=false, bool overrideDiffuse=false, bool overrideEmissive=false);
	virtual ~ms3d();
	void draw();
	void drawGL3();
	void prepare(Shader* shader);
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
