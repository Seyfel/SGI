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

	int fps = 1 / timer.getDeltaTime();
	ss << " FPS: " << fps;

	glutSetWindowTitle(ss.str().c_str());
}

void showFPS() {
	int fps = 1 / timer.getDeltaTime();
	std::stringstream ss;
	ss << "FPS: " << fps;
	glutSetWindowTitle(ss.str().c_str());
}

void drawRoad() {
	GLfloat Em[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat Am[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat Dm[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat Sm[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat s = 3.0;
	glMaterialfv(GL_FRONT, GL_EMISSION, Em);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Am);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Dm);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Sm);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, s);

	//RenderUtils::quads(Pointf(0, 0, 0), Pointf(4, 0, 1), Pointf(0, 3, 2), Pointf(5, 4, -2), 10, 10);


	float sinAmplitude = 5;
	float sinPeriod = 50;
	float roadWidth = 5;
	float lightDistance = 50/4;
	int frontLength = 50;
	int backLength = 15;

	glColor3f(.1, 0.1, 0.1);

	static GLfloat posicionFarola1[] = { sinAmplitude * sin(-0 * lightDistance * (Constants::pi / (sinPeriod / 2))), 4, -0 * lightDistance, 1.0 };
	static GLfloat posicionFarola2[] = { sinAmplitude * sin(-1 * lightDistance * (Constants::pi / (sinPeriod / 2))), 4, -1 * lightDistance, 1.0 };
	static GLfloat posicionFarola3[] = { sinAmplitude * sin(-2 * lightDistance * (Constants::pi / (sinPeriod / 2))), 4, -2 * lightDistance, 1.0 };
	static GLfloat posicionFarola4[] = { sinAmplitude * sin(-3 * lightDistance * (Constants::pi / (sinPeriod / 2))), 4, -3 * lightDistance, 1.0 };

	float z = camera.position.z + backLength;

	
	if (std::abs(camera.position.z) > std::abs(posicionFarola1[2] - lightDistance / 2)) {
		posicionFarola1[0] = posicionFarola2[0];
		posicionFarola1[2] = posicionFarola2[2];

		posicionFarola2[0] = posicionFarola3[0];
		posicionFarola2[2] = posicionFarola3[2];

		posicionFarola3[0] = posicionFarola4[0];
		posicionFarola3[2] = posicionFarola4[2];

		posicionFarola4[2] -= lightDistance;
		posicionFarola4[0] = sinAmplitude * sin(posicionFarola4[2] * (Constants::pi / (sinPeriod / 2)));
	}

	glLightfv(GL_LIGHT2, GL_POSITION, posicionFarola1);
	glLightfv(GL_LIGHT3, GL_POSITION, posicionFarola2);
	glLightfv(GL_LIGHT4, GL_POSITION, posicionFarola3);
	glLightfv(GL_LIGHT5, GL_POSITION, posicionFarola4);

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

		RenderUtils::quads(prevPos, prevNeg, actualPos, actualNeg, 32, 32);

		prevPos = actualPos;
		prevNeg = actualNeg;
	}
}

void light() {
	//GLfloat A[] = { 1, 0, 0, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, A);
	GLfloat ALuna[] = { 0.05, 0.05, 0.05, 1.0 };
	GLfloat DLuna[] = { 0.05, 0.05, 0.05, 1.0 };
	GLfloat SLuna[] = { 0.0,0.0,0.0,1.0 };
	GLfloat posicionLuna[] = { 0.0, 10.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuna);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ALuna);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DLuna);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SLuna);

	glEnable(GL_LIGHT0);

	GLfloat AFaro[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat DFaro[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat SFaro[] = { 0.30, 0.3, 0.3, 1.0 };
	GLfloat posicionFaro[] = { camera.position.x, 0.9, camera.position.z, 1.0 };
	GLVector3f::GLVector3f x = GLVector3f::normalize(camera.look);
	GLfloat dir_central[] = {x.x, -0.5, x.z };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20);
	glLightfv(GL_LIGHT1, GL_POSITION, posicionFaro);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AFaro);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DFaro);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SFaro);

	glEnable(GL_LIGHT1);
	
	GLfloat AFarola[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat DFarola[] = { 0.5, 0.5, 0.2, 1.0 };
	GLfloat SFarola[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat dir_centralFarola[] = { 0.0, -1.0, 0.0 };

	//GLfloat posicionFaro[] = { camera.position.x, 0.7, camera.position.z, 1.0 };
	//glLightfv(GL_LIGHT1, GL_POSITION, posicionFaro);
	
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_centralFarola);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AFarola);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DFarola);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SFarola);

	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_centralFarola);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT3, GL_AMBIENT, AFarola);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DFarola);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SFarola);

	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_centralFarola);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT4, GL_AMBIENT, AFarola);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, DFarola);
	glLightfv(GL_LIGHT4, GL_SPECULAR, SFarola);

	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_centralFarola);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT5, GL_AMBIENT, AFarola);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, DFarola);
	glLightfv(GL_LIGHT5, GL_SPECULAR, SFarola);
	
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
}

void updateScene() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawRoad();
	
	light();
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

	//showFPS();
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
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glClearColor(0.0, 0.0, 0.0, 1.0);

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