#include <Physical/Material.h>
#include <Core/world.h>
#include <Sampler/Sampler.h>

#include <Physical/BSDF/bsdf.h>

RayLevelType Material::numAreaLightSample = 256;
RayLevelType Material::numGlobalSample = 12;
RayLevelType Material::traceLevelLimit = 4;

Material::Material()
{
}

void Material::shade(Ray* r)
{
    ShadeInfo &si = r->shadeInfo;
    Sampler* sampler = r->sampler;

	si.firstHitPoint = r->origin + r->direction*si.firstHitT;
	si.hitNormal = si.firstHitEntity->normalAt(si.firstHitPoint);

	si.Lo = RColor(0);
	//Direct light
	for (auto i = World::currentWorld->lightList.begin(); i != World::currentWorld->lightList.end(); i++)
	{
		RColor Li; vector3D lightVector;
        if ((*i)->Lo(r, Li, lightVector))
            si.Lo += Li*(kd * bsdf->BRDF(si, r->direction, lightVector))*(-dot(si.hitNormal,normalize(lightVector)));
	}

    //Area Light
    for (auto light = World::currentWorld->areaLightList.begin();light != World::currentWorld->areaLightList.end();light++)
    {
        RColor Li; RColor tmpLo;
        vector3D lightVector;// From light sample point to hit point
        sampler->shuffleIndex(numAreaLightSample);
        for (int i = 0; i < numAreaLightSample; i++)
        {
            point3D samplePoint;
            ColorFloat pdf;
            if (!(*light)->CalcSample(r->shadeInfo.firstHitPoint, (*sampler)[i], samplePoint, Li,pdf))
                    continue;
            lightVector = r->shadeInfo.firstHitPoint - samplePoint;
            CoordFloat distance = glm::length(lightVector);
            Ray shadowRay(samplePoint,lightVector/distance);
            shadowRay.shadeInfo.firstHitT = distance;
            if (!shadowRay.hasHit())
                tmpLo += Li*((kd * bsdf->BRDF(si, r->direction, lightVector))*(-dot(si.hitNormal,lightVector)/distance)/ pdf);
        }
        si.Lo += (tmpLo/static_cast<float>(numAreaLightSample));
    }

    //Indirect light


    sampler->shuffleIndex(numGlobalSample+1);
    if ((*sampler)[numGlobalSample].x < ka && r->rayLevel < traceLevelLimit && ka > 0)
    {
        RColor tmpC(0);
        for (int i = 0; i < numGlobalSample; i++)
        {
            normal3D sampleOut;ColorFloat pdf;
            ColorFloat f = bsdf->sample_BRDF((*sampler)[i],si,r->direction,sampleOut,pdf);
            Ray *refRay = new Ray(si.firstHitPoint,sampleOut,r);
            if (refRay->trace())
            {
                refRay->shadeInfo.firstHitEntity->material->shade(refRay);
                ColorFloat cosin = dot(sampleOut, si.hitNormal);
                tmpC += refRay->shadeInfo.Lo * (ka * f * cosin/ pdf);
            }

            delete refRay;
        }

        si.Lo += (tmpC / static_cast<float>(numGlobalSample));
    }
	//Lambertian
    si.Lo = si.Lo * color;
}
