#include "Plane.h"
#include <Core/ray.h>

float Plane::firstHit(const Ray* r)
{
	float x = (dot(position - r->origin, normal) / dot(r->direction, normal));
	if (x < 0)
		return INFINITY;
	return x;
}