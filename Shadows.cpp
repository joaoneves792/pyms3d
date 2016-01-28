#include "ms3d.h"

Shadows::Shadows(GLM* glm, shader* normalShader, shader* shadowMapShader, int window_width, int window_height){
	_glm = glm;
	_normalShader = normalShader;
	_shadowMapShader = shadowMapShader;
	_windowSize[0] = window_width;
	_windowSize[1] = window_height;

	_depthBiasMVPID = glGetUniformLocation( normalShader->getShader(), "depthBiasMVP");
	_shadowMapID = glGetUniformLocation( normalShader->getShader(), "shadowMap" );

	glGenFramebuffers(1, &_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	glGenTextures(1, &_depthTexture);
        glBindTexture(GL_TEXTURE_2D, _depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthTexture, 0);
        glDrawBuffer(GL_NONE); // No color buffer is drawn to.

}

Shadows::~Shadows(){
	glDeleteTextures(1, &_depthTexture);
	glDeleteFramebuffers(1, &_framebuffer);
}

void Shadows::prepareToMapDepth(float lightPosX, float lightPosY, float lightPosZ){
	glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
		       	0.0, 0.5, 0.0, 0.0,
		       	0.0, 0.0, 0.5, 0.0,
		       	0.5, 0.5, 0.5, 1.0);

	_glm->selectMatrix(MODEL);
	_glm->pushMatrix();
	_glm->selectMatrix(VIEW);
	_glm->pushMatrix();
	_glm->selectMatrix(PROJECTION);
	_glm->pushMatrix();

	_glm->changeShader(_shadowMapShader);

	_glm->otho(-200.0f, 200.0f, -200.0f, 200.0f, -500.0f, 500.0f);
	_glm->lookAt(lightPosX, lightPosY, lightPosZ, 0, 0, 0, 0, 1, 0);
	_glm->selectMatrix(MODEL);
	_glm->loadIdentity();

	_depthBiasMVP = biasMatrix*(_glm->getMVP());

	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
}

void Shadows::returnToNormalDrawing(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	_glm->changeShader(_normalShader);
	_glm->selectMatrix(PROJECTION);
	_glm->popMatrix();
	_glm->selectMatrix(VIEW);
	_glm->popMatrix();
	_glm->selectMatrix(MODEL);
	_glm->popMatrix();

	glUniformMatrix4fv(_depthBiasMVPID, 1, GL_FALSE, glm::value_ptr(_depthBiasMVP));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _depthTexture);
	glUniform1i(_shadowMapID, 1);

	glActiveTexture(GL_TEXTURE0);
	glViewport(0, 0, _windowSize[0], _windowSize[1]);
}


