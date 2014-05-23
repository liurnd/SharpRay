#ifndef BALLLIGHT_H
#define BALLLIGHT_H
#include <Light/arealight.h>
#include <Sampler/Sampler.h>
#include <Core/BaseDS.h>
class BallLight : public AreaLight
{
private:
    point3D position;
    CoordFloat radius;


    Sampler* sampler;
    int numSample;
public:
    RColor color;
    ColorFloat ls;
    BallLight(const point3D& pos, const CoordFloat radius);
    bool CalcSample(const point3D& targetSample, const normal3D& squareSample, point3D& samplePoint, RColor& Li,float& pdf);
    bool CalcRad(Ray *ray, RColor &colorOut);
};

#endif // BALLLIGHT_H
