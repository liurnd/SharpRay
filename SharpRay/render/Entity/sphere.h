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
    bool firstHit(const Ray* r, CoordFloat& t, uint8_t deferData[]=0);
    normal3D normalAt(const point3D& pos, const uint8_t deferData[]=0);
    bool map2texture(const point3D& point, point3D& texturePoint, const uint8_t deferData[]=0);
	Sphere(point3D pos, float r) : position(pos), radius(r){ kEpsilon = 0.01f; }
	~Sphere();
};
#endif
