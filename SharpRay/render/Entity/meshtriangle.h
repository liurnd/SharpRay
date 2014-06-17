#ifndef MESHTRIANGLE_H
#define MESHTRIANGLE_H
#include <Core/fmath.h>
#include <Entity/entity.h>
struct Mesh;
struct Triangle;
class MeshTriangle : public Entity
{
protected:
    struct triangleParam{
        CoordFloat beta,gamma;
    };

public:
    Triangle* triangle;

    bool firstHit(const Ray* r, CoordFloat& t, uint8_t deferData[]=0);
    normal3D normalAt(const point3D& pos, const uint8_t deferData[]=0);
    bool map2texture(const point3D& point, point3D& texturePoint, const uint8_t deferData[]=0){return false;}
};

#endif // MESHTRIANGLE_H
