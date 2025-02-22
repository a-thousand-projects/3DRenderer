#include "vector.h"
#include "camera.h"
#include "matrix.h"

camera_t camera = {
};

void init_camera(vec3_t  position, vec3_t direction)
{
    camera.position = position;
    camera.direction = direction;
    camera.forward_verlocity = vec3_new(0,0,0);
    camera.yaw = 0.0;
    camera.pitch = 0.0;
}

vec3_t get_camera_position()
{
    return camera.position;
}

vec3_t get_camera_direction()
{
    return camera.direction;
}

vec3_t get_camera_forward_velocity()
{
    return camera.forward_verlocity;
}

float get_camera_yaw()
{
    return camera.yaw;
}

float get_camera_pitch()
{
    return camera.pitch;
}

void set_camera_position(vec3_t position)
{
    camera.position = position;
}

void set_camera_direction(vec3_t direction)
{
    camera.direction = direction;   
}

void set_camera_forward_velocity(vec3_t forward_velocity)
{
    camera.forward_verlocity = forward_velocity;
}


void rotate_camera_yaw(float angle)
{
    camera.yaw += angle;
}

void rotate_camera_pitch(float angle)
{
    camera.pitch += angle;
}

vec3_t get_camera_lookat_target(void) {
    // Initialize the target looking at the positive z-axis
    vec3_t target = { 0, 0, 1 };
    
    mat4_t camera_yaw_rotation = mat4_make_rotation_y(camera.yaw);
    mat4_t camera_pitch_rotation = mat4_make_rotation_x(camera.pitch);

    // Create camera rotation matrix based on yaw and pitch
    mat4_t camera_rotation = mat4_identity();
    camera_rotation = mat4_mul_mat4(camera_pitch_rotation, camera_rotation);
    camera_rotation = mat4_mul_mat4(camera_yaw_rotation, camera_rotation);

    // Update camera direction based on the rotation
    vec4_t camera_direction = mat4_mul_vec4(camera_rotation, vec4_from_vec3(target));
    camera.direction = vec3_from_vec4(camera_direction);

    // Offset the camera position in the direction where the camera is pointing at
    target = vec3_add(camera.position, camera.direction);

    return target;
}

/*mat4_t mat4_look_at(vec3_t eye, vec3_t target, vec3_t up)
{

    // Compute the forward (z), right (x) and up(y) vectors
    vec3_t z = vec3_sub(target,eye);
    vec3_normalize(&z);

    vec3_t x = vec3_cross(up,z);
    vec3_normalize(&x);

    vec3_t y = vec3_cross(z,x);

    // | x.x    x.y     x.z     -dot(x,eye) |
    // | y.x    y.y     y.z     -dot(y,eye) |
    // | z.x    z.y     z.z     -dot(z,eye) |
    // |   0      0       0               1 |


    mat4_t view_matrix = {{
        { x.x, x.y, x.z, -vec3_dot(x,eye) },
        { y.x, y.y, y.z, -vec3_dot(y,eye) },
        { z.x, z.y, z.z, -vec3_dot(z,eye) },
        { 0,0,1}
    }};

    return view_matrix;

};
*/