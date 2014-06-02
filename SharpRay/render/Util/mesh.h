#ifndef MESH_H
#define MESH_H
#include <Core/BaseDS.h>
#include <Core/fmath.h>
struct Mesh
{
public:
    point3D* vertices;
    normal3D* normals;
    float* texture_u;
    float* texture_v;

    int* face[3];

    int numVertices;
    int numFace;
};

#endif // MESH_H
