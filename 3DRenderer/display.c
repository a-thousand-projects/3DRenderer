#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"


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


void drawHLine(uint16_t x, uint16_t y, uint16_t length, uint32_t color)
{
    for (int xd = x; xd < length + x; xd++)
    {
        colorBuffer[(window_width * y) + xd] = color;
    }
}

void drawRect(uint16_t x, uint16_t y, uint16_t height, uint16_t width, uint32_t color)
{
    for (uint16_t h = y; h < height + y; h++)
    {
        drawHLine(x, h, x + width, color);
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


