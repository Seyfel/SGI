#include <ctime>
#include <GL/freeglut.h>
#include <utility>
#include <math.h>
#include <iostream>

#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f

struct Camera {
	float x, y, z;
	float fovy;
} camera;

void updateCamera() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.x, camera.y, camera.z,
		0, 0, 0,
		0, 1, 0);
}

class Timer {
private:
	clock_t startTime;
	clock_t deltaStartTime;
	float deltaTime;
public:
	Timer() {
		startTime = clock();
		deltaStartTime = startTime;
		deltaTime = 0.0f;
	}
	double getElapsedTime() {
		clock_t now = clock();
		return double(now - startTime) / CLOCKS_PER_SEC;
	}
	float getDeltaTime() {
		return deltaTime;
	}
	void startDeltaChrono() {
		deltaStartTime = clock();
	}
	void stopDeltaChrono() {
		clock_t now = clock();
		deltaTime = float(now - deltaStartTime) / CLOCKS_PER_SEC;
	}
} timer;

std::pair<float, float> rotate2f(const std::pair<float, float>& p, float degrees) {
	float rad = degrees * DEG_TO_RAD;
	return std::make_pair(p.first * cos(rad) - p.second * sin(rad),
		p.first * sin(rad) + p.second * cos(rad));
}

void drawI() {
	glPushMatrix();
	glScalef(0.1, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
}

void drawV() {
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(18, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	drawI();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(-18, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	drawI();
	glPopMatrix();

	glPopMatrix();
}

void drawX() {
	glPushMatrix();

	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	drawI();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20, 0, 0, 1);
	drawI();
	glPopMatrix();

	glPopMatrix();
}

void drawXII() {
	glPushMatrix();
	glTranslatef(0.14, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(-0.35, 0, 0);
	drawX();
	glPopMatrix();

	drawI();

	glPushMatrix();
	glTranslatef(0.2, 0, 0);
	drawI();
	glPopMatrix();

	glPopMatrix();
}

void drawIII() {
	glPushMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 0, 0);
	drawI();
	glPopMatrix();

	drawI();

	glPushMatrix();
	glTranslatef(0.2, 0, 0);
	drawI();
	glPopMatrix();

	glPopMatrix();
}

void drawVI() {
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(-0.525, 0.05, 0);
	drawV();
	glPopMatrix();

	drawI();

	glPopMatrix();
}

void drawIX() {
	glPushMatrix();
	glTranslatef(-0.2, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(0.35, 0, 0);
	drawX();
	glPopMatrix();

	drawI();

	glPopMatrix();
}

void drawRing(float extRadius, float intRadius, int sides) {
	std::pair<float, float> vInterior(0.0, intRadius), vExterior(0.0, extRadius);
	glBegin(GL_TRIANGLE_STRIP); {
		glVertex2f(vInterior.first, vInterior.second);
		glVertex2f(vExterior.first, vExterior.second);
		for (int i = 0; i <= sides; i++) {
			vInterior = rotate2f(vInterior, 360 / sides);
			vExterior = rotate2f(vExterior, 360 / sides);
			glVertex2f(vInterior.first, vInterior.second);
			glVertex2f(vExterior.first, vExterior.second);
		}
	}
	glEnd();
}

int clockList;
void initClockList() {

	int xiiList = glGenLists(1);
	glNewList(xiiList, GL_COMPILE); {
		drawXII();
	}
	glEndList();

	int iiiList = glGenLists(1);
	glNewList(iiiList, GL_COMPILE); {
		drawIII();
	}
	glEndList();

	int viList = glGenLists(1);
	glNewList(viList, GL_COMPILE); {
		drawVI();
	}
	glEndList();

	int ixList = glGenLists(1);
	glNewList(ixList, GL_COMPILE); {
		drawIX();
	}
	glEndList();

	clockList = glGenLists(1);
	glNewList(clockList, GL_COMPILE); {
		// Dibujar Anillo exterior
		drawRing(1, 0.98, 40);
		drawRing(0.97, 0.95, 40);

		// Dibujar Anillo interior
		drawRing(0.75, 0.73, 40);
		drawRing(0.72, 0.7, 40);


		// Dibujar Numeros (12, 3, 6, 9)
		glPushMatrix();
		glTranslatef(0, 0.845, 0);
		glScalef(0.24, 0.24, 0);
		glCallList(xiiList);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.845, 0, 0);
		glRotatef(90, 0, 0, 1);
		glScalef(0.24, 0.24, 0);
		glCallList(iiiList);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -0.845, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(0.24, 0.24, 0);
		glCallList(viList);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.845, 0, 0);
		glRotatef(90, 0, 0, 1);
		glScalef(0.24, 0.24, 0);
		glCallList(ixList);
		glPopMatrix();


		// Dibujar marcadores de horas adicionales
		glPushMatrix();
		glRotatef(30, 0, 0, 1);
		glTranslatef(0, 0.845, 0);
		glScalef(0.24, 0.24, 0);
		drawI();
		glPopMatrix();

		glPushMatrix();
		glRotatef(60, 0, 0, 1);
		glTranslatef(0, 0.845, 0);
		glScalef(0.24, 0.24, 0);
		drawI();
		glPopMatrix();

		glPushMatrix();
		glRotatef(30, 0, 0, 1);
		glTranslatef(-0.845, 0, 0);
		glScalef(0.24, 0.24, 0);
		glRotatef(90, 0, 0, 1);
		drawI();
		glPopMatrix();

		glPushMatrix();
		glRotatef(60, 0, 0, 1);
		glTranslatef(-0.845, 0, 0);
		glScalef(0.24, 0.24, 0);
		glRotatef(90, 0, 0, 1);
		drawI();
		glPopMatrix();

		glPushMatrix();
		glRotatef(30, 0, 0, 1);
		glTranslatef(0, -0.845, 0);
		glScalef(0.24, 0.24, 0);
		drawI();
		glPopMatrix();

		glPushMatrix();
		glRotatef(60, 0, 0, 1);
		glTranslatef(0, -0.845, 0);
		glScalef(0.24, 0.24, 0);
		drawI();
		glPopMatrix();

		glPushMatrix();
		glRotatef(30, 0, 0, 1);
		glTranslatef(0.845, 0, 0);
		glScalef(0.24, 0.24, 0);
		glRotatef(90, 0, 0, 1);
		drawI();
		glPopMatrix();

		glPushMatrix();
		glRotatef(60, 0, 0, 1);
		glTranslatef(0.845, 0, 0);
		glScalef(0.24, 0.24, 0);
		glRotatef(90, 0, 0, 1);
		drawI();
		glPopMatrix();
	}
	glEndList();
}

float rotationMinutes(tm t) {
	return t.tm_min * 360 / 60;
}

float rotationHours(tm t) {
	return ((t.tm_hour) % 12 * 360 / 12) + (rotationMinutes(t) / 12);
}

float rotationSeconds(tm t) {
	return t.tm_sec * 360 / 60;
}

void updateScene() {
	static bool changeColor = true;
	static double rotation1 = 0;
	static double rotation2 = 0;
	static double rotationSpeed = 30; // Grados por segundo
	static float rotS = 0;
	static float lastSecond = 0;


	// Esfera 1
	rotation1 += timer.getDeltaTime() * rotationSpeed;
	rotation1 = std::fmod(rotation1, 360);
	if (fabs(rotation1 - 90) < 1e-1) {
		rotation1 += 180;
	}

	glPushMatrix(); {
		glRotated(rotation1, 0, 1, 0);
		glColor3f(0, fabs(sin(timer.getElapsedTime() / 10.0)), fabs(cos(timer.getElapsedTime() / 10.0)));
		drawRing(0.98, 0.97, 40);
		drawRing(0.73, 0.72, 40);

		if (changeColor) {
			glColor3f(0.5, 0.5, 0.5);
		}
		else {
			glColor3f(0, 0, 0);
		}
		glCallList(clockList);
	}
	glPopMatrix();

	// Esfera 2
	rotation2 += timer.getDeltaTime() * rotationSpeed;
	rotation2 = std::fmod(rotation2, 360);
	if (fabs(rotation2 - 180) < 1e-1) {
		rotation2 += 180;
	}

	glPushMatrix(); {
		glRotated(rotation2, 0, 1, 0);
		glRotatef(-90, 0, 1, 0);
		glColor3f(0, fabs(cos(timer.getElapsedTime() / 10.0)), fabs(sin(timer.getElapsedTime() / 10.0)));
		drawRing(0.98, 0.97, 40);
		drawRing(0.73, 0.72, 40);

		if (changeColor) {
			glColor3f(0.5, 0.5, 0.5);
		}
		else {
			glColor3f(0, 0, 0);
		}
		glCallList(clockList);
	}
	glPopMatrix();

	// Leer hora actual
	std::time_t now = std::time(nullptr);
	struct tm t;
	time(&now);
	localtime_s(&t, &now);

	// Actualizar rotacion del segundero
	if (t.tm_sec == lastSecond) {
		rotS += 360 / 60 * timer.getDeltaTime();
	}
	else {
		rotS = rotationSeconds(t);
		lastSecond = t.tm_sec;
	}
	// Dibujar segundero
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(rotS, 0, 0, -1);
	glTranslatef(0, 0.35, 0);
	glScalef(0.1, 0.7, 0);
	drawI();
	glPopMatrix();

	// Dibujar minutero
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(rotationMinutes(t), 0, 0, -1);
	glTranslatef(0, 0.35, 0);
	glScalef(0.8, 0.7, 0);
	drawI();
	glPopMatrix();

	// Controlar cuando se cambia de hora para actualizar un objeto cada hora
	static int lastHour = 0;
	if (t.tm_hour != lastHour) {
		lastHour = t.tm_hour;
		changeColor = !changeColor;
	}
	// Dibujar saeta de las horas
	glPushMatrix();
	glRotatef(rotationHours(t), 0, 0, -1);
	glTranslatef(0, 0.175, 0);
	glScalef(0.8, 0.35, 0);
	drawI();
	glPopMatrix();

}

void display() {
	timer.stopDeltaChrono();
	timer.startDeltaChrono();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateCamera();
	updateScene();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = (float)w / h;
	gluPerspective(camera.fovy, ratio, 0.1, 1000);
}

void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowSize(400, 400);
	glutCreateWindow("Reloj analogico");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	initClockList();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	init();

	camera.x = 0; camera.y = 0; camera.z = 10;
	camera.fovy = 2 * RAD_TO_DEG * asinf(1 / sqrtf(camera.x * camera.x + camera.y * camera.y + camera.z * camera.z));

	timer.startDeltaChrono();
	glutMainLoop();
}