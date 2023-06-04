#include "vectors.h"
#include <math.h>


float vct2Length(vct2_t v)
{
	return (sqrtf(v.x*v.x + v.y*v.y));
}


vct2_t vct2Add(vct2_t a, vct2_t b)
{
	vct2_t r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}



vct2_t vct2Subtract(vct2_t a, vct2_t b)
{
	vct2_t r;
	r.x = a.x - a.x;
	r.y = a.y - b.y;
	return r;
}

void vct2Nomialiase(vct2_t* a)
{
	float length = sqrt(a->x * a->x + a->y * a->y);
	a->x /= length;
	a->y /= length;
}



vct2_t vct2Mul(vct2_t a, float factor)
{
	vct2_t result = { 
		a.x * factor, 
		a.y * factor };
	return result;
};

vct2_t vct2Div(vct2_t a, float factor) 
{
	vct2_t result = {
		.x = a.x / factor,
		.y = a.y / factor };
	return result;
};

float vct2Dot(vct2_t a, vct2_t b)
{
	return (a.x * b.x) + (a.y * b.y) ;
}


/************************************************
* 3D Vectors
*************************************************/
vct3_t vct3Add(vct3_t a, vct3_t b)
{
	vct3_t r;
	r.x = a.x + b.x;
	r.x = a.y + b.y;
	r.x = a.z + b.z;
	return r;
}

vct3_t vct3Subtract(vct3_t a, vct3_t b)
{
	vct3_t r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return r;
}

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

float vct3Length(vct3_t v)
{
	return (sqrtf(v.x*v.x + v.y *v.y + v.z*v.z));
}

vct3_t vct3Mul(vct3_t a, float factor) 
{
	vct3_t result = {
		.x = a.x * factor,
		.y = a.y * factor,
		.z = a.z * factor};
	return result;
};

vct3_t vct3Div(vct3_t a, float factor) 
{
	vct3_t result = {
		.x = a.x / factor,
		.y = a.y / factor,
		.z = a.z / factor };
	return result;
};

vct3_t vct3Cross(vct3_t a, vct3_t b)
{
	vct3_t result = {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
	return result;
}

float vct3Dot(vct3_t a, vct3_t b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void vct3Nomialiase(vct3_t* a)
{
	float length = sqrt((a->x * a->x) + (a->y * a->y) + (a->z * a->z));
	a->x /= length;
	a->y /= length;
	a->z /= length;
}

vct4_t vec3ToVec4(vct3_t v)
{
	vct4_t result = {0,0,0,0};
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	result.w = 1.0;
	return result;
}

vct3_t vec4ToVec3(vct4_t v)
{
	vct3_t result = { v.x,v.y,v.z };
	return result;
}
