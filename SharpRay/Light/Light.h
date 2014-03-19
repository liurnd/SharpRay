#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <Core/fmath.h>
#include <Core/Color.h>
class ShadeInfo;
class Entity;
class Ray;
class Light
{
public:
	virtual vector3D getDirection(ShadeInfo*)=0;
	virtual bool isInShadow(ShadeInfo*) const=0;
	virtual RColor Li(ShadeInfo*,const vector3D& lightDirection) const = 0;
	Light();
	~Light();
};

#include <Light/spotLight.h>
#endif