#include "clipping.h"
#include "math.h"
#define NUM_PLANES 6
plane_t frustum_planes[NUM_PLANES];

///////////////////////////////////////////////////////////////////////////////
// Frustum planes are defined by a point and a normal vector
///////////////////////////////////////////////////////////////////////////////
// Near plane   :  P=(0, 0, znear), N=(0, 0,  1)
// Far plane    :  P=(0, 0, zfar),  N=(0, 0, -1)
// Top plane    :  P=(0, 0, 0),     N=(0, -cos(fov/2), sin(fov/2))
// Bottom plane :  P=(0, 0, 0),     N=(0, cos(fov/2), sin(fov/2))
// Left plane   :  P=(0, 0, 0),     N=(cos(fov/2), 0, sin(fov/2))
// Right plane  :  P=(0, 0, 0),     N=(-cos(fov/2), 0, sin(fov/2))
///////////////////////////////////////////////////////////////////////////////
//
//           /|\
//         /  | | 
//       /\   | |
//     /      | |
//  P*|-->  <-|*|   ----> +z-axis
//     \      | |
//       \/   | |
//         \  | | 
//           \|/
//
///////////////////////////////////////////////////////////////////////////////

void init_frustrum_planes(float fov, float z_near, float z_far)
{
float cos_half_fov = cos(fov / 2);
float sin_half_fov = sin(fov / 2);



frustum_planes[LEFT_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
frustum_planes[LEFT_FRUSTUM_PLANE].normal.x = cos_half_fov;
frustum_planes[LEFT_FRUSTUM_PLANE].normal.y = 0;
frustum_planes[LEFT_FRUSTUM_PLANE].normal.z = sin_half_fov;

frustum_planes[RIGHT_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
frustum_planes[RIGHT_FRUSTUM_PLANE].normal.x = -cos_half_fov;
frustum_planes[RIGHT_FRUSTUM_PLANE].normal.y = 0;
frustum_planes[RIGHT_FRUSTUM_PLANE].normal.z = sin_half_fov;

frustum_planes[TOP_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
frustum_planes[TOP_FRUSTUM_PLANE].normal.x = 0;
frustum_planes[TOP_FRUSTUM_PLANE].normal.y = -cos_half_fov;
frustum_planes[TOP_FRUSTUM_PLANE].normal.z = sin_half_fov;

frustum_planes[BOTTOM_FRUSTUM_PLANE].point = vec3_new(0, 0, 0);
frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.x = 0;
frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.y = cos_half_fov;
frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.z = sin_half_fov;

frustum_planes[NEAR_FRUSTUM_PLANE].point = vec3_new(0, 0, z_near);
frustum_planes[NEAR_FRUSTUM_PLANE].normal.x = 0;
frustum_planes[NEAR_FRUSTUM_PLANE].normal.y = 0;
frustum_planes[NEAR_FRUSTUM_PLANE].normal.z = 1;

frustum_planes[FAR_FRUSTUM_PLANE].point = vec3_new(0, 0, z_far);
frustum_planes[FAR_FRUSTUM_PLANE].normal.x = 0;
frustum_planes[FAR_FRUSTUM_PLANE].normal.y = 0;
frustum_planes[FAR_FRUSTUM_PLANE].normal.z = -1;
}



polygon_t create_poygon_from_triangle(vec3_t v0, vec3_t v1, vec3_t v2)
{
    polygon_t polygon;    
    polygon.num_vertices = 3;
    polygon.vertices[0] = v0;
    polygon.vertices[1] = v1;
    polygon.vertices[2] = v2;
    return polygon;
}


void clip_Polygon(polygon_t * polygon)
{
    clip_polygon_against_plane(polygon, LEFT_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, RIGHT_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, TOP_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, BOTTOM_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, NEAR_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, FAR_FRUSTUM_PLANE);
}


void clip_polygon_against_plane(polygon_t *polygon, e_frustrum_planes plane)
{
    vec3_t plane_point = frustum_planes[plane].point;
    vec3_t plane_normal = frustum_planes[plane].normal;

    // create an array for clipping the polygon
    vec3_t inside_vertices[MAX_VERTICES];
    int num_insdie_vertices = 0;

    // Init current and last
    vec3_t *current_vertex = &polygon->vertices[0];
    vec3_t *previous_vertex = &polygon->vertices[polygon->num_vertices-1];

    // Get current and previouse dot products
    float current_dot = vec3_dot(vec3_sub(*current_vertex, plane_point),plane_normal);
    float previous_dot = vec3_dot(vec3_sub(*previous_vertex,plane_point),plane_normal );

    while(current_vertex != &polygon->vertices[polygon->num_vertices])
    {
        current_dot = vec3_dot(vec3_sub(*current_vertex, plane_point),plane_normal);

        if (current_dot * previous_dot < 0)
        {
            // Calculate interpolation factor,  t = gotQ1 / (dotQ1 - dotQ2)
            vec3_t Q1_Q2 = vec3_sub(current_dot - previous_dot);
            float t = current_dot / ;

            // Calculate intercection point , I = Q1 +t(Q2-Q1)

            inside_vertices[num_insdie_vertices] = vec3_clone(&interception_point);
            num_insdie_vertices++;
        }

        if (current_dot > 0)
        {
            inside_vertices[num_insdie_vertices] = vec3_clone(current_vertex);
            num_insdie_vertices++;
        }


        // Move to next vertex
        previous_dot = current_dot;
        previous_vertex = current_vertex;
        current_vertex++;

    }

}