#ifndef _RAY_H_
#define _RAY_H_


#include <Core/fmath.h>
#include <Core/Color.h>
class Film;
struct Pixel;
class Entity;
class World;

struct ShadeInfo
{
	float transferFactor;
	float firstHitT;
	point3D firstHitPoint;
	vector3D hitNormal;
	Entity* firstHitEntity;
	RColor Lo;
};

struct Ray
{
	point3D origin;
	vector3D direction;
	World* world;
	Film* currentFilm;
	union{
		Pixel* orgPixel;
		Ray* orgRay;
	}parent;
	ShadeInfo shadeInfo;
	
	bool hasHit() const;
	void trace();

	Ray(const point3D& o, const vector3D& d, Film* cf, Pixel* p, World* w) :origin(o), direction(normalize(d)),world(w), currentFilm(cf){ 
		parent.orgPixel = p;
	}
	Ray(const point3D& o, const vector3D& d, Film* cf, Ray* p, World* w) :origin(o), direction(normalize(d)), world(w), currentFilm(cf){ 
		parent.orgRay = p;
	}
	Ray(const point3D& o, const vector3D& d, World* w) :origin(o), direction(normalize(d)), world(w){ }
};
#endif