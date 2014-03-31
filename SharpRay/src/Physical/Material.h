#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include <Core/Color.h>
#include <Physical/BSDF.h>
struct Ray;
struct ShadeInfo;
class Material
{
public:
	float ka, kd;
	RColor cd;
	BSDF* bsdf;
	void shade(Ray* r);
};
#endif