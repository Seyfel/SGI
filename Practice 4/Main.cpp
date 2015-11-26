#include <GL/freeglut.h>
#include <utility>
#include <math.h>
#include <iostream>

#define RAD_TO_DEG 57.295779f
#define PI 3.14159265f

GLuint star;

float camera_x = 9, camera_y = 10, camera_z = -10;

float c1_r = 1, c1_g = 1, c1_b = 0; //Amarillo
float c2_r = 0, c2_g = 0, c2_b = 1; //Azul

float fovy = 2 * RAD_TO_DEG * asinf(1 / sqrtf(camera_x * camera_x + camera_y * camera_y + camera_z * camera_z));

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

void updateCamera() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z,
		0, 0, 0,
		0, 1, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateCamera();

	int numStars = 6;
	for (int i = 0; i < numStars; i++) {
		float alpha = 1.0f / numStars * i;
		glColor3f(c1_r * alpha + c2_r * (1 - alpha),
			c1_g * alpha + c2_g * (1 - alpha),
			c1_b * alpha + c2_b * (1 - alpha));
		glCallList(star);
		glRotatef(180 / numStars, 0, 1, 0);
	}

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(1, 16, 16);

	glFlush();
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = (float)w / h;
	gluPerspective(fovy, ratio, 0.1, 1000);
}

void init() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(400, 400);
	glutCreateWindow("Estrella 3D");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	initStar();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	init();

	glutMainLoop();
}