#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_
#include <Core/Color.h>
#include <Light/Light.h>

class spotLight:public Light
{
public:
	float ls;
	RColor color;
	vector3D position;
	spotLight();
	vector3D getDirection(ShadeInfo*) ;
	bool isInShadow(ShadeInfo*) const ;
	RColor Li(ShadeInfo*, const vector3D& lightDirection) const;
	~spotLight();
};
#endif