#ifndef _ms3d_H_
#define _ms3d_H_

#include <stack>
#include <ms3d/MS3DFile.h>
#include <ms3d/Textures.h>
#include <ms3d/Shader.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

class GLM{
private:
	Shader* _shader;

	glm::mat4 _Model;
	glm::mat4 _View;
	glm::mat4 _Projection;

	glm::mat4* _activeMatrix;
	int _activeMatrixID;

	GLuint _modelID;
	GLuint _viewID;
	GLuint _projectionID;

	std::stack<glm::mat4> _stack;

public:
	GLM(Shader* shader);
	virtual ~GLM();

	void selectMatrix(int Matrix);
	void perspective(double fov_degrees, double aspect_ratio, double near, double far);
	//void otho(...)
	void loadIdentity();
	void translate(double x, double y, double z);
	void rotate(float angle, double x, double y, double z);
	void pushMatrix();
	void popMatrix();
private:
	void uploadMatrix();
};

#endif
