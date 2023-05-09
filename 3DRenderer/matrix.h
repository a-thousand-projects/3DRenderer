#pragma once
#include "vectors.h"

typedef struct {
	float m[4][4];
} mat4_t;

/* ProtoTypes */

mat4_t matIdenetity(void);
mat4_t matMakeScale(float x, float y, float z);
vct4_t mat4MulVec4(mat4_t m, vct4_t v);
mat4_t matMakeTranslate(float x, float y, float z);
mat4_t matMakeRotateX(float angle);
mat4_t matMakeRotateY(float angle);
mat4_t matMakeRotateZ(float angle);