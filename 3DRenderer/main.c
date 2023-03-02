#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vectors.h"

#define N_POINTS 9*9*9
vct3_t cubePoints[N_POINTS];
vct2_t projectedPoints[N_POINTS];
vct3_t cameraPosition = {0,0,-4};
vct3_t cubeRotation = { 0,0,0 };
float fovFactor = 600;

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
        for (float y=-1; y<=1; y += 0.25)
            for (float z = -1; z <= 1; z += 0.25)
            {
                vct3_t newPoint = { .x=x,.y=y,.z=z };
                cubePoints[pointCount++] = newPoint;
            }

}


vct2_t project(vct3_t point)
{
    vct2_t projectedPoint = {
        .x = (fovFactor * point.x)/point.z,
        .y = (fovFactor * point.y)/point.z
    };
    return projectedPoint;
}

void update(void) {

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), prevFrameTime+FRAME_TARGET_TIME));

    prevFrameTime = SDL_GetTicks();


    cubeRotation.y += 0.1;
    cubeRotation.x += 0.001;
    cubeRotation.z += 0.001;
    

    for (int i = 0; i < N_POINTS; i++)
    {
        vct3_t point = cubePoints[i];
        vct3_t transformedPoint = vec3RotoateY(point, cubeRotation.y);
        transformedPoint = vec3RotoateZ(transformedPoint, cubeRotation.z);
       // transformedPoint = vec3RotoateX(transformedPoint, cubeRotation.x);
        // translate the points away from the camera
        transformedPoint.z -= cameraPosition.z;
        vct2_t projectedPoint = project(transformedPoint);
        projectedPoints[i] = projectedPoint;
    }
}

void render(void)
{
    

    //drawGrid(50, 50, 0x0000FF00, GRID_DOTS);
    for (int i = 0; i < N_POINTS; i++ )
    {
        drawRect(
            projectedPoints[i].x + (window_width/2), 
            projectedPoints[i].y + (window_height/2),
            4,
            4, 
            0xFFFFFF00);
        
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

