#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler() {
	speed = 0;
	acceleration = 2;
	accelerating = false;
	decelerating = false;
	rotation = 0;
	rotationSpeed = 60.0f;

	a = 0;
	d = 0;
	l = 0;
	r = 0;
}
InputHandler& InputHandler::getInstance() {
	static InputHandler instance;
	return instance;
}

void InputHandler::init() {
	glutKeyboardFunc(InputHandler::GLCallbackOnKey);
	glutKeyboardUpFunc(InputHandler::GLCallbackOnKeyUp);
	glutSpecialFunc(InputHandler::GLCallbackOnSpecialKey);
	glutSpecialUpFunc(InputHandler::GLCallbackOnSpecialKeyUp);
	glutMouseFunc(InputHandler::GLCallbackOnMouse);
	glutMotionFunc(InputHandler::GLCallbackOnMotion);
	glutPassiveMotionFunc(InputHandler::GLCallbackOnPassiveMotion);
}
void InputHandler::setCamera(Camera* camera) {
	this->camera = camera;
}

void InputHandler::setTimer(Timer* timer) {
	this->timer = timer;
}

void InputHandler::update() {
	float delta = timer->getDeltaTime();

	speed += delta * acceleration *(a - d);
	speed = std::max((double)speed, 0.0);
	camera->moveForward(delta * speed);

	camera->yaw(delta * rotationSpeed * (r - l));
}

float InputHandler::getSpeed() {
	return speed;
}

void InputHandler::onKey(unsigned char key, int x, int y) {
	std::cout << key << std::endl;
}

void InputHandler::onKeyUp(unsigned char key, int x, int y) {

}

void InputHandler::onSpecialKey(int specialKey, int x, int y) {
	switch (specialKey) {
	case 100:
		l = 1;
		break;
	case 101:
		a = 1;
		break;
	case 102:
		r = 1;
		break;
	case 103:
		d = 1;
		break;
	}
}

void InputHandler::onSpecialKeyUp(int specialKey, int x, int y) {
	switch (specialKey) {
	case 100:
		l = 0;
		break;
	case 101:
		a = 0;
		break;
	case 102:
		r = 0;
		break;
	case 103:
		d = 0;
		break;
	}
}

void InputHandler::onMouse(int button, int state, int x, int y) {

}

void InputHandler::onMotion(int x, int y) {

}

void InputHandler::onPassiveMotion(int x, int y) {

}

/*****************\
*	GLCallbacks   *
\*****************/

void InputHandler::GLCallbackOnKey(unsigned char key, int x, int y) {
	InputHandler& instance = InputHandler::getInstance();
	instance.onKey(key, x, y);

	instance.pressedKeys.insert(key);
}

void InputHandler::GLCallbackOnKeyUp(unsigned char key, int x, int y) {
	InputHandler& instance = InputHandler::getInstance();
	instance.onKeyUp(key, x, y);

	instance.pressedKeys.erase(key);
}

void InputHandler::GLCallbackOnSpecialKey(int specialKey, int x, int y) {
	InputHandler& instance = InputHandler::getInstance();
	instance.onSpecialKey(specialKey, x, y);

	instance.pressedSpecialKeys.insert(specialKey);
}

void InputHandler::GLCallbackOnSpecialKeyUp(int specialKey, int x, int y) {
	InputHandler& instance = InputHandler::getInstance();
	instance.onSpecialKeyUp(specialKey, x, y);

	instance.pressedSpecialKeys.erase(specialKey);
}

void InputHandler::GLCallbackOnMouse(int button, int state, int x, int y) {
	InputHandler& instance = InputHandler::getInstance();
	instance.onMouse(button, state, x, y);
}

void InputHandler::GLCallbackOnMotion(int x, int y) {
	InputHandler& instance = InputHandler::getInstance();
	instance.onMotion(x, y);
}

void InputHandler::GLCallbackOnPassiveMotion(int x, int y) {
	InputHandler& instance = InputHandler::getInstance();
	instance.onPassiveMotion(x, y);
}