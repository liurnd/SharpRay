#pragma once
#include <Physical/BSDF/BSDF.h>
class PerfectSpecular :
	public BSDF
{
    ColorFloat BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector);
};

