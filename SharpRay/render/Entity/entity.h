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
     * @brief Calc t, where t*r->direction+r->origin is the first point the ray can hit. t should be in [0, INFINITY).
     * @param r Pointer to the ray you want to check
     * @param t [out] the calc result
     * @return
     */
    virtual bool firstHit(const Ray* r, CoordFloat& t)=0;

    virtual bool map2texture(const point3D& point, point3D& texturePoint){return false;}
	virtual ~Entity();
};

#include "sphere.h"
#include "meshtriangle.h"
#include "Plane.h"
#endif
