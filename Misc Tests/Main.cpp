#include <GL/freeglut.h>
#include <utility>
#include <math.h>
#include <iostream>
#include <string>
#include "GLMatrixf.h"
#include "GLVector3f.h"

#include "Timer.h"

#define PI 3.14159265f

GLuint star;
float rotation;

Timer timer;

std::pair<float, float> rotate2d(const std::pair<float, float>& p, float degrees) {
	float rad = degrees * PI / 180;
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
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	rotation += 90.0f * timer.getDeltaTime();
	rotation = std::fmodf(rotation, 360);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	/*
	GLfloat mv[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mv);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << mv[i + j * 4] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/

	glColor3f(0.0f, 0.0f, 0.3f);
	//glCallList(star);
	
	GLMatrixf::GLMatrixf m;
	m.rotate(-rotation, GLVector3f::GLVector3f(0.0, 0.0, 1.0));
	m.transpose();
	glLoadMatrixf((float*) m.m);

	glCallList(star);

	glFlush();
	glutPostRedisplay();

	int fps = 1 / timer.getDeltaTime();
	std::cout << "\r" << fps << " fps                   ";
}

void reshape(GLint w, GLint h) {

}

int main(int argc, char** argv) {
	timer = Timer();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(400, 400);
	glutCreateWindow("Estrella de David");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	initStar();
	rotation = 0.0f;

	timer.startDeltaChrono();
	glutMainLoop();
}