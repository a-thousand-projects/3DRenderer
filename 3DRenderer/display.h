#ifndef _DISPLAY_H
#define _DISPLAY_H


#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

typedef enum
{
    GRID_LINE,
    GRID_DOTS
}gridMode_t;

int window_height;
int window_width;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* colorBufferTexture;
uint32_t* colorBuffer;
bool is_running;




void process_input(void);
void destroyWindow(void);
void drawRect(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint32_t color);
void drawHLine(uint16_t x, uint16_t y, uint16_t length, uint32_t color);
void drawGrid(uint8_t col, uint8_t row, uint32_t color, gridMode_t mode);
void renderColorBuffer(void);
bool initialize_window(void);
void clearColorBuffer(uint32_t color);

#endif