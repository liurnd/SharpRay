#ifndef _SPHERE_H_
#define _SPHERE_H_
#include <Core/fmath.h>
#include <Entity/entity.h>
class Sphere :
	public Entity
{
private:
	point3D position;
	float radius;
public:
	float firstHit(const Ray*);
	vector3D normalAt(const point3D& pos);
	Sphere(point3D pos, float r) : position(pos), radius(r){ kEpsilon = 0.01f; }
	~Sphere();
};
#endif
