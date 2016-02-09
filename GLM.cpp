#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GL/glew.h>
#include <stack>
#include "GLM.h"
#include "shader.h"

GLM::GLM(shader* shader){
	_Model = glm::mat4(1.0f);
	_View = glm::mat4(1.0f);
	_Projection = glm::mat4(1.0f);
	changeShader(shader);	
	
	//Get the identities loaded up...
	glUniformMatrix4fv(_modelID, 1, GL_FALSE, glm::value_ptr(_Model));
	glUniformMatrix4fv(_viewID, 1, GL_FALSE, glm::value_ptr(_View));
	//glUniformMatrix4fv(_projectionID, 1, GL_FALSE, glm::value_ptr(_Projection));
	uploadMVP();

	_activeMatrix = &_Projection;
}


GLM::~GLM(){
	//Maybe do something here?
}

void GLM::changeShader(shader* newShader){
	_shader = newShader;
	_modelID = glGetUniformLocation( _shader->getShader(), "Model" );
	_viewID = glGetUniformLocation( _shader->getShader(), "View" );
	//_projectionID = glGetUniformLocation( _shader->getShader(), "Projection");
	

	_MVPID = glGetUniformLocation( _shader->getShader(), "MVP");
}

void GLM::selectMatrix(int Matrix){
	if(Matrix == MODEL)
		_activeMatrix = &_Model;
	else if(Matrix == VIEW)
		_activeMatrix = &_View;
	else if(Matrix == PROJECTION)
		_activeMatrix = &_Projection;
	else
		return;
	_activeMatrixID = Matrix;
}

void GLM::perspective(double fov_degrees, double aspect_ratio, double near, double far){
	_Projection = glm::perspective(glm::radians(fov_degrees), aspect_ratio, near, far);
	uploadMVP();
}

void GLM::otho(double left, double right, double bottom, double top, double near, double far){
	_Projection = glm::ortho(left, right, bottom, top, near, far);
	uploadMVP();
}

void GLM::lookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ){
	_View = glm::lookAt(glm::vec3(eyeX, eyeY, eyeZ), glm::vec3(centerX, centerY, centerZ), glm::vec3(upX, upY, upZ));
	glUniformMatrix4fv(_viewID, 1, GL_FALSE, glm::value_ptr(_View));
}

void GLM::loadIdentity(){
	*(_activeMatrix) = glm::mat4(1.0f);
	uploadMatrix();
}

void GLM::translate(double x, double y, double z){
	*(_activeMatrix) = glm::translate(*(_activeMatrix), glm::vec3(x, y, z));
	uploadMatrix();
}
void GLM::rotate(float angle, double x, double y, double z){
	*(_activeMatrix) = glm::rotate(*(_activeMatrix), glm::radians(angle), glm::vec3(x, y, z));
	uploadMatrix();
}

void GLM::scale(double x, double y, double z){
	*(_activeMatrix) = glm::scale(*(_activeMatrix), glm::vec3(x, y, z));
	uploadMatrix();
}

void GLM::billboard(double x, double y, double z){
	//Transpose the rotation of the View matrix (effectively its inverse)

	_Model[0][0] = _View[0][0];
	_Model[1][0] = _View[0][1];
	_Model[2][0] = _View[0][2];
	_Model[3][0] = x;

	_Model[0][1] = _View[1][0];
	_Model[1][1] = _View[1][1];
	_Model[2][1] = _View[1][2];
	_Model[3][1] = y;
	
	_Model[0][2] = _View[2][0];
	_Model[1][2] = _View[2][1];
	_Model[2][2] = _View[2][2];
	_Model[3][2] = z;

	_Model[0][3] = 0;
	_Model[1][3] = 0;
	_Model[2][3] = 0;
	_Model[3][3] = 1;

	uploadMatrix();
}

void GLM::pushMatrix(){
	_stack.push(*(_activeMatrix));
}

void GLM::popMatrix(){
	*(_activeMatrix) = _stack.top();
	_stack.pop();
	uploadMatrix();
}

void GLM::uploadMatrix(){
	if(_activeMatrixID == MODEL)
		glUniformMatrix4fv(_modelID, 1, GL_FALSE, glm::value_ptr(_Model));
	else if(_activeMatrixID == VIEW)
		glUniformMatrix4fv(_viewID, 1, GL_FALSE, glm::value_ptr(_View));
	uploadMVP();
}

void GLM::uploadMVP(){
	glUniformMatrix4fv(_MVPID, 1, GL_FALSE, glm::value_ptr(getMVP()));
}

glm::mat4 GLM::getMVP(){
	return _Projection * _View * _Model;
}
