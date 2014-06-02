#include "lambertian.h"
#include <Core/ray.h>
#include <Sampler/Sampler.h>
ColorFloat Lambertian::BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector)
{
    return 1.f/3.14f/4.f;
}

ColorFloat Lambertian::sample_BRDF(const normal3D &sampleIn, const ShadeInfo &si, const vector3D &wo, normal3D &sampleOut, float &pdf)
{
    CoordSystem cs(si.hitNormal,wo);
    sampleOut = cs(Sampler::mapToHemiSphere(sampleIn, 0));
    pdf = 1.f/3.14f/4.f;
    return 1.f/3.14f/4.f;
}
