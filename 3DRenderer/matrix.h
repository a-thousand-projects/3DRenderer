#pragma once

typedef struct {
	float m[4][4];
} mat4_t;

/* ProtoTypes */

mat4_t matIdenetity(void);
mat4_t matMakeScale(float x, float y, float z);