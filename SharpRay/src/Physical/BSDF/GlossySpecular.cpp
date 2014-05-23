#include "GlossySpecular.h"
#include <Core/fmath.h>
#include <Core/ray.h>
#include <Sampler/Sampler.h>
ColorFloat GlossySpecular::sample_BRDF(const normal3D& sampleIn,  const ShadeInfo& si, const vector3D& wo, normal3D& sampleOut, float& pdf)
{
    normal3D mainDirection = wo + si.hitNormal* (-dot(si.hitNormal,wo)*2);
    CoordSystem cs(mainDirection, si.hitNormal);
    normal3D sphereVector = Sampler::mapToHemiSphere(sampleIn, exp);
    sampleOut = cs(sphereVector); //Reflect ray direction
    if (dot(sampleOut,si.hitNormal)<0) //Wrap the directions below surface to upper area
    {
        sphereVector.x = -sphereVector.x;
        sphereVector.y = -sphereVector.y;
        sampleOut = cs(sphereVector);
    }
    assert(dot(sampleOut,si.hitNormal)>0);
    ColorFloat bsdf = pow(dot(sampleOut,mainDirection), exp);
    pdf = bsdf * dot(si.hitNormal,sampleOut);
    return bsdf;
}

ColorFloat GlossySpecular::BRDF(const ShadeInfo& si, const vector3D& wo, const vector3D& wi)
{
    return 1.f/3.14f/4.f;
}
