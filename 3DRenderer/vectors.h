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