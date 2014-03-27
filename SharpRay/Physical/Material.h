#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include <Core/Color.h>
struct Ray;
struct ShadeInfo;
class Material
{
public:
	float ka, kd;
	RColor cd;
	virtual RColor Lo(ShadeInfo* si, float cosLn, RColor Li)
	{
		return kd*Li / (4.0f * 3.14f);
	}
};
#endif