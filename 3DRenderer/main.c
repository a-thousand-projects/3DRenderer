#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vectors.h"
#include "mesh.h"
#include "array.h"
#include "matrix.h"
#include "light.h"
#include "texture.h"
#include "triangle.h"


triange_t *triToRender = NULL;
vct3_t cameraPosition = {0,0,0};
vct3_t lightPosition = { 0,0,1 };
mat4_t projectionMatrix;

int previous_frame_time = 0;



void setup(void) {

    renderMethod = RENDER_WIRE_VERTEX;
    enableFaceCulling = true;

    colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    uint32_t sz = sizeof(colorBuffer);
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width, window_height);

    // Init the prespective Projection matrix
    float fov = (float)M_PI / 3.0; // 60 Deg in radians
    float aspect = (float)window_height / (float)window_width;
    float znear = (float)0.1;
    float zfar = 100.0;
    projectionMatrix = matMakeProjection(fov,aspect,znear,zfar);

    mesh_texture = (uint32_t*)REDBRICK_TEXTURE;

    loadCubeMeshData();
   // loadObjDatafromFile("assets/cube.obj");
   //loadObjDatafromFile("assets/f22.obj");
   // loadObjDatafromFile("assets/clamp.obj");

    mesh.translation.z = 10;

}


void setZoom(int z)
{
    mesh.translation.z += z;
}

void update(void) {

    // Wait some time until the reach the target frame time in milliseconds
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    // Only delay execution if we are running too fast
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    prevFrameTime = SDL_GetTicks();

    triToRender = NULL;

  //  mesh.rotation.y += 0.01;
    mesh.rotation.x += 0.03;
  //  mesh.rotation.z += 0.01;
    
  //  mesh.scale.x += 0.002;
  //  mesh.scale.y += 0.001;
  //  mesh.scale.z += 0.001;

   
 

   // mesh.translation.x += 0.01;
   // mesh.translation.z = 100.0;

    // Create a scale, rotate and translate matrix 
    mat4_t scaleMatrix = matMakeScale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    mat4_t translateMatrix = matMakeTranslate(mesh.translation.x, mesh.translation.y, mesh.translation.z);
    mat4_t rotateMatrixX = matMakeRotateX(mesh.rotation.x);
    mat4_t rotateMatrixY = matMakeRotateY(mesh.rotation.y);
    mat4_t rotateMatrixZ = matMakeRotateZ(mesh.rotation.z);
    
    //loop all triangle faces
    int meshFaceSize = array_length(mesh.faces);
    for (int i = 0; i < meshFaceSize; i++)
    {
        face_t meshFace = mesh.faces[i];
        vct3_t faceVertices[3] = {0,0,0};

        faceVertices[0] = mesh.vertices[meshFace.a - 1];
        faceVertices[1] = mesh.vertices[meshFace.b - 1];
        faceVertices[2] = mesh.vertices[meshFace.c - 1];
        vct4_t transformedVertices[3];

        // loop all three vertives and apply transfrmation
        for (int v = 0; v < 3; v++)
        {       
            
            vct4_t transformedVertice = vec3ToVec4(faceVertices[v]);
            // Create a wold Matrix for Scale, Rotation and transformation

            mat4_t worldMatrix = matIdenetity();
            // Order Matters
            worldMatrix = mat4MulMat4(scaleMatrix,worldMatrix );
            worldMatrix = mat4MulMat4(rotateMatrixZ,worldMatrix );
            worldMatrix = mat4MulMat4(rotateMatrixY,worldMatrix );
            worldMatrix = mat4MulMat4(rotateMatrixX,worldMatrix );
            worldMatrix = mat4MulMat4(translateMatrix,worldMatrix );

            transformedVertice = mat4MulVec4(worldMatrix, transformedVertice); // Left Matrix transforms one on right!

            transformedVertices[v] = transformedVertice;
            // translate the points away from the camera
            
        }

        // Do backface culling check
        vct3_t vectorA = vec4ToVec3(transformedVertices[0]); /*   A    */
        vct3_t vectorB = vec4ToVec3(transformedVertices[1]); /*  / \   */
        vct3_t vectorC = vec4ToVec3(transformedVertices[2]); /* B---C  */

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
        // Calc how aligned the ray and face normal is
        float cull = vct3Dot (vectorNormal,cameraRay);
        if (enableFaceCulling)
        {
            if (cull < 0)
            {
                continue;
            }
        }
     


        // calculate light shading 
        float lightFactor = -vct3Dot(vectorNormal, lightPosition);
        
        ////////////////////////////////////////////////////////////
        // Do Projection
        ///////////////////////////////////////////////////////////
        vct4_t projectedPoints[3];
        for (int v = 0; v < 3; v++)
        {
            // transate to middle of te screen
            projectedPoints[v] = mat4MulVec4Project(projectionMatrix, transformedVertices[v]);
            projectedPoints[v].x *= (window_width / 2.0);
            projectedPoints[v].y *= (window_height / 2.0);

            // Invert Y values cos screen grows down, not up
            projectedPoints[v].y *= -1;

            // Scale into view
            projectedPoints[v].x += (window_width / 2.0);
            projectedPoints[v].y += (window_height / 2.0);
        }

        // Calc the Average face depth after transformation
        float avg_depth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;

        triange_t projectedTriangle = {

            {
                projectedPoints[0].x, projectedPoints[0].y,
                projectedPoints[1].x, projectedPoints[1].y,
                projectedPoints[2].x, projectedPoints[2].y,
            },
            .texCoords = {
                {meshFace.a_uv.u,meshFace.a_uv.v},
                {meshFace.b_uv.u,meshFace.b_uv.v},
                {meshFace.c_uv.u,meshFace.b_uv.v},
            },
            lightApplyIntensity(meshFace.color,lightFactor),
            avg_depth
        };

        array_push(triToRender, projectedTriangle);
    }
    /* sort triangles to render by ave depth*/

    /* Simple Buble Sort*/
    uint16_t triangleCount = array_length(triToRender);
   
    for (int i = 0; i < triangleCount; i++)
    {
        for (int j = i; j < triangleCount; j++)
        {
            if (triToRender[i].aveFaceDepth < triToRender[j].aveFaceDepth)
            {
                triange_t temp = triToRender[i];
                triToRender[i] = triToRender[j];
                triToRender[j] = temp;
            }
        }
    }
}

void render(void)
{
   

    drawGrid(50, 50, 0x0000FF00, GRID_DOTS);
    uint16_t triArrayLen = array_length(triToRender);
    int dotSize = 10 / 2;
   for (int i = 0; i < triArrayLen; i++)
    {
        triange_t triangle = triToRender[i];
        if (renderMethod == RENDER_WIRE)
        {
            drawRect(triangle.points[0].x - dotSize, triangle.points[0].y - dotSize, dotSize, dotSize, 0xFF0000);
            drawRect(triangle.points[1].x - dotSize, triangle.points[1].y - dotSize, dotSize, dotSize, 0xFF0000);
            drawRect(triangle.points[2].x - dotSize, triangle.points[2].y - dotSize, dotSize, dotSize, 0xFF0000);
        } 
        // Draw Textured Triangle 
        if (renderMethod == RENDER_TEXTURED || renderMethod == RENDER_FILLED_TRIANGLE_WIRE)
        {
             drawTexturedTriangle(  triangle.points[0].x,triangle.points[0].y,triangle.texCoords[0].u,triangle.texCoords[0].v,
                                    triangle.points[1].x, triangle.points[1].y, triangle.texCoords[1].u, triangle.texCoords[1].v,
                                    triangle.points[2].x, triangle.points[2].y, triangle.texCoords[2].u, triangle.texCoords[2].v,
                                    mesh_texture);
        }
        
        if (renderMethod == RENDER_FILLED_TRIANGLE || renderMethod == RENDER_FILLED_TRIANGLE_WIRE)
        {
            drawFilledTriangle(triangle.points[0].x,triangle.points[0].y,
                triangle.points[1].x, triangle.points[1].y,
                triangle.points[2].x, triangle.points[2].y,
                triangle.color );
        }
       
        if (renderMethod == RENDER_WIRE_VERTEX  || renderMethod == RENDER_WIRE || renderMethod == RENDER_TEXTURED_WIRE)
        {
            drawTriangle(triangle.points[0].x,triangle.points[0].y,
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

