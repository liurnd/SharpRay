#include <Physical/Material.h>
#include <Core/world.h>
#include <Sampler/Sampler.h>
#include <Physical/BSDF.h>

RayLevelType Material::numAreaLightSample = 1024;
RayLevelType Material::traceLevelLimit = 4;

void Material::shade(Ray* r)
{
    ShadeInfo &si = r->shadeInfo;

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
        sampler->type = square;
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
    /*normal3D mainDirection = r->direction + si.hitNormal* (dot(si.hitNormal,r->direction)*2);
    coordSystem cs(mainDirection);
    if (r->rayLevel < traceLevelLimit && ka > 0)
    {
        assert(sampler->type==hemisphere);

        sampler->shuffleIndex(numSample);
        for (int i = 0; i < numSample; i++)
        {
            normal3D refDirection = cs(sampler->sampleList[i]); //Reflect ray direction
            if (dot(refDirection,si.hitNormal)<0)
                continue;
            Ray *refRay = new Ray(si.firstHitPoint,refDirection,r);
            if (refRay->trace())
            {
                refRay->shadeInfo.firstHitEntity->material->shade(refRay);
                CoordFloat cos = dot(refDirection,mainDirection)/(refDirection.length()*mainDirection.length());
                si.Lo += refRay->shadeInfo.Lo * pow(cos,bsdf->getE());
            }
            delete refRay;
        }
	}
	*/
	//Lambertian


    si.Lo = si.Lo * color;
}
