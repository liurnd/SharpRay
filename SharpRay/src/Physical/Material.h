#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include <Core/Color.h>
#include <Core/BaseDS.h>
struct Ray;
struct ShadeInfo;
class BSDF;
class Sampler;
class Material
{
public:
	float ka, kd;
    RColor color;
	BSDF* bsdf;
    Sampler* sampler;   //Must be convert to hemisphere before put here

    static RayLevelType traceLevelLimit;
    static RayLevelType numSample;

    virtual void shade(Ray* r);
};
#include <Physical/mirror.h>
#endif
