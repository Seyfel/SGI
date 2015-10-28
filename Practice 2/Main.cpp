//#include <GL/GLUT.H>
#include <GL/freeglut.h>
#include <utility>
#include <math.h>

#define PI 3.14159265f

GLuint star;

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
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.3f);
	glCallList(star);
	glFlush();
}

void reshape(GLint w, GLint h) {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(400, 400);
	glutCreateWindow("star de David");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	initStar();

	glutMainLoop();
}