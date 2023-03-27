#include "mesh.h"
#include "array.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0,0,0}
};
/*
vct3_t cubeVertices[N_CUBE_VERTICES] = {
    {.x = -1 ,.y = -1 ,.z = -1},
    {.x = -1 , .y = 1 , .z = -1},
    {.x = 1 , .y = 1 , .z = -1},
    {.x = 1 , .y = -1 , .z = -1},
    {.x = 1 , .y = 1 , .z = 1},
    {.x = 1 , .y = -1 , .z = 1},
    {.x = -1 , .y = 1 , .z = 1},
    {.x = -1 , .y = -1 , .z = 1},
};

face_t cubeFaces[N_CUBE_FACES] = {
    // front
    {.a = 1, .b = 2, .c = 3 },
    {.a = 1, .b = 3, .c = 4 },
    // right
    {.a = 4, .b = 3, .c = 5 },
    {.a = 4, .b = 5, .c = 6 },
    // back
    {.a = 6, .b = 5, .c = 7 },
    {.a = 6, .b = 7, .c = 8 },
    // left
    {.a = 8, .b = 7, .c = 2 },
    {.a = 8, .b = 2, .c = 1 },
    // top
    {.a = 2, .b = 7, .c = 5 },
    {.a = 2, .b = 5, .c = 3 },
    // bottom
    {.a = 6, .b = 8, .c = 1 },
    {.a = 6, .b = 1, .c = 4 }
};

void loadCubeMeshData(void)
{
    for (int i = 0; i < N_CUBE_VERTICES; i++)
    {
        array_push(mesh.vertices, cubeVertices[i]);
    }

    for (int i = 0; i < N_CUBE_FACES; i++)
    {
        array_push(mesh.faces, cubeFaces[i]);
    }

}
*/


void loadObjDatafromFile(char* filename)
{
    FILE* filePtr;
    char objString[1024];
    errno_t err = 0;
    err = fopen_s(&filePtr, filename, "r");
    
    char* tokenPtr = NULL;
    char* next = NULL;
    if (!filePtr)
    {
        return;
    }


    while (fgets(objString, 1024, filePtr))
    {
        
        if (!strncmp(objString,"v ",2))
        {
            vct3_t vector = {0,0,0};
            /* Process a vector (v -1.000000 -1.000000 1.000000) */
            sscanf_s(objString, "v %f %f %f", &vector.x, &vector.y, &vector.z);
            array_push(mesh.vertices, vector);
            printf("V = %f,%f,%f\n\r", vector.x, vector.y, vector.z);
        }

        if (!strncmp(objString, "f ", 2))
        {
            /* f 1/1/1 2/2/1 3/3/1 */
            face_t face = { 0,0,0 };
            int texture[3] = { 0,0,0 };
            int normal[3] = { 0,0,0 };
            sscanf_s(&objString,
                "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &face.a, &texture[0], &normal[0],
                &face.b, &texture[1], &normal[1],
                &face.c, &texture[2], &normal[2]);
            
            array_push(mesh.faces, face);
            printf("F = %i,%i,%i\n\r", face.a, face.b, face.c);
        }


    }  
    printf("Vertice Count : %d\n\r", array_length(mesh.vertices));
    printf("Face Count    : %d\n\r", array_length(mesh.faces));

 }