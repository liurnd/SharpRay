#ifndef _BSDF_H_
#define _BSDF_H_
#include <Core/BaseDS.h>
struct ShadeInfo;
class Sampler;
class BSDF
{
public:
    virtual float getE(){return -1;}
	virtual float BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector) = 0;
	virtual float BTDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector){ return 0; }
};
#endif
