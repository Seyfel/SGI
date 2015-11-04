#include <GL/freeglut.h>
#include <utility>
#include <math.h>
#include <iostream>
#include <string>
#include "GLMatrixf.h"
#include "GLVector3f.h"

#include "Timer.h"
#include "Camera.h"
#include "Constants.h"

GLuint star;
float rotation;

Timer timer;
Camera camera;

std::pair<float, float> rotate2d(const std::pair<float, float>& p, float degrees) {
	float rad = degrees * Constants::deg_to_rad;
	return std::make_pair(p.first * cos(rad) - p.second * sin(rad),
		p.first * sin(rad) + p.second * cos(rad));
}

void initStar() {
	star = glGenLists(1);
	glNewList(star, GL_COMPILE); {
		glBegin(GL_TRIANGLE_STRIP); {
			std::pair<float, float> vInterior(0.0, 0.7), vExterior(0.0, 1.0);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);

			vInterior = rotate2d(vInterior, 360 / 3);
			vExterior = rotate2d(vExterior, 360 / 3);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);

			vInterior = rotate2d(vInterior, 360 / 3);
			vExterior = rotate2d(vExterior, 360 / 3);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);

			vInterior = rotate2d(vInterior, 360 / 3);
			vExterior = rotate2d(vExterior, 360 / 3);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);
		}
		glEnd();

		glBegin(GL_TRIANGLE_STRIP); {
			std::pair<float, float> vInterior(0.0, -0.7), vExterior(0.0, -1.0);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);

			vInterior = rotate2d(vInterior, 360 / 3);
			vExterior = rotate2d(vExterior, 360 / 3);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);

			vInterior = rotate2d(vInterior, 360 / 3);
			vExterior = rotate2d(vExterior, 360 / 3);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);

			vInterior = rotate2d(vInterior, 360 / 3);
			vExterior = rotate2d(vExterior, 360 / 3);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);
		}
		glEnd();
	}
	glEndList();
}

void display() {
	timer.stopDeltaChrono();
	timer.startDeltaChrono();
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	

	GLMatrixf::GLMatrixf m;
	m.rotate(90.0f * timer.getDeltaTime(), GLVector3f::GLVector3f(0, 0, 1));
	GLVector3f::GLVector3f newPos = GLMatrixf::transformPoint(m, camera.position);
	camera.newPosition(newPos);
	camera.lookAt(GLVector3f::GLVector3f(0.0, 0.0, 0.0));

	//camera.yaw(90.0f * timer.getDeltaTime());
	//camera.pitch(45.0f * timer.getDeltaTime());

	camera.update();

	rotation += 90.0f * timer.getDeltaTime();
	rotation = std::fmodf(rotation, 360);
	
	glPushMatrix();
	glRotatef(rotation, 1.0, 0.0, 0.0);

	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	glTranslatef(0.0, 0.0, -2.0);
	glScalef(50.0, 50.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);

	glFlush();
	glutPostRedisplay();

	int fps = 1 / timer.getDeltaTime();
	std::cout << "\r" << fps << " fps                   ";
	
	//std::string line;
	//std::getline(std::cin, line);
	
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = (float) w / h;
	gluPerspective(90, ratio, 1, 100);
}

int main(int argc, char** argv) {
	timer = Timer();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(400, 400);
	glutCreateWindow("Estrella de David");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	initStar();
	rotation = 0.0f;

	camera.newPosition(GLVector3f::GLVector3f(5, 5, 5));
	camera.lookAt(GLVector3f::GLVector3f(0, 0, 0));

	timer.startDeltaChrono();
	glutMainLoop();
}