#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vectors.h"

#define N_POINTS 9*9*9
vct3_t cubePoints[N_POINTS];
vct2_t projectedPoints[N_POINTS];


void setup(void) {

    colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    uint32_t sz = sizeof(colorBuffer);
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width, window_height);
    int pointCount = 0;
    for (float x = -1 ;x<=1 ; x += 0.25)
        for (float y=1; y<=1; y+= 0.25)
            for (float z = 1; z <= 1; z += 0.25)
            {
                vct3_t newPoint = { x,y,z };
                cubePoints[pointCount++] = newPoint;
            }

}


vct2_t project(vct3_t point)
{
    vct2_t projectedPoint = {
        .x = point.x,
        .y = point.y
    };
    return projectedPoint;
}

void update(void) {
    for (int i = 0; i < N_POINTS; i++)
    {
        vct3_t point = cubePoints[i];
        vct2_t projectedPoint = project(point);
        projectedPoints[i] = projectedPoint;
    }
}

void render(void)
{
    
    //drawGrid(50, 50, 0x0000FF00, GRID_DOTS);
    for (int i = 0; i < N_POINTS; i++ )
    {
        drawRect(projectedPoints[i].x, projectedPoints[i].y,4,4, 0xFFFFFF00);
    }
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

