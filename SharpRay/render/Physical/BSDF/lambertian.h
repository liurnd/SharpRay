#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "bsdf.h"
class Lambertian : public BSDF
{
public:
    ColorFloat sample_BRDF(const normal3D &sampleIn, const ShadeInfo &si, const vector3D &wo, normal3D &sampleOut, float &pdf);
    ColorFloat BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector);
};

#endif // LAMBERTIAN_H
