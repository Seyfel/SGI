#pragma once
#include <GL\freeglut.h>
#include <cmath>

#include "GLVector3f.h"
#include "GLMatrixf.h"
#include "Constants.h"

class Camera {
private:
	float maxPitch;
	float cosMaxPitch;
public:
	GLVector3f::GLVector3f position;
	GLVector3f::GLVector3f look;
	GLVector3f::GLVector3f up;

	Camera();
	Camera(GLVector3f::GLVector3f position, GLVector3f::GLVector3f look);
	void render();

	void moveForward(float distance);
	void pan(float distance);
	void pitch(float delta);
	void yaw(float delta);

	void newPosition(GLVector3f::GLVector3f newPosition);
	void lookAt(GLVector3f::GLVector3f point);
};