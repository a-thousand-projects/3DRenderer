#include "matrix.h"

mat4_t matIdenetity(void)
{
	return (mat4_t) {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};
}

mat4_t matMakeScale(float x, float y, float z)
{
	return (mat4_t) {
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
	};
}