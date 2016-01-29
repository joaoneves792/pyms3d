#ifndef _ms3d_H_
#define _ms3d_H_

#include <stack>
#include <GL/glew.h>
#include <ms3d/MS3DFile.h>
#include <ms3d/Textures.h>
#include <ms3d/Shader.h>
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
	void use();
};

class ms3d{
private:
	CMS3DFile* _model;

public: 
	ms3d(char* filename, bool overrideAmbient=false, bool overrideSpecular=false, bool overrideDiffuse=false, bool overrideEmissive=false);
	ms3d();
	virtual ~ms3d();
	void draw();
	void drawGL3();
	void createRectangle(float width, float height, int texture);
	void changeRectangleTexture(int texture);
	void prepare(shader* shader);
	float* getJointPosition(char* jointName);
	void changeTexture(char* groupName, char* textureFile);
	static void initGlew();
};

class Tex{
private:
	int _tex;
public:
	Tex(char* filename);
	int getTexture();
};

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
	GLuint _projectionID;

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
	void pushMatrix();
	void popMatrix();
	void changeShader(shader* newShader);
	glm::mat4 getMVP();
private:
	void uploadMatrix();
};

#define MAX_LIGHTS 10

class Lights{
private:
	GLint _lightingDisabledID;
	GLint _enabled[MAX_LIGHTS];
	GLint _enabledID;
	GLint _colorsID[MAX_LIGHTS];
	GLint _conesID[MAX_LIGHTS];
	GLint _positionID[MAX_LIGHTS];
public:
	Lights(shader* shader);
	virtual ~Lights();

	void enableLighting();
	void disableLighting();
	void enable(int light);
	void disable(int light);
	void setColor(int light, float red, float green, float blue, float intensity);
	void setPosition(int light, float x, float y, float z);
	void setCone(int light, float direction_x, float direction_y, float direction_z, float angle);
};

#define SHADOW_MAP_SIZE 1024

class Shadows{
private:
	shader* _normalShader;
	shader* _shadowMapShader;
	GLuint _framebuffer;
	GLuint _depthTexture;
	GLM* _glm;

	glm::mat4 _depthBiasMVP;
	GLuint _depthBiasMVPID;
	GLuint _shadowMapID;
	int _windowSize[2];
	
	int _textureWidth;
	int _textureHeight;
	float _orthoBox[6];

public:
	Shadows(GLM* glm, shader* normalShader, shader* shadowMapShader, int window_width, int window_height, int shadow_map_width, int shadow_map_height);
	virtual ~Shadows();
	void prepareToMapDepth(float lightPosX, float lightPosY, float lightPosZ);
	void changeOrthoBox(float left, float right, float bottom, float top, float near, float far);
	void returnToNormalDrawing();
	int getShadowTexture();
};

#endif
