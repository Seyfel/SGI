#include <GL/GLUT.H>

void display() {
	glClearColor(0.0, 0.0, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void reshape(GLint w, GLint h) {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 400);
	glutInitWindowPosition(50, 600);
	glutCreateWindow("Primer Programa en OpenGL");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}