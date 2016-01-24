#include "ms3d.h"

shader::shader(char* vertShader, char* fragShader){
	_shader = new Shader(vertShader, fragShader);
}

shader::~shader(){
	delete _shader;
}

GLuint shader::getShader(){
	return _shader->getShader();
}
