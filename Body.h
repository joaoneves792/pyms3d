
#ifndef _BODY_H_
#define _BODY_H_

#include <glm/glm.hpp>
#include "GLM.h"

class Body{
private:
	GLM* _glm;
	
	double _mass;

	double _drag;

	glm::vec3 _position;
	glm::vec3 _velocity;
	glm::vec3 _forces;

	glm::quat _currentRotation;
	glm::vec3 _forwards;
	glm::vec3 _left;
	glm::vec3 _up;


public:
	Body(GLM *glm, double x, double y, double z, double mass);
	void setAxis(double forwardsX, double forwardsY, double forwardsZ, double leftX, double leftY, double leftZ, double upX, double upY, double upZ);
	virtual ~Body();

	glm::vec3 getPosition();

	void setX(double x);
	void setY(double y);
	void setZ(double z);

	void setDrag(double d);

	void addForwardForce(double f);
	void addForce(double fx, double fy, double fz);
	//void addTorque(double fx, double fy, double fz, double offset_x, double offset_y, double offset_z);
	void integrate(float dt);

	void updateRotation(float yaw, float pitch, float roll);
	
	void applyRotation();
	void applyPosition();
};
#endif