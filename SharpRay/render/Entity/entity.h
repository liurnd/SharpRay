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
     * @param deferData
	 * @return The normal vector
	 */

    virtual normal3D normalAt(const point3D& pos, const uint8_t deferData[]=0) = 0;

    /**
     * @brief Calc t, where t*r->direction+r->origin is the first point the ray can hit. t should be in [0, INFINITY).
     * @param r Pointer to the ray you want to check
     * @param t [out] the calc result
     * @param deferData [in] a pointer to a buffer which would be passed to normalAt and map2texture. Typically it's used for speeding up the calc of those function.
     * @return
     */
    virtual bool firstHit(const Ray* r, CoordFloat& t, uint8_t deferData[]=0)=0;

    virtual bool map2texture(const point3D& point, point3D& texturePoint, const uint8_t deferData[]=0){return false;}
	virtual ~Entity();
};

#include "sphere.h"
#include "meshtriangle.h"
#include "Plane.h"
#endif
