#include "GLVector3f.h"

namespace GLVector3f {
	float GLVector3f::getLength() const {
		return sqrtf(x*x + y*y + z*z);
	}

	void GLVector3f::scale(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	void GLVector3f::normalize() {
		float length = getLength();
		if (length <= 0.0f) {
			return;
		}
		x /= length;
		y /= length;
		z /= length;
	}

	GLVector3f add(const GLVector3f& v1, const GLVector3f& v2) {
		GLVector3f result = v1;
		result.x += v2.x;
		result.y += v2.y;
		result.z += v2.z;

		return result;
	}
	GLVector3f substract(const GLVector3f& v1, const GLVector3f& v2) {
		GLVector3f result = v1;
		result.x -= v2.x;
		result.y -= v2.y;
		result.z -= v2.z;

		return result;
	}
	float dotProduct(const GLVector3f& v1, const GLVector3f& v2) {
		float result = v1.x * v2.x;
		result += v1.y * v2.y;
		result += v1.z * v2.z;

		return result;
	}
	GLVector3f crossProduct(const GLVector3f& v1, const GLVector3f& v2) {
		GLVector3f result(0.0f, 0.0f, 0.0f);
		result.x = v1.y * v2.z - v2.y * v1.z;
		result.y = v1.z * v2.x - v2.z * v1.x;
		result.z = v1.x * v2.y - v2.x * v1.y;

		return result;
	}
}