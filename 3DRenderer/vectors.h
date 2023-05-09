#pragma once

typedef struct {
	float x;
	float y;
} vct2_t;

typedef struct {
	float x;
	float y;
	float z;
} vct3_t;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} vct4_t;

vct3_t vec3RotoateX(vct3_t v, float angle);
vct3_t vec3RotoateY(vct3_t v, float angle);
vct3_t vec3RotoateZ(vct3_t v, float angle);


float vct2Length(vct2_t v2);
vct2_t vct2Add(vct2_t a, vct2_t b);
vct2_t vct2Subtract(vct2_t a, vct2_t b);
vct2_t vct2Mul(vct2_t a, float factor);
vct2_t vct2Div(vct2_t a, float factor);
float vct2Dot(vct2_t a, vct2_t b);
void vct2Nomialiase(vct2_t* a);

float vct3Length(vct3_t v3);
vct3_t vct3Add(vct3_t a, vct3_t b);
vct3_t vct3Subtract(vct3_t a, vct3_t b);
vct3_t vct3Mul(vct3_t a, float factor);
vct3_t vct3Div(vct3_t a, float factor);
vct3_t vct3Cross(vct3_t a, vct3_t b);
void vct3Nomialiase(vct3_t *a);
float vct3Dot(vct3_t a, vct3_t b);

vct4_t vec3ToVec4(vct3_t v);
vct3_t vec4ToVec3(vct4_t v);
