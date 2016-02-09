#ifndef _GLM_H_
#define _GLM_H_

#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>

#define MODEL 1
#define VIEW 2
#define PROJECTION 3

class GLM{
private:
	shader* _shader;

	glm::mat4 _Model;
	glm::mat4 _View;
	glm::mat4 _Projection;

	glm::mat4* _activeMatrix;
	int _activeMatrixID;

	GLuint _modelID;
	GLuint _viewID;
	//GLuint _projectionID;
	GLuint _MVPID;

	std::stack<glm::mat4> _stack;

public:
	GLM(shader* shader);
	virtual ~GLM();

	void selectMatrix(int Matrix);
	void perspective(double fov_degrees, double aspect_ratio, double near, double far);
	void otho(double left, double right, double bottom, double top, double near, double far);
	void lookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ);
	void loadIdentity();
	void translate(double x, double y, double z);
	void rotate(float angle, double x, double y, double z);
	void scale(double x, double y, double z);
	void billboard(double x, double y, double z);
	void pushMatrix();
	void popMatrix();
	void changeShader(shader* newShader);
	glm::mat4 getMVP();
private:
	void uploadMatrix();
	void uploadMVP();
};

#endif
