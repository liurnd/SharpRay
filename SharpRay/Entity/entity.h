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
	virtual vector3D normalAt(const point3D& pos) = 0;
	virtual float firstHit(const Ray*)=0;
	virtual ~Entity();
};

#include "sphere.h"
#endif