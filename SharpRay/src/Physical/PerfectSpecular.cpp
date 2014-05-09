#include "PerfectSpecular.h"
#include <Core/ray.h>
float PerfectSpecular::BRDF(const ShadeInfo& si, const vector3D& cameraVector, const vector3D& lightVector)
{
    return 1.f/3.14f/4.f;
}
