#pragma once
#include <math.h>

namespace GLVector3f {

	class GLVector3f {
	public:
		float x, y, z;

		GLVector3f(float x, float y, float z) : x(x), y(y), z(z) {}
		float getLength() const;
		void scale(float scalar);
		void normalize();
	};


	GLVector3f add(const GLVector3f& v1, const GLVector3f& v2) {};
	GLVector3f substract(const GLVector3f& v1, const GLVector3f& v2) {};

	float dotProduct(const GLVector3f& v1, const GLVector3f& v2) {};
	GLVector3f crossProduct(const GLVector3f& v1, const GLVector3f& v2) {};
}