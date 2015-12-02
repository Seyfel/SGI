#include "RenderUtils.h"

#include <iostream>


void RenderUtils::quads(Pointf v0, Pointf v1, Pointf v2, Pointf v3, int N, int M) {
	#define MAXN 10
	#define MAXM 10
	
	if (N > MAXN) N = MAXN;
	if (M > MAXM) M = MAXM;

	GLfloat vertices[3 * (MAXN + 1) * (MAXM + 1)];
	GLubyte indices[4 * MAXN * MAXM];
	int numVertices = (N + 1) * (M + 1);
	int numIndices = 4 * N * M;

	GLVector3f::GLVector3f left(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
	GLVector3f::GLVector3f right(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
	
	for (int m = 0; m <= M; m++) {
		GLVector3f::GLVector3f start = GLVector3f::scale(left, (float) m / M);
		GLVector3f::GLVector3f end = GLVector3f::scale(right, (float) m / M);
		GLVector3f::GLVector3f currentStart(v0.x + start.x, v0.y + start.y, v0.z + start.z);
		GLVector3f::GLVector3f currentEnd(v1.x + end.x, v1.y + end.y, v1.z + end.z);
		GLVector3f::GLVector3f horizontal = GLVector3f::substract(currentEnd, currentStart);

		for (int n = 0; n <= N; n++) {
			GLVector3f::GLVector3f currentHorizontal = GLVector3f::scale(horizontal, (float) n / N);
			vertices[(m * (N + 1) * 3) + (n * 3) + 0] = currentStart.x + currentHorizontal.x;
			vertices[(m * (N + 1) * 3) + (n * 3) + 1] = currentStart.y + currentHorizontal.y;
			vertices[(m * (N + 1) * 3) + (n * 3) + 2] = currentStart.z + currentHorizontal.z;
		}
	}

	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			indices[(m * (N) * 4) + (n * 4) + 0] = m * (N + 1) + n;
			indices[(m * (N) * 4) + (n * 4) + 1] = m * (N + 1) + n+1;
			indices[(m * (N) * 4) + (n * 4) + 2] = (m+1) * (N + 1) + n+1;
			indices[(m * (N) * 4) + (n * 4) + 3] = (m+1) * (N + 1) + n;
		}
	}

	for (int i = 0; i < numIndices; i += 4) {
		glBegin(GL_QUADS);
		glVertex3f(vertices[indices[i] * 3 + 0], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
		glVertex3f(vertices[indices[i+1] * 3 + 0], vertices[indices[i+1] * 3 + 1], vertices[indices[i+1] * 3 + 2]);
		glVertex3f(vertices[indices[i+2] * 3 + 0], vertices[indices[i+2] * 3 + 1], vertices[indices[i+2] * 3 + 2]);
		glVertex3f(vertices[indices[i+3] * 3 + 0], vertices[indices[i+3] * 3 + 1], vertices[indices[i+3] * 3 + 2]);
		glEnd();
	}

	//glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glDrawElements(GL_QUADS, numIndices, GL_UNSIGNED_BYTE, indices);
}