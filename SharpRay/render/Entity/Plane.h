#pragma once
#include "entity.h"
class Plane :
	public Entity
{
	normal3D normal;
	point3D position;
public:
    Plane(const normal3D& n, const point3D& p) :normal(n), position(p){}
    normal3D normalAt(const point3D& pos, const uint8_t deferData[]=0){ return normal; }
    bool firstHit(const Ray* r, CoordFloat& t, uint8_t deferData[]=0);
};

