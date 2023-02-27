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

extern int window_height;
extern int window_width;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* colorBufferTexture;
extern uint32_t* colorBuffer;
extern bool is_running;




void process_input(void);
void destroyWindow(void);
void drawRect(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint32_t color);
void drawHLine(uint16_t x, uint16_t y, uint16_t length, uint32_t color);
void drawGrid(uint8_t col, uint8_t row, uint32_t color, gridMode_t mode);
void renderColorBuffer(void);
bool initialize_window(void);
void clearColorBuffer(uint32_t color);
bool checkWindowBounds(uint16_t x, uint16_t y);
void drawPixel(uint16_t x, uint16_t y, uint32_t color);

#endif