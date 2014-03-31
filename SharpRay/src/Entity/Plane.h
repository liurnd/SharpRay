#pragma once
#include "entity.h"
class Plane :
	public Entity
{
	vector3D normal;
	point3D position;
public:
	Plane(const vector3D& n, const point3D& p) :normal(n), position(p){};
	vector3D normalAt(const point3D& pos){ return normal; }
	float firstHit(const Ray* r);
};

