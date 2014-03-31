#pragma once
#include <Physical/BSDF.h>
class PerfectSpecular :
	public BSDF
{
	float BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector);
};

