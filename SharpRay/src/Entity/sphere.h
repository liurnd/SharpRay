#ifndef _SPHERE_H_
#define _SPHERE_H_
#include <Core/BaseDS.h>
#include <Entity/entity.h>
class Sphere :
	public Entity
{
private:
	point3D position;
	float radius;
public:
    bool firstHit(const Ray*, CoordFloat& t);
	normal3D normalAt(const point3D& pos);
    bool map2texture(const point3D& point, point3D& texturePoint);
	Sphere(point3D pos, float r) : position(pos), radius(r){ kEpsilon = 0.01f; }
	~Sphere();
};
#endif
