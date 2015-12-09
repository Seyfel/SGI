#include "Camera.h"

#include <iostream>

Camera::Camera() {
	maxPitch = 85.0f;
	cosMaxPitch = cosf((90 - maxPitch) * Constants::deg_to_rad);

	position = GLVector3f::GLVector3f(0.0f, 0.0f, 0.0f);
	look = GLVector3f::GLVector3f(0.0f, 0.0f, -1.0f);
	up = GLVector3f::GLVector3f(0.0f, 1.0f, 0.0f);
}

Camera::Camera(GLVector3f::GLVector3f position, GLVector3f::GLVector3f look) : position(position) {
	maxPitch = 85.0f;
	cosMaxPitch = cosf((90 - maxPitch) * Constants::deg_to_rad);

	this->look = normalize(look);
	up = GLVector3f::GLVector3f(0.0f, 1.0f, 0.0f);
}

void Camera::render() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z,
		position.x+look.x, position.y+look.y, position.z+look.z,
		up.x, up.y, up.z);
}

void Camera::moveForward(float distance) {
	GLVector3f::GLVector3f movement = look;
	position = GLVector3f::add(position, GLVector3f::scale(movement, distance));
}

void Camera::pan(float distance) {
	// Pan direction is perpendicular to look and up
	GLVector3f::GLVector3f movement = GLVector3f::crossProduct(look, up);
	position = GLVector3f::add(position, GLVector3f::scale(movement, distance));
}

void Camera::pitch(float delta) {
	// Pitch rotation axis is perpendicular to look and up
	GLVector3f::GLVector3f perp = GLVector3f::crossProduct(look, up);

	GLMatrixf::GLMatrixf m;
	m.rotate(delta, perp);
	GLVector3f::GLVector3f newLook = GLMatrixf::transformPoint(m, look);
	if (std::abs(GLVector3f::dotProduct(newLook, up)) < cosMaxPitch) {
		look = newLook;
	}
}

void Camera::yaw(float delta) {
	GLMatrixf::GLMatrixf m;
	m.rotate(-delta, up);
	look = GLMatrixf::transformPoint(m, look);
}

void Camera::newPosition(GLVector3f::GLVector3f newPosition) {
	position = newPosition;
}

void Camera::lookAt(GLVector3f::GLVector3f point) {
	look = GLVector3f::normalize(GLVector3f::substract(point, position));
}