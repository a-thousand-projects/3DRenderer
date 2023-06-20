#pragma once

#include <stdint.h>

typedef struct
{
	float u;
	float v;
} tex2_t;

extern int textureWidth;
extern int textureHeight;
                     
extern const uint8_t REDBRICK_TEXTURE[];

extern  uint32_t* mesh_texture;