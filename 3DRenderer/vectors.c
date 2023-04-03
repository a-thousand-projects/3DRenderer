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


float vct2Length(vct2_t v2)
{
	float x = powf(v2.x, 2);
	float y = powf(v2.y, 2);
	return (sqrtf(x + y));
}
float vct3Length(vct3_t v3)
{
	float x = powf(v3.x, 2);
	float y = powf(v3.y, 2);
	float z = powf(v3.z, 2);
	return (sqrtf(x + y + z));
}

vct2_t vct2Add(vct2_t a, vct2_t b)
{
	vct2_t r;
	r.x = a.x + a.x;
	r.y = a.y + b.y;
	return r;
}

vct3_t vct3Add(vct3_t a, vct3_t b)
{
	vct3_t r;
	r.x = a.x + b.x;
	r.x = a.y + b.y;
	r.x = a.z + b.z;
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

vct3_t vct3Subtract(vct3_t a, vct3_t b)
{
	vct3_t r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return r;
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
		a.x / factor,
		a.y / factor };
	return result;
};

float vct2Dot(vct2_t a, vct2_t b)
{
	return (a.x * b.x) + (a.y * b.y) ;
}

vct3_t vct3Mul(vct3_t a, float factor) 
{
	vct3_t result = {
		a.x * factor,
		a.y * factor,
		a.z * factor};
	return result;
};

vct3_t vct3Div(vct3_t a, float factor) 
{
	vct3_t result = {
		a.x / factor,
		a.y / factor,
		a.z / factor };
	return result;
};

vct3_t vct3Cross(vct3_t a, vct3_t b)
{
	vct3_t result = {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
	return result;
}

float vct3Dot(vct3_t a, vct3_t b)
{
	return (a.x* b.x) + (a.y * b.y) + (a.z * b.z);
}



void vct3Nomialiase(vct3_t* a)
{
	float length = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x /= length;
	a->y /= length;
	a->z /= length;
}