#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "vectors.h"

typedef struct {
	int a;
	int b;
	int c;
	uint32_t color;
} face_t;

typedef struct {
	vct2_t points[3];
	uint32_t color;
	float aveFaceDepth;
}triange_t;

void drawFilledTriangle(int x, int y, int x1, int y1, int x2, int y2, uint32_t color);