#include "mesh.h"
#include "array.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0,0,0},
    .scale = {1.0,1.0,1.0},
    .translation = {0,0,0}
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

/*
face_t cubeFaces[N_CUBE_FACES] = {
    // front
    {.a = 1, .b = 2, .c = 3, 0xFFFFFFFF},
    {.a = 1, .b = 3, .c = 4, 0xFFFFFFFF},
    // right
    {.a = 4, .b = 3, .c = 5, 0xFFFFFFFF },
    {.a = 4, .b = 5, .c = 6, 0xFFFFFFFF },
    // back
    {.a = 6, .b = 5, .c = 7, 0xFFFFFFFF },
    {.a = 6, .b = 7, .c = 8, 0xFFFFFFFF },
    // left
    {.a = 8, .b = 7, .c = 2, 0xFFFFFFFF },
    {.a = 8, .b = 2, .c = 1, 0xFFFFFFFF },
    // top
    {.a = 2, .b = 7, .c = 5, 0xFFFFFFFF },
    {.a = 2, .b = 5, .c = 3, 0xFFFFFFFF },
    // bottom
    {.a = 6, .b = 8, .c = 1, 0xFFFFFFFF },
    {.a = 6, .b = 1, .c = 4, 0xFFFFFFFF }
};
*/

/*face_t cubeFaces[N_CUBE_FACES] = {
    // front
    {.a = 1, .b = 2, .c = 3, 0xFFFF0000},
    {.a = 1, .b = 3, .c = 4, 0xFFFF0000},
    // right
    {.a = 4, .b = 3, .c = 5, 0xFF00FF00 },
    {.a = 4, .b = 5, .c = 6, 0xFF00FF00 },
    // back
    {.a = 6, .b = 5, .c = 7, 0xFF0000FF },
    {.a = 6, .b = 7, .c = 8, 0xFF0000FF },
    // left
    {.a = 8, .b = 7, .c = 2, 0xFFFFFF00 },
    {.a = 8, .b = 2, .c = 1, 0xFFFFFF00 },
    // top
    {.a = 2, .b = 7, .c = 5, 0xFF00FFFF },
    {.a = 2, .b = 5, .c = 3, 0xFF00FFFF },
    // bottom
    {.a = 6, .b = 8, .c = 1, 0xFFFF00FF },
    {.a = 6, .b = 1, .c = 4, 0xFFFF00FF }
};
*/

face_t cubeFaces[N_CUBE_FACES] = {
    // front
    {.a = 1, .b = 2, .c = 3, .a_uv = { 0, 0 }, .b_uv = { 0, 1 }, .c_uv = { 1, 1 }, .color = 0xFFFFFFFF },
    {.a = 1, .b = 3, .c = 4, .a_uv = { 0, 0 }, .b_uv = { 1, 1 }, .c_uv = { 1, 0 }, .color = 0xFFFFFFFF },
    // right
    {.a = 4, .b = 3, .c = 5, .a_uv = { 0, 0 }, .b_uv = { 0, 1 }, .c_uv = { 1, 1 }, .color = 0xFFFFFFFF },
    {.a = 4, .b = 5, .c = 6, .a_uv = { 0, 0 }, .b_uv = { 1, 1 }, .c_uv = { 1, 0 }, .color = 0xFFFFFFFF },
    // back
    {.a = 6, .b = 5, .c = 7, .a_uv = { 0, 0 }, .b_uv = { 0, 1 }, .c_uv = { 1, 1 }, .color = 0xFFFFFFFF },
    {.a = 6, .b = 7, .c = 8, .a_uv = { 0, 0 }, .b_uv = { 1, 1 }, .c_uv = { 1, 0 }, .color = 0xFFFFFFFF },
    // left
    {.a = 8, .b = 7, .c = 2, .a_uv = { 0, 0 }, .b_uv = { 0, 1 }, .c_uv = { 1, 1 }, .color = 0xFFFFFFFF },
    {.a = 8, .b = 2, .c = 1, .a_uv = { 0, 0 }, .b_uv = { 1, 1 }, .c_uv = { 1, 0 }, .color = 0xFFFFFFFF },
    // top
    {.a = 2, .b = 7, .c = 5, .a_uv = { 0, 0 }, .b_uv = { 0, 1 }, .c_uv = { 1, 1 }, .color = 0xFFFFFFFF },
    {.a = 2, .b = 5, .c = 3, .a_uv = { 0, 0 }, .b_uv = { 1, 1 }, .c_uv = { 1, 0 }, .color = 0xFFFFFFFF },
    // bottom
    {.a = 6, .b = 8, .c = 1, .a_uv = { 0, 0 }, .b_uv = { 0, 1 }, .c_uv = { 1, 1 }, .color = 0xFFFFFFFF },
    {.a = 6, .b = 1, .c = 4, .a_uv = { 0, 0 }, .b_uv = { 1, 1 }, .c_uv = { 1, 0 }, .color = 0xFFFFFFFF }
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
        
        if (strncmp(objString,"v ",2) ==0)
        {
            vct3_t vector = {0,0,0};
            /* Process a vector (v -1.000000 -1.000000 1.000000) */
            sscanf_s(objString, "v %f %f %f", &vector.x, &vector.y, &vector.z);
            array_push(mesh.vertices, vector);
            printf("V = %f,%f,%f\n\r", vector.x, vector.y, vector.z);
        }

        if (strncmp(objString, "f ", 2)==0)
        {
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];
            sscanf_s(objString, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                &vertex_indices[2], &texture_indices[2], &normal_indices[2]
            );
            face_t face = {
                .a = vertex_indices[0],
                .b = vertex_indices[1],
                .c = vertex_indices[2],
                .color = 0xFFFFFFFF
            };
            array_push(mesh.faces, face);
            printf("F = %i,%i,%i\n\r", face.a, face.b, face.c);
        }


    }  
    printf("Vertice Count : %d\n\r", array_length(mesh.vertices));
    printf("Face Count    : %d\n\r", array_length(mesh.faces));

 }