#pragma once
#include <Physical/BSDF/bsdf.h>
class GlossySpecular : public BSDF
{
public:
    ColorFloat exp;
    ColorFloat sample_BRDF(const normal3D& sampleIn,  const ShadeInfo& si, const vector3D& wo, normal3D& sampleOut, float& pdf);
    ColorFloat BRDF(const ShadeInfo& si, const vector3D& wo, const vector3D& wi);
};
