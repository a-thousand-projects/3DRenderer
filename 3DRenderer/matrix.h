#pragma once
#include "vectors.h"

typedef struct {
	float m[4][4];
} mat4_t;

/* ProtoTypes */

mat4_t matIdenetity(void);
mat4_t matMakeScale(float x, float y, float z);
vct4_t mat4MulVec4(mat4_t m, vct4_t v);
mat4_t mat4MulMat4(mat4_t a, mat4_t b);
mat4_t matMakeTranslate(float x, float y, float z);
mat4_t matMakeRotateX(float angle);
mat4_t matMakeRotateY(float angle);
mat4_t matMakeRotateZ(float angle);
mat4_t matMakeProjection(float fov, float aspect, float znear, float zfar);
vct4_t mat4MulVec4Project(mat4_t matProjection, vct4_t v);