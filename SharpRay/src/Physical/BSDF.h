#ifndef _BSDF_H_
#define _BSDF_H_
#include <Core/fmath.h>
struct ShadeInfo;
class Sampler;
class BSDF
{
public:
	virtual float BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector) = 0;
	virtual float BTDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector){ return 0; }
};
#endif