#ifndef _DISPLAY_H
#define _DISPLAY_H


#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)

typedef enum
{
    GRID_LINE,
    GRID_DOTS
}gridMode_t;

extern int window_height;
extern int window_width;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* colorBufferTexture;
extern uint32_t* colorBuffer;
extern bool is_running;
extern uint32_t prevFrameTime;




void process_input(void);
void destroyWindow(void);
void drawRect(int x, int y, int width, int height, uint32_t color);
void drawHorzLine(int x, int y, int length, uint32_t color);
void drawGrid(uint8_t col, uint8_t row, uint32_t color, gridMode_t mode);
void renderColorBuffer(void);
bool initialize_window(void);
void clearColorBuffer(uint32_t color);
bool checkWindowBounds(uint16_t x, uint16_t y);
void drawPixel(int x, int y, uint32_t color);
void drawLine(int x, int y, int x1, int y1, uint32_t color);
void drawTriangle(int x, int y, int x1, int y1, int x2, int y2, uint32_t color);

#endif