#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vectors.h"
#include "mesh.h"
#include "array.h"


triange_t *triToRender = NULL;
vct3_t cameraPosition = {0,0,-3};

float fovFactor = 1000;

void setup(void) {

    colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    uint32_t sz = sizeof(colorBuffer);
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width, window_height);
    
    //loadCubeMeshData();
    //loadObjDatafromFile("assets/cube.obj");
    loadObjDatafromFile("assets/f22.obj");
    //loadObjDatafromFile("assets/pi.obj");

}


vct2_t project(vct3_t point)    
{
    vct2_t projectedPoint = {
        .x = (fovFactor * point.x)/ (point.z),
        .y = (fovFactor * point.y)/(point.z)
    };
    return projectedPoint;
}

void update(void) {

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), prevFrameTime+FRAME_TARGET_TIME));

    prevFrameTime = SDL_GetTicks();

    triToRender = NULL;

    mesh.rotation.y += 0.00;
    mesh.rotation.x += 0.01;
    mesh.rotation.z += 0.0;
    
    //loop all triangle faces
    int meshFaceSize = array_length(mesh.faces);
    for (int i = 0; i < meshFaceSize; i++)
    {
        face_t meshFace = mesh.faces[i];
        vct3_t faceVertices[3];
        faceVertices[0] = mesh.vertices[meshFace.a - 1];
        faceVertices[1] = mesh.vertices[meshFace.b - 1];
        faceVertices[2] = mesh.vertices[meshFace.c - 1];
        // loop all three vertives and apply transfrmations
        triange_t projectedTriangle;
        for (int v = 0; v < 3; v++)
        {
            vct3_t transformedVertice = faceVertices[v];
            transformedVertice = vec3RotoateY(transformedVertice, mesh.rotation.y);
            transformedVertice = vec3RotoateZ(transformedVertice, mesh.rotation.z);
            transformedVertice = vec3RotoateX(transformedVertice, mesh.rotation.x);

            // translate the points away from the camera
            transformedVertice.z -= cameraPosition.z;
            vct2_t projectedPoint = project(transformedVertice);
            
            // Scale and transate to middle of te screen
            projectedPoint.x += (window_width / 2);
            projectedPoint.y += (window_height / 2);
            projectedTriangle.points[v] = projectedPoint;
        }
        array_push(triToRender, projectedTriangle);
       // triToRender[i] = projectedTriangle;
    }


}

void render(void)
{
   

    //drawGrid(50, 50, 0x0000FF00, GRID_DOTS);
    uint16_t triArrayLen = array_length(triToRender);
    for (int i = 0; i < triArrayLen; i++)
    {
        triange_t triangle = triToRender[i];
        drawTriangle(triangle.points[0].x, triangle.points[0].y,
            triangle.points[1].x, triangle.points[1].y,
            triangle.points[2].x, triangle.points[2].y, 0xFF00FF00);

        drawRect(triangle.points[0].x-3, triangle.points[0].y-3, 5, 5, 0xFF00FF00);
        drawRect(triangle.points[1].x-3, triangle.points[1].y-3, 5, 5, 0xFF00FF00);
        drawRect(triangle.points[2].x-3, triangle.points[2].y-3, 5, 5, 0xFF00FF00);
        
       /* for (int j = 0; j < 3; j++) 
        {
            drawRect(
                triangle.points[j].x,
                triangle.points[j].y,
                4,
                4,
                0xFFFFFF00);
        }*/
    }

    array_free(triToRender);
    renderColorBuffer();
    clearColorBuffer(0x00000000);
    SDL_RenderPresent(renderer);
}

void freeResouces(void)
{
    array_free(mesh.faces);
    array_free(mesh.vertices);
    free(colorBuffer);
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
    freeResouces();
    return 0;
}

