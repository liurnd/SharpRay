#include "balllight.h"
#include <Core/ray.h>
#include <Sampler/Sampler.h>
BallLight::BallLight(const point3D &pos, const CoordFloat r)
    :position(pos),radius(r)
{
}

bool BallLight::CalcRad(Ray *r, RColor &colorOut)
{
    point3D nPos = position - r->origin;
    float b = -2*dot(r->direction, nPos);
    float a = dot(r->direction, r->direction);
    float c = dot(nPos, nPos)-radius*radius;
    float b2ac = b*b - 4 * a*c;
    if (b2ac < 0.0f)
        return false;
    float t = (-b - sqrt(b2ac)) / (2 * a);
    if (t <= 0.0f)
    {
        t = (-b + sqrt(b2ac)) / (2 * a);
        if (t <= 0.0f)
            return false;
    }
    r->shadeInfo.firstHitT = t;
    point3D lightPoint = r->origin + r->direction*t;
    normal3D pointNormal = lightPoint - position;
    colorOut = color* (ls * -dot(pointNormal, r->direction));
    return true;
}

bool BallLight::CalcSample(const point3D& targetPoint, const normal3D& squareSample, point3D& samplePoint, RColor& Li,float& pdf)
{
    float sin_theta = sin(squareSample.x*2*pi);
    float cos_theta = cos(squareSample.x*2*pi);
    float sin_rho = sin(squareSample.y*2*pi);
    float cos_rho = cos(squareSample.y*2*pi);
    vector3D sampleVector(sin_theta * cos_rho, sin_theta * sin_rho,cos_theta);
    samplePoint = position + sampleVector*radius;
    vector3D lightVector = targetPoint - samplePoint;
    float cosN = dot(lightVector, sampleVector)/glm::length(lightVector);
    if (cosN < 0)
        return false;
    Li = color * (ls * cosN);
    pdf = 1/(radius*radius);
    return true;
}
