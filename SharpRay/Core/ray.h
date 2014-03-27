#ifndef _RAY_H_
#define _RAY_H_


#include <Core/fmath.h>
class Film;
class Pixel;
class ShadeInfo;
struct Ray
{
	point3D origin;
	vector3D direction;
	Film* currentFilm;
	int rayLevel;
	union{
		Pixel* orgPixel;
		Ray* orgRay;
	}parent;
	ShadeInfo* shadeInfo;
	
	void trace();

	Ray(const point3D& o, const vector3D& d, Film* cf, Pixel* p) :origin(o), direction(normalize(d)), currentFilm(cf){ parent.orgPixel = p; rayLevel = 0; }
	Ray(const point3D& o, const vector3D& d, Film* cf, Ray* p) :origin(o), direction(normalize(d)), currentFilm(cf){ parent.orgRay = p; rayLevel = p->rayLevel+1; }
	Ray(const point3D& o, const vector3D& d) :origin(o), direction(normalize(d)){ rayLevel = -1; }
	~Ray();
};
#endif