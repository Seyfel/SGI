#pragma once
#include <GL\freeglut.h>
#include <vector>
#include <set>

#include "Camera.h"
#include "Timer.h"

class InputHandler {
private:
	int mouseX, mouseY;
	std::set<unsigned char> pressedKeys;
	std::set<int> pressedSpecialKeys;

	InputHandler() {}

	Camera* camera;
	Timer* timer;
	float speed = 0; // M/S
	float acceleration = 1; // Increase speed by, M/S
	bool accelerating = false;
	bool decelerating = false;
	int rotation = 0;
	float rotationSpeed = 90.0f;

	int a = 0;
	int d = 0;
	int l = 0;
	int r = 0;

public:
	static InputHandler& getInstance();

	InputHandler(const InputHandler&) = delete;
	void operator=(const InputHandler&) = delete;

	void init();
	void setCamera(Camera* camera);
	void setTimer(Timer* timer);

	void update();

	float getSpeed();

	bool isKeyPressed(unsigned char key);
	std::vector<char> getPressedKeys();

	bool isSpecialKeyPressed(int specialKey);
	std::vector<char> getPressedSpecialKeys();

	void getMousePosition();

	virtual void onKey(unsigned char key, int x, int y);
	virtual void onKeyUp(unsigned char key, int x, int y);
	virtual void onSpecialKey(int specialKey, int x, int y);
	virtual void onSpecialKeyUp(int specialKey, int x, int y);
	virtual void onMouse(int button, int state, int x, int y);
	virtual void onMotion(int x, int y);
	virtual void onPassiveMotion(int x, int y);

	static void GLCallbackOnKey(unsigned char key, int x, int y);
	static void GLCallbackOnKeyUp(unsigned char key, int x, int y);
	static void GLCallbackOnSpecialKey(int specialKey, int x, int y);
	static void GLCallbackOnSpecialKeyUp(int specialKey, int x, int y);
	static void GLCallbackOnMouse(int button, int state, int x, int y);
	static void GLCallbackOnMotion(int x, int y);
	static void GLCallbackOnPassiveMotion(int x, int y);
};
