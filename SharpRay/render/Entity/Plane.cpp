#include "Plane.h"
#include <Core/ray.h>

bool Plane::firstHit(const Ray* r, CoordFloat& t, uint8_t deferData[])
{
    t = (dot(position - r->origin, normal) / dot(r->direction, normal));
    return true;
}
