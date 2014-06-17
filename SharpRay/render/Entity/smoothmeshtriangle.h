#ifndef SMOOTHMESHTRIANGLE_H
#define SMOOTHMESHTRIANGLE_H
#include <Core/BaseDS.h>
class smoothMeshTriangle : public meshTriangle
{
public:
    smoothMeshTriangle();
    normal3D normalAt(const point3D& pos, const uint8_t deferData[]=0);
};

#endif // SMOOTHMESHTRIANGLE_H
