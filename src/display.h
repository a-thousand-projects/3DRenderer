#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)


 enum cull_method {
    CULL_NONE,
    CULL_BACKFACE
} ;//cull_method_t;

 enum render_method {
    RENDER_WIRE,
    RENDER_WIRE_VERTEX,
    RENDER_FILL_TRIANGLE,
    RENDER_FILL_TRIANGLE_WIRE,
    RENDER_TEXTURED,
    RENDER_TEXTURED_WIRE
};//  render_method_t;



//extern SDL_Window* window;
//extern SDL_Renderer* renderer;
//extern uint32_t* color_buffer;
//extern float* z_buffer;
//extern SDL_Texture* color_buffer_texture;
//extern int window_width;
//extern int window_height;

bool initialize_window(void);
void draw_grid(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void clear_z_buffer();

float get_zBuffer_at(int x, int y);
void set_zBuffer_at(int x, int y, float value);

void destroy_window(void);

int get_window_width(void);
int get_window_height(void);

void set_render_method(int method);
void set_cull_method(int method);

int get_render_method(void);
int get_cull_method(void);

bool is_cull_backface(int method);
bool is_render_method(int method);

bool should_render_filled_triangle(void);
bool should_render_textured_triangle(void);
bool should_render_triangle_wireframe(void);
bool should_render_vertex_points(void);



#endif
