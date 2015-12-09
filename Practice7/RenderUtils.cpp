#include "RenderUtils.h"

#include <iostream>
#include <cstdio>


void RenderUtils::quads(Pointf v0, Pointf v1, Pointf v2, Pointf v3, int N, int M) {
	#define MAXN 200
	#define MAXM 200
	
	if (N > MAXN) N = MAXN;
	if (M > MAXM) M = MAXM;

	float vertices2[MAXN + 1][MAXM + 1][3];
	float normals2[MAXN+1][MAXM+1][3];

	GLVector3f::GLVector3f left(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
	GLVector3f::GLVector3f right(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
	
	static bool print(true);

	for (int m = 0; m <= M; m++) {
		GLVector3f::GLVector3f start = GLVector3f::scale(left, (float) m / M);
		GLVector3f::GLVector3f end = GLVector3f::scale(right, (float) m / M);
		GLVector3f::GLVector3f currentStart(v0.x + start.x, v0.y + start.y, v0.z + start.z);
		GLVector3f::GLVector3f currentEnd(v1.x + end.x, v1.y + end.y, v1.z + end.z);
		GLVector3f::GLVector3f horizontal = GLVector3f::substract(currentEnd, currentStart);

		GLVector3f::GLVector3f normal = GLVector3f::crossProduct(horizontal, left);
		
		for (int n = 0; n <= N; n++) {
			normals2[n][m][0] = normal.x;
			normals2[n][m][1] = normal.y;
			normals2[n][m][2] = normal.z;

			GLVector3f::GLVector3f currentHorizontal = GLVector3f::scale(horizontal, (float) n / N);
			vertices2[n][m][0] = currentStart.x + currentHorizontal.x;
			vertices2[n][m][1] = currentStart.y + currentHorizontal.y;
			vertices2[n][m][2] = currentStart.z + currentHorizontal.z;

			
		}
	}

	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			glBegin(GL_QUADS);

			glNormal3f(normals2[n][m][0], normals2[n][m][1], normals2[n][m][2]);

			glVertex3f(vertices2[n][m][0], vertices2[n][m][1], vertices2[n][m][2]);
			glVertex3f(vertices2[n+1][m][0], vertices2[n+1][m][1], vertices2[n+1][m][2]);
			glVertex3f(vertices2[n+1][m+1][0], vertices2[n+1][m+1][1], vertices2[n+1][m+1][2]);
			glVertex3f(vertices2[n][m+1][0], vertices2[n][m+1][1], vertices2[n][m+1][2]);

			glEnd();
		}
	}

	//glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glDrawElements(GL_QUADS, numIndices, GL_UNSIGNED_BYTE, indices);
}