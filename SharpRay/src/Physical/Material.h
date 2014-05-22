#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include <Core/Color.h>
#include <Core/BaseDS.h>
#include <Physical/BSDF/bsdf.h>
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
    Sampler* sampler;

    static RayLevelType traceLevelLimit;
    static RayLevelType numAreaLightSample;
    static RayLevelType numGlobalSample;

    Material();
    virtual void shade(Ray* r);
};
#include <Physical/mirror.h>
#endif
