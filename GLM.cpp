#include "ms3d.h"
#include <GLES3/gl3.h>

#define MODEL 1
#define VIEW 2
#define PROJECTION 3

GLM::GLM(shader* shader){
	_shader = shader;

	_Model = glm::mat4(1.0f);
	_View = glm::mat4(1.0f);
	_Projection = glm::mat4(1.0f);
	
	
	_modelID = glGetUniformLocation( _shader->getShader(), "Model" );
	_viewID = glGetUniformLocation( _shader->getShader(), "View" );
	_projectionID = glGetUniformLocation( _shader->getShader(), "Projection");
	
	//Get the identities loaded up...
	glUniformMatrix4fv(_modelID, 1, GL_FALSE, glm::value_ptr(_Model));
	glUniformMatrix4fv(_viewID, 1, GL_FALSE, glm::value_ptr(_View));
	glUniformMatrix4fv(_projectionID, 1, GL_FALSE, glm::value_ptr(_Projection));

	_activeMatrix = &_Projection;
}

GLM::~GLM(){
	//Maybe do something here?
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
	glUniformMatrix4fv(_projectionID, 1, GL_FALSE, glm::value_ptr(_Projection));
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
	*(_activeMatrix) = glm::rotate(*(_activeMatrix), angle, glm::vec3(x, y, z));
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
	else if(_activeMatrixID == PROJECTION)
		glUniformMatrix4fv(_projectionID, 1, GL_FALSE, glm::value_ptr(_Projection));
}
