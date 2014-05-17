#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <Core/BaseDS.h>
#include <Core/film.h>
#include <Physical/Material.h>
struct Ray;

class Entity
{
public:
	float kEpsilon;
	Material* material;
	Entity() :kEpsilon(0.0001f){}
	
	/**
	 * @brief Return the normal vector at the giving position.
	 * 
	 * @param pos The position
	 * @return The normal vector
	 */

	virtual normal3D normalAt(const point3D& pos) = 0;

	/**
	 * @brief Return t, where t*r->direction+r->origin is the first point the ray can hit
	 * @details 	Return t, where t*r->direction+r->origin is the first point the ray can hit,
	 * t should be in [0, INFINITY).
	 * if t == INFINITY (in program should be checked by !isfinit(t)) means this ray would not hit the surface.
	 * 
	 * @param  Pointer to the ray you want to check
	 * @return t where t*r->direction+r->origin the first point the giving ray can hit;
	 */
    virtual bool firstHit(const Ray*, CoordFloat& t)=0;
	virtual ~Entity();
};

#include "sphere.h"
#include "Plane.h"
#endif
