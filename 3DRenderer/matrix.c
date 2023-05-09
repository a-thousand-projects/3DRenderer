#include <math.h>
#include "matrix.h"
#include "vectors.h"

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
	mat4_t m = matIdenetity();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	return m;
}

mat4_t matMakeTranslate(float x, float y, float z)
{
	mat4_t m = matIdenetity();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return m;
}

mat4_t matMakeRotateZ(float angle)
{
	// c  -s  0  0
	// s   c  0  0
	// 0   0  1  0 
	// 0   0  0  1 
	float c = cos(angle);
	float s = sin(angle);
	mat4_t m = matIdenetity();
	m.m[0][0] = c;
	m.m[0][1] = -s;
	m.m[1][0] = s;
	m.m[1][1] = c;
	return m;
}

mat4_t matMakeRotateX(float angle)
{
	// 1   0   0   0
	// 0   c   -s  0
	// 0   s   c   0 
	// 0   0   0   1 
	float c = cos(angle);
	float s = sin(angle);
	mat4_t m = matIdenetity();
	m.m[1][1] = c;
	m.m[1][2] = -s;
	m.m[2][1] = s;
	m.m[2][2] = c;
	return m;
}

mat4_t matMakeRotateY(float angle)
{
	//  c   0   s   0
	//  0   1   0   0
	// -s   0   c   0 
	//  0   0   0   1 
	float c = cos(angle);
	float s = sin(angle);
	mat4_t m = matIdenetity();
	m.m[0][0] = c;
	m.m[0][2] = s;
	m.m[2][0] = -s;
	m.m[2][2] = c;
	return m;
}

vct4_t mat4MulVec4(mat4_t m, vct4_t v)
{
	vct4_t result;
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

	return result;
}