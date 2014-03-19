#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include <Core/Color.h>
class Ray;
class ShadeInfo;
class Material
{
public:
	float ka, kd;
	RColor cd;
	virtual RColor Lo(ShadeInfo* si, vector3D lightDirection, RColor Li)
	{
		return kd*Li / (4.0f * 3.14f);
	}
};
#endif