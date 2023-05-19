#include <stdio.h>
#include "stdint.h"
#include "light.h"


uint32_t lightApplyIntensity(uint32_t orgColor, float factor)
{
	if (factor < 0) factor = 0;
	if (factor > 1) factor = 1;
	uint32_t a = (orgColor & 0xFF000000);
	uint32_t r = (orgColor & 0x00FF0000)* factor;
	uint32_t g = (orgColor & 0x0000FF00)* factor;
	uint32_t b = (orgColor & 0x000000FF)* factor;
	uint32_t newCol = a | (r & 0x00ff0000) | (g & 0x0000ff00) | (b & 0x000000ff);
	return newCol; 
}
