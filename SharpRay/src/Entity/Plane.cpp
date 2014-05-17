#include "Plane.h"
#include <Core/ray.h>

bool Plane::firstHit(const Ray* r, CoordFloat& t)
{
    t = (dot(position - r->origin, normal) / dot(r->direction, normal));
    if (t < 0)
        return false;
    return true;
}
