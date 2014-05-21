#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "bsdf.h"
class Lambertian : public BSDF
{
public:
    float BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector);
};

#endif // LAMBERTIAN_H
