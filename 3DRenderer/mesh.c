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

int readLine(FILE* filePtr, char *line)
{
    char s = 0;
    while (s != '\n' )
    {
        s = fgetc(filePtr);
        *(line++) = s;
        if (feof(filePtr))
        {
            return -1;
        }
    }
    *(line) = 0x0; 
    return 0;
}

void loadObjDatafromFile(char* filename)
{
    FILE* filePtr;
    char objString[50];
    errno_t err = 0;
    err = fopen_s(&filePtr, filename, "r");
    vct3_t vector = {0,0,0};
    char* tokenPtr = NULL;
    char* next = NULL;
    if (!filePtr)
    {
        return;
    }


    while (!readLine(filePtr, objString))
    {
        if (objString[0] == 'v')
        {
            /* Process a vector (v -1.000000 -1.000000 1.000000) */

            /*tokenize string*/
            tokenPtr = strtok_s(objString, " ",&next); /* Skip the first token = V*/
            tokenPtr = strtok_s(NULL, " ",&next); 
            vector.x = (float)atof(tokenPtr);
            tokenPtr = strtok_s(NULL, " ",&next); /* Read the third Token = V*/
            vector.x = (float)atof(tokenPtr);
            tokenPtr = strtok_s(NULL, " ",&next); /* Read the third Token = V*/
            vector.z = (float)atof(tokenPtr);
            printf(tokenPtr);
        }
    }
 }