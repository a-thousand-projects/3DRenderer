#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"

int window_height = 600;
int window_width = 800;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* colorBufferTexture = NULL;
uint32_t* colorBuffer = NULL;
bool is_running = false;
uint32_t prevFrameTime=0;

bool initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    // Get full monitor res from SDL
    SDL_DisplayMode displaymode;
    SDL_GetCurrentDisplayMode(0, &displaymode);
    window_width = displaymode.w;
    window_height = displaymode.h;

    // Create a SDL Window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void renderColorBuffer(void)
{
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int)(window_width * sizeof(uint32_t)));

    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void drawGrid(uint8_t col, uint8_t row, uint32_t color, gridMode_t mode)
{

    for (int x = 0; x < window_width; x++) {
        for (int y = 0; y < window_height; y++) {
            if ((((y % col) == 0) && ((x % row) == 0)) && mode == GRID_DOTS)
            {
                colorBuffer[(window_width * y) + x] = color;
            }
            else if ((((y % col) == 0) || ((x % row) == 0)) && mode == GRID_LINE)
            {
                colorBuffer[(window_width * y) + x] = color;
            }
        }
    }
}

void drawLine(int x, int y, int x1, int y1, uint32_t color)
{
    int deltaX = (x1 - x);
    int deltaY = (y1 - y);

    int sideLength = (abs(deltaX) > abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    // Calculate inc for X & Y
    float incX = deltaX / (float)sideLength;
    float incY = deltaY / (float)sideLength;

    float currentX = x;
    float currentY = y;

    for (int i = 0; i < sideLength; i++)
    {
        drawPixel(round(currentX), round(currentY),color);
        currentX += incX;
        currentY += incY;
    }

}


void drawTriangle(int x, int y, int x1, int y1, int x2, int y2, uint32_t color)
{
    drawLine(x, y, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x, y, color);
}

void drawHLine(uint16_t x, uint16_t y, uint16_t length, uint32_t color)
{
    for (int xd = x; xd < length + x; xd++)
    {
        drawPixel(xd, y, color);
        colorBuffer[(window_width * y) + xd] = color;
    }
}

void drawPixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
        colorBuffer[(window_width * y) + x] = color;
    }
}

void drawRect(int x, int y, int width, int height, uint32_t color)
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            drawPixel(current_x, current_y, color);
        }
    }
}
void destroyWindow(void)
{
    free(colorBuffer);
    SDL_DestroyTexture(colorBufferTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void process_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        break;
    }
}


void clearColorBuffer(uint32_t color)
{
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            colorBuffer[(window_width * y) + x] = color;
        }
    }

}

bool checkWindowBounds(uint16_t x, uint16_t y)
{
    return (x > 0 && x < window_width && y>0 && y < window_height);
}

//void drawPixel(uint16_t x, uint16_t y, uint32_t color)
//{
//    if  (checkWindowBounds(x, y))
//    {
//        colorBuffer[(window_width * y) + x] = color;
//    }
//}