#ifndef MESH_H
#define MESH_H
#include <Core/BaseDS.h>
#include <Core/fmath.h>

class Material;
class World;
struct Triangle{
    point3D vertex[3];
    point3D texturePos[3];
    normal3D normal[3];
};

struct Mesh
{
public:
    Material* material;
    Triangle* triMesh;

    int numTriangle;
    void addToWorld(World* world);
};
#endif // MESH_H
