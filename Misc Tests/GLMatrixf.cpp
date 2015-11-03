#include "GLMatrixf.h"

#include <iostream>

#define DEG_TO_RAD .017453292F

namespace GLMatrixf {
	GLMatrixf::GLMatrixf() {
	}

	void GLMatrixf::translate(float dx, float dy, float dz) {
		GLMatrixf t;
		t.m[0][3] = dx;
		t.m[1][3] = dy;
		t.m[2][3] = dz;

		memcpy(m, multiply(*this, t).m, sizeof(m));
	}

	void GLMatrixf::rotate(float degrees, GLVector3f::GLVector3f axis) {
		axis.normalize();

		float rad = degrees * DEG_TO_RAD;
		float s = sinf(rad);
		float c = cosf(rad);
		float t = 1.0f - c;

		GLMatrixf r;
		r.m[0][0] = axis.x * axis.x * t + c;
		r.m[0][1] = axis.x * axis.y * t - axis.z * s;
		r.m[0][2] = axis.x * axis.z * t + axis.y * s;

		r.m[1][0] = axis.y * axis.x * t + axis.z * s;
		r.m[1][1] = axis.y * axis.y * t + c;
		r.m[1][2] = axis.y * axis.z * t - axis.x * s;

		r.m[2][0] = axis.z * axis.x * t - axis.y * s;
		r.m[2][1] = axis.z * axis.y * t + axis.x * s;
		r.m[2][2] = axis.z * axis.z * t + c;

		memcpy(m, multiply(*this, r).m, sizeof(m));
	}

	void GLMatrixf::scale(float sx, float sy, float sz) {
		GLMatrixf s;
		s.m[0][0] *= sx;
		s.m[1][1] *= sy;
		s.m[2][2] *= sz;
		std::cout << "scale: " << std::endl;
		print(s);

		memcpy(m, multiply(*this, s).m, sizeof(m));
	}

	void GLMatrixf::transpose() {
		float temp;
		for (int i = 0; i < 3; i++) {
			for (int j = i + 1; j < 4; j++) {
				temp = m[i][j];
				m[i][j] = m[j][i];
				m[j][i] = temp;
			}
		}
	}

	GLMatrixf multiply(const GLMatrixf& m1, const GLMatrixf& m2) {
		GLMatrixf r;
		r.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
		r.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
		r.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
		r.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
		
		r.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
		r.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
		r.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
		r.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

		r.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
		r.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
		r.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
		r.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
		
		r.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
		r.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
		r.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
		r.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
		
		return r;
	}

	GLVector3f::GLVector3f transformPoint(const GLMatrixf& m, const GLVector3f::GLVector3f& p) {
		return p;
	}

	void print(const GLMatrixf& m) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << m.m[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
}