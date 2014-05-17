#pragma once
#include "entity.h"
class Plane :
	public Entity
{
	normal3D normal;
	point3D position;
public:
    Plane(const normal3D& n, const point3D& p) :normal(n), position(p){}
	normal3D normalAt(const point3D& pos){ return normal; }
    bool firstHit(const Ray*, CoordFloat& t);
};

