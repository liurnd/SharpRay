#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <Core/fmath.h>
#include <Core/film.h>
#include <Physical/Material.h>
class Ray;

class Entity
{
public:
	float kEpsilon;
	Material* material;
	Entity() :kEpsilon(0.0001f){}
	
	//Return the normal vector at the giving position.
	virtual vector3D normalAt(const point3D& pos) = 0;

	//Return t, where t*r->direction+r->origin is the first point the ray can hit;
	//t should be in [0, INFINITY) , if t == INFINITY (!isfinit(t)) means this
	//ray would not hit the surface.
	virtual float firstHit(const Ray*)=0;	
	virtual ~Entity();
};

#include "sphere.h"
#include "Plane.h"
#endif