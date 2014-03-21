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
	bool isMajor;
	union{
		Pixel* orgPixel;
		Ray* orgRay;
	}parent;
	ShadeInfo* shadeInfo;
	
	void trace();

	Ray(const point3D& o,const vector3D& d, Film* cf, Pixel* p) :origin(o), direction(normalize(d)), currentFilm(cf){ parent.orgPixel = p; isMajor = true; }
	Ray(const point3D& o,const vector3D& d, Film* cf, Ray* p) :origin(o), direction(normalize(d)), currentFilm(cf){ parent.orgRay = p; isMajor = false; }
	Ray(const point3D& o, const vector3D& d) :origin(o), direction(normalize(d)){ isMajor = false; }
	~Ray();
};
#endif