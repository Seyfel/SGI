#include <GL/freeglut.h>
#include <sstream>

#include <iostream>

#include "Timer.h"
#include "InputHandler.h"
#include "Camera.h"
#include "RenderUtils.h"

const std::string titulo = "Interfaz de conduccion";

Timer timer;
Camera camera;
InputHandler& input = InputHandler::getInstance();

void showSpeed() {
	std::stringstream ss;
	ss << titulo << " Velocidad = " << input.getSpeed() << "m/s";
	glutSetWindowTitle(ss.str().c_str());
}

void drawRoad() {
	float sinAmplitude = 5;
	float sinPeriod = 50;
	float roadWidth = 5;
	int frontLength = 50;
	int backLength = 15;

	glColor3f(0.0, 0.0, 0.0);

	float z = camera.position.z + backLength;

	float roadZ = z;
	float roadX = sinAmplitude * sin(roadZ * (Constants::pi / (sinPeriod / 2)));
	float tgAlpha = (Constants::pi / sinAmplitude) * sin(roadZ * (Constants::pi / (sinPeriod / 2)));

	GLVector3f::GLVector3f perp(-1, 0, tgAlpha);
	GLVector3f::GLVector3f n = GLVector3f::normalize(perp);
	GLVector3f::GLVector3f scaled = GLVector3f::scale(n, roadWidth);

	Pointf prevPos(roadX + scaled.x, 0, roadZ + scaled.z);
	Pointf prevNeg(roadX - scaled.x, 0, roadZ - scaled.z);

	for (int i = 1; i <= frontLength + backLength; i++) {
		float roadZ = z - i;
		float roadX = sinAmplitude * sin(roadZ * (Constants::pi / (sinPeriod / 2)));
		float tgAlpha = (Constants::pi / sinAmplitude) * sin(roadZ * (Constants::pi / (sinPeriod / 2)));

		GLVector3f::GLVector3f perp(-1, 0, tgAlpha);
		GLVector3f::GLVector3f n = GLVector3f::normalize(perp);
		GLVector3f::GLVector3f scaled = GLVector3f::scale(n, roadWidth);

		Pointf actualPos(roadX + scaled.x, 0, roadZ + scaled.z);
		Pointf actualNeg(roadX - scaled.x, 0, roadZ - scaled.z);

		RenderUtils::quads(prevPos, prevNeg, actualPos, actualNeg, 10, 10);

		prevPos = actualPos;
		prevNeg = actualNeg;
	}
}

void updateScene() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawRoad();
}

void updateCamera() {
	
}

void display() {
	timer.stopDeltaChrono();
	timer.startDeltaChrono();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	input.update();
	camera.render();
	updateScene();

	showSpeed();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = (float)w / h;
	gluPerspective(60, ratio, 0.1, 1000);
}

void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowSize(400, 400);
	glutCreateWindow(titulo.c_str());

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	input.init();
	input.setCamera(&camera);
	input.setTimer(&timer);

	camera.newPosition(GLVector3f::GLVector3f(0, 1, 0));
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();

	timer.startDeltaChrono();
	glutMainLoop();
}