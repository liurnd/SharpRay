#pragma once
#include <Physical/BSDF.h>
class GlossySpecular : BSDF
{
public:
	virtual float BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector) = 0;
	virtual float BTDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector){ return 0; }
};

