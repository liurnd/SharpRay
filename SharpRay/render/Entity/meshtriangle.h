#ifndef MESHTRIANGLE_H
#define MESHTRIANGLE_H
#include <Core/fmath.h>
#include <Entity/entity.h>
struct Mesh;
class MeshTriangle : public Entity
{
    struct triangleParam{
        CoordFloat beta,gamma;
    };

public:
    Mesh* mesh;
    int vertexIdx[3];

    bool firstHit(const Ray* ray, CoordFloat& t);
    normal3D normalAt(const point3D& pos);
    bool map2texture(const point3D& point, point3D& texturePoint){return false;}
};

#endif // MESHTRIANGLE_H
