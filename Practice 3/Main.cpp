//#include <GL/GLUT.H>
#include <GL/freeglut.h>
#include <utility>
#include <math.h>

#define PI 3.14159265f

GLuint star;
GLuint tile;

std::pair<float, float> rotate2d(const std::pair<float, float>& p, float degrees) {
	float rad = degrees * PI / 180;
	return std::make_pair(p.first * cos(rad) - p.second * sin(rad),
		p.first * sin(rad) + p.second * cos(rad));
}

void init() {
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

	tile = glGenLists(1);
	glNewList(tile, GL_COMPILE); {
		glPushMatrix();
		glScalef(0.5, 0.5, 0);
		glCallList(star);
		glScalef(0.4, 0.4, 0);
		glRotatef(-30, 0, 0, 1);
		glCallList(star);
		glPopMatrix();
	}
	glEndList();
}

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.8f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0);
	glRotatef(15, 0, 0, 1);
	glCallList(tile);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(-15, 0, 0, 1);
	glCallList(tile);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0);
	glRotatef(-15, 0, 0, 1);
	glCallList(tile);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.5, 0);
	glRotatef(15, 0, 0, 1);
	glCallList(tile);
	glPopMatrix();

	glFlush();
}

void reshape(GLint w, GLint h) {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(400, 400);
	glutCreateWindow("Mosaico");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	init();

	glutMainLoop();
}