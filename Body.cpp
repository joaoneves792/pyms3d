#include "Body.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Body::Body(GLM *glm, double x, double y, double z, double mass){
	_glm = glm;
	
	_mass = mass;

	_drag = 0;

	_currentRotation = glm::quat(glm::vec3(0));
	_forwards = glm::vec3(0, 0, 1);
	_left = glm::vec3(1, 0, 0);
	_up = glm::vec3(0, 1, 0);

	_position = glm::vec3(x, y, z);
	_velocity = glm::vec3(0);
	_forces = glm::vec3(0);
}


Body::~Body(){
	//Maybe do something here?
}

void Body::setAxis(double forwardsX, double forwardsY, double forwardsZ, double leftX, double leftY, double leftZ, double upX, double upY, double upZ){
	_forwards[0] = forwardsX;
	_forwards[1] = forwardsY;
	_forwards[2] = forwardsZ;
	_left[0] = leftX;
	_left[1] = leftY;
	_left[2] = leftZ;
	_up[0] = upX;
	_up[1] = upY;
	_up[2] = upZ;
}

glm::vec3 Body::getPosition(){
	return _position;
}

void Body::setX(double x){
	_position[0] = x;
}

void Body::setY(double y){
	_position[1] = y;
}

void Body::setZ(double z){
	_position[2] = z;
}

void Body::setDrag(double d){
	_drag = d;
}

void Body::addForce(double fX, double fY, double fZ){
	_forces[0] += fX;
	_forces[1] += fY;
	_forces[2] += fZ;
}

void Body::addForwardForce(double f){
	_forces[0] += _forwards[0]*f;
	_forces[1] += _forwards[1]*f;
	_forces[2] += _forwards[2]*f;
}

void Body::updateRotation(float yaw, float pitch, float roll){
	glm::quat rollQuat = glm::angleAxis(roll, _forwards);
	_left = glm::rotate(rollQuat, _left);
	_up = glm::rotate(rollQuat, _up);

	glm::quat pitchQuat = glm::angleAxis(pitch, _left);
	_forwards = glm::rotate(pitchQuat, _forwards);
	_up = glm::rotate(pitchQuat, _up);

	glm::quat yawQuat = glm::angleAxis(yaw, _up);
	_forwards = glm::rotate(yawQuat, _forwards);
	_left = glm::rotate(yawQuat, _left);
	
	glm::quat rotationChange = yawQuat * pitchQuat * rollQuat;

	_currentRotation = rotationChange * _currentRotation;
	
}

void Body::integrate(float dt){
	/*Its up to the application to get the units right*/

	glm::vec3 acceleration = glm::vec3(_forces[0]/_mass, _forces[1]/_mass, _forces[2]/_mass);
	_velocity += acceleration*dt;
	_position += _velocity*dt;
	_forces[0] = 0;
	_forces[1] = 0;
	_forces[2] = 0;

	if(_drag > 0){
		for(int i=0; i<3; i++)
			if (_velocity[i] > 0){
				if (_velocity[i] - _drag < 0)
					_velocity[i] = 0;
				else
					_velocity[i] -= _drag;
			}else if (_velocity[i] < 0){
				if (_velocity[i] - _drag > 0)
					_velocity[i] = 0;
				else
					_velocity[i] += _drag;
			}
	}

	/*TODO angular stuff*/
}


void Body::applyRotation(){
	glm::mat4 rotationMatrix = glm::toMat4(_currentRotation);
	_glm->multiply(rotationMatrix);
}

void Body::applyPosition(){
	_glm->translate(_position[0], _position[1], _position[2]);
}