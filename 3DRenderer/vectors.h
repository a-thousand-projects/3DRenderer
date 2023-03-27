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

vct3_t vec3RotoateX(vct3_t v, float angle);
vct3_t vec3RotoateY(vct3_t v, float angle);
vct3_t vec3RotoateZ(vct3_t v, float angle);


float vct2Length(vct2_t v2);
vct2_t vct2Add(vct2_t a, vct2_t b);
vct2_t vct2Subtract(vct2_t a, vct2_t b);

float vct3Length(vct3_t v3);
vct3_t vct3Add(vct3_t a, vct3_t b);
vct3_t vct3Subtract(vct3_t a, vct3_t b);
