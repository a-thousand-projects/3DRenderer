#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vectors.h"
#include "mesh.h"


triange_t triToRender[N_MESH_FACES];
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
    
    //loop all triangle faces
    for (int i = 0; i < N_MESH_FACES; i++)
    {
        face_t meshFace = mesFaces[i];
        vct3_t faceVertices[3];
        faceVertices[0] = meshVertices[meshFace.a - 1];
        faceVertices[1] = meshVertices[meshFace.b - 1];
        faceVertices[2] = meshVertices[meshFace.c - 1];
        // loop all three vertives and apply transfrmations
        triange_t projectedTriangle;
        for (int v = 0; v < 3; v++)
        {
            vct3_t transformedVertice = faceVertices[v];
            transformedVertice = vec3RotoateY(transformedVertice, cubeRotation.y);
            transformedVertice = vec3RotoateZ(transformedVertice, cubeRotation.z);
            transformedVertice = vec3RotoateX(transformedVertice, cubeRotation.x);

            // translate the points away from the camera
            transformedVertice.z -= cameraPosition.z;
            vct2_t projectedPoint = project(transformedVertice);
            
            // Scale and transate to middle of te screen
            projectedPoint.x += (window_width / 2);
            projectedPoint.y += (window_height / 2);
            projectedTriangle.points[v] = projectedPoint;
        }
        triToRender[i] = projectedTriangle;
    }


}

void render(void)
{
    

    //drawGrid(50, 50, 0x0000FF00, GRID_DOTS);
    for (int i = 0; i < N_MESH_FACES; i++)
    {
        triange_t triangle = triToRender[i];
        for (int j = 0; j < 3; j++)
        {

            drawRect(
                triangle.points[j].x,
                triangle.points[j].y,
                4,
                4,
                0xFFFFFF00);
        }
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

