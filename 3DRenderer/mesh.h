#pragma 

#include "vectors.h"
#include "triangle.h"

//#define N_CUBE_VERTICES 8
//#define N_CUBE_FACES (6 * 2) // 6 cube faces, 2 triangles per 

//extern vct3_t cubeVertices[N_CUBE_VERTICES];
//extern face_t cubeFaces[N_CUBE_FACES];

typedef struct {
	vct3_t* vertices;
	face_t* faces;
	vct3_t rotation;
} mesh_t;

extern mesh_t mesh;

void loadCubeMeshData(void);
void loadObjDatafromFile(char* filename);