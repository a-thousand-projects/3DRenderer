#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vectors.h"
#include "mesh.h"
#include "array.h"


triange_t *triToRender = NULL;
vct3_t cameraPosition = {0,0,0};

float fovFactor = 1000;

void setup(void) {

    displayWireFrameMode = RenderWireOnly;
    enableFaceCulling = true;

    colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    uint32_t sz = sizeof(colorBuffer);
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width, window_height);
    
    loadCubeMeshData();
    //loadObjDatafromFile("assets/cube.obj");
    //loadObjDatafromFile("assets/f22.obj");
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

    mesh.rotation.y += 0.01;
    mesh.rotation.x += 0.01;
    mesh.rotation.z += 0.01;
    
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
        
        vct3_t transformedVertices[3]; 
        for (int v = 0; v < 3; v++)
        {
            vct3_t transformedVertice = faceVertices[v];
            transformedVertice = vec3RotoateY(transformedVertice, mesh.rotation.y);
            transformedVertice = vec3RotoateZ(transformedVertice, mesh.rotation.z);
            transformedVertice = vec3RotoateX(transformedVertice, mesh.rotation.x);

            // translate the points away from the camera
            transformedVertice.z += 3; // cameraPosition.z;
            transformedVertices[v] = transformedVertice;
        }

        // Do backface culling check
        vct3_t vectorA = transformedVertices[0]; /*   A    */
        vct3_t vectorB = transformedVertices[1]; /*  / \   */
        vct3_t vectorC = transformedVertices[2]; /* B---C  */ 

        vct3_t vectorAB = vct3Subtract(vectorB, vectorA);
        vct3_t vectorAC = vct3Subtract(vectorC, vectorA);
        vct3Nomialiase(&vectorAB);
        vct3Nomialiase(&vectorAC);

        // Computer the Face Normal using the cross product
        vct3_t vectorNormal = vct3Cross(vectorAB, vectorAC); //This order cos we are using left handed system

        // Normalise the Normal

        vct3Nomialiase(&vectorNormal);

        // Find vector between camera and face
        vct3_t cameraRay = vct3Subtract( cameraPosition,vectorA);
        // Calc hpw aligned the ray and face normal is
        float cull = vct3Dot (vectorNormal,cameraRay);
        if (cull < 0 && enableFaceCulling) continue;

        
        vct2_t projectedPoints[3];

        for (int v = 0; v < 3; v++)
        {
            // Scale and transate to middle of te screen
            projectedPoints[v] = project(transformedVertices[v]);
            projectedPoints[v].x += (window_width / 2);
            projectedPoints[v].y += (window_height / 2);
        }


        triange_t projectedTriangle = {

            {
                projectedPoints[0].x, projectedPoints[0].y,
                projectedPoints[1].x, projectedPoints[1].y,
                projectedPoints[2].x, projectedPoints[2].y,
            },
            meshFace.color
        };

        array_push(triToRender, projectedTriangle);
       // triToRender[i] = projectedTriangle;
    }


}

void render(void)
{
   

    //drawGrid(50, 50, 0x0000FF00, GRID_DOTS);
    uint16_t triArrayLen = array_length(triToRender);
    int dotSize = 20 / 2;
   for (int i = 0; i < triArrayLen; i++)
    {
        triange_t triangle = triToRender[i];
        if (displayWireFrameMode == RenderWireAndDot)
        {
            drawRect(triangle.points[0].x - dotSize, triangle.points[0].y - dotSize, dotSize, dotSize, 0xFF0000);
            drawRect(triangle.points[1].x - dotSize, triangle.points[1].y - dotSize, dotSize, dotSize, 0xFF0000);
            drawRect(triangle.points[2].x - dotSize, triangle.points[2].y - dotSize, dotSize, dotSize, 0xFF0000);
        } 
        if (displayWireFrameMode == RenderFilledOnly || displayWireFrameMode == RenderFilledAndWire)
        {
            drawFilledTriangle(triangle.points[0].x, triangle.points[0].y,
                triangle.points[1].x, triangle.points[1].y,
                triangle.points[2].x, triangle.points[2].y, 
                triangle.color);
        }
       
        if (displayWireFrameMode == RenderWireOnly || displayWireFrameMode == RenderFilledAndWire || displayWireFrameMode == RenderWireAndDot)
        {
            drawTriangle(triangle.points[0].x, triangle.points[0].y,
                triangle.points[1].x, triangle.points[1].y,
                triangle.points[2].x, triangle.points[2].y, 0xffff00);
        }
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

