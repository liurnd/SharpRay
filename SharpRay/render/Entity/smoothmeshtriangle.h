#ifndef SMOOTHMESHTRIANGLE_H
#define SMOOTHMESHTRIANGLE_H
#include <Core/BaseDS.h>
#include <Entity\meshtriangle.h>

class SmoothMeshTriangle : public MeshTriangle
{
public:
    SmoothMeshTriangle();
    normal3D normalAt(const point3D& pos, const uint8_t deferData[]=nullptr) override;
};

#endif // SMOOTHMESHTRIANGLE_H
