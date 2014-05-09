#include <Entity/sphere.h>
#include <Core/ray.h>
#include <Core/BaseDS.h>

Sphere::~Sphere()
{
}

normal3D Sphere::normalAt(const point3D& pos)
{
    return normalize(pos - position);
}

float Sphere::firstHit(const Ray* r)
{
	point3D nPos = position - r->origin;
	float b = -2*dot(r->direction, nPos);
	float a = dot(r->direction, r->direction);
	float c = dot(nPos, nPos)-radius*radius;
	float b2ac = b*b - 4 * a*c;
	if (b2ac < 0.0f)
		return INFINITY;
	float root1 = (-b - sqrt(b2ac)) / (2 * a);
	if (root1 > 0.0f)
		return root1;
	root1 = (-b + sqrt(b2ac)) / (2 * a);
	if (root1 > 0.0f)
		return root1;
	return INFINITY;
}
