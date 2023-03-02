#include "vectors.h"
#include <math.h>

vct3_t vec3RotoateX(vct3_t v, float angle)
{
	vct3_t rotateVector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z * sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle)
	};
	return rotateVector;
}

vct3_t vec3RotoateY(vct3_t v, float angle)
{
	vct3_t rotateVector = {
		.x = v.x * cos(angle) - v.z * sin(angle),
		.y = v.y,
		.z = v.x * sin(angle) + v.z * cos(angle)
	};
	return rotateVector;
}

vct3_t vec3RotoateZ(vct3_t v, float angle)
{
	vct3_t rotateVector = {
		.x = v.x * cos(angle) - v.y * sin(angle),
		.y = v.x * sin(angle) + v.y * cos(angle),
		.z = v.z
	};
	return rotateVector;
}