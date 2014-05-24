#ifndef _RAY_H_
#define _RAY_H_

#include <Core/BaseDS.h>
#include <Core/Color.h>
class Film;
struct Pixel;
class Entity;
class World;
class Sampler;

struct ShadeInfo
{
	float transferFactor;
	float firstHitT;
    point3D hitPoint;
	normal3D hitNormal;
	Entity* firstHitEntity;
	RColor Lo;
};

struct Ray
{
	point3D origin;
	normal3D direction;
    Film* currentFilm;
    World* currentWorld;
	union{
		Pixel* orgPixel;
		Ray* orgRay;
	}parent;

    RayLevelType rayLevel;
    Sampler* sampler;

	ShadeInfo shadeInfo;
	
	/**
	 * @brief Return whether this ray will hit any entity before hit a giving point.
	 * @details Ray may hit the entity which the giving point belong to.
	 * shadeInfo.firstHitT should be set to specify the point origin + direction * shadeInfo.firstHitT 
	 * This function are often used to check whether a point is in the shadow of other object
	 * @return True if this ray hit an entity before hit the giving point.
	 */
	bool hasHit() const;

	/**
	 * @brief Trace this ray
	 * @details
	 *  1. Find the nearest surface the ray may hit in the world
	 *  2. Calculate and set shadeInfo
     * @return Whether this ray hit something
	 */
    bool trace();


    Ray(const point3D& o, const normal3D& d, Film* cf, Pixel* p) :
        origin(o),
        direction(d),
        currentFilm(cf){
		parent.orgPixel = p;
		rayLevel = 0;
	}
    Ray(const point3D& o, const normal3D& d, Ray* p) :
        origin(o),
        direction(d),currentWorld(p->currentWorld),
        currentFilm(p->currentFilm){
        sampler = p->sampler;
		parent.orgRay = p;
        rayLevel = p->rayLevel + 1;
    }
};
#endif
