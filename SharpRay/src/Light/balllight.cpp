#include "balllight.h"
#include <Core/ray.h>
#include <Sampler/Sampler.h>
BallLight::BallLight(const point3D &pos, const CoordFloat r)
    :position(pos),radius(r)
{
}

bool BallLight::CalcSample(const point3D& targetPoint, const normal3D& squareSample, point3D& samplePoint, RColor& Li,float& pdf)
{
    float sin_theta = sin(squareSample.x*2*pi);
    float cos_theta = cos(squareSample.x*2*pi);
    float sin_rho = sin(squareSample.y*2*pi);
    float cos_rho = cos(squareSample.y*2*pi);
    vector3D sampleVector(sin_theta, cos_theta * sin_rho, cos_theta * cos_rho);
    samplePoint = position + sampleVector*radius;
    vector3D lightVector = targetPoint - samplePoint;
    float cosN = dot(lightVector, sampleVector)/glm::length(lightVector);
    if (cosN < 0)
        return false;
    Li = color * (ls * cosN);
    pdf = 1/(radius*radius);
    return true;
}
