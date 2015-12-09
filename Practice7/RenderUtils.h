#pragma once
#include <GL/freeglut.h>

#include "GLVector3f.h"

struct Pointf {
	float x, y, z;

	Pointf(float x, float y, float z) : x(x), y(y), z(z) {};
};
namespace RenderUtils {
	void quads(Pointf v0, Pointf v1, Pointf v2, Pointf v3, int N, int M);
}