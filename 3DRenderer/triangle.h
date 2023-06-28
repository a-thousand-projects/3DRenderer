#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "vectors.h"
#include "texture.h"

typedef struct {
	int a;
	int b;
	int c;
	tex2_t a_uv;
	tex2_t b_uv;
	tex2_t c_uv;
	uint32_t color;
} face_t;

typedef struct {
	vct2_t points[3];
	tex2_t texCoords[3]; // texture coordinates
	uint32_t color;
	float aveFaceDepth;
}triange_t;

void drawFilledTriangle(int x, int y, int x1, int y1, int x2, int y2, uint32_t color);
void drawTriangle(int x, int y, int x1, int y1, int x2, int y2, uint32_t color);

void drawTexturedTriangle(
		int x0, int y0, float u0, float v0,
		int x1, int y1, float u1, float v1,
		int x2, int y2, float u2, float v2,
		uint32_t* texture);