#ifndef CLIPPING_H
#define CLIPPING_H

#include "vector.h"

#define MAX_VERTICES 10

typedef enum {
    LEFT_FRUSTUM_PLANE,
    RIGHT_FRUSTUM_PLANE,
    TOP_FRUSTUM_PLANE,
    BOTTOM_FRUSTUM_PLANE,
    NEAR_FRUSTUM_PLANE,
    FAR_FRUSTUM_PLANE,
} e_frustrum_planes;

typedef struct {
    vec3_t point;
    vec3_t normal;    

} plane_t;

typedef struct {
    vec3_t vertices[MAX_VERTICES];
    int num_vertices;
} polygon_t;


void init_frustrum_planes(float fov, float z_near, float z_far);
polygon_t create_poygon_from_triangle(vec3_t v0, vec3_t v1, vec3_t v2);
void clip_polygon_against_plane(polygon_t *polygon, e_frustrum_planes plane);
void clip_Polygon(polygon_t * polygon);


#endif