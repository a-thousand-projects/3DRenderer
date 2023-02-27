#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"




void setup(void) {

    colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    uint32_t sz = sizeof(colorBuffer);
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width, window_height);
}



void update(void) {
    // TODO:
}

void render(void)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    drawGrid(50, 50, 0x0000FF00, GRID_DOTS);
    drawHLine(500, 500, 200, 0xFF00FF00);
    drawRect(500, 700, 200, 100, 0xABAAFAbb);
    renderColorBuffer();
    clearColorBuffer(0x00000000);
    SDL_RenderPresent(renderer);
}

int main()
{
    is_running = initialize_window();

    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }

    destroyWindow();
    return 0;
}

