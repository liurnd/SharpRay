#include <Physical/Material.h>
#include <Core/world.h>
#include <Sampler/Sampler.h>
#include <Texture/texture.h>
#include <Physical/BSDF/bsdf.h>

RayLevelType Material::numAreaLightSample = 4;
RayLevelType Material::numGlobalSample = 2;
RayLevelType Material::traceLevelLimit = 4;

Material::Material()
{
    texture = NULL;
}

void Material::shade(Ray* r)
{
    ShadeInfo &si = r->shadeInfo;
    Sampler* sampler = r->sampler;
    World* currentWorld = r->currentWorld;

    si.hitPoint = r->origin + r->direction*si.firstHitT;
    si.hitNormal = si.firstHitEntity->normalAt(si.hitPoint);

	si.Lo = RColor(0);
	//Direct light
    for (auto i = currentWorld->lightList.begin(); i != currentWorld->lightList.end(); i++)
	{
		RColor Li; vector3D lightVector;
        if ((*i)->Lo(r, Li, lightVector))
            si.Lo += Li*(kd * bsdf->BRDF(si, r->direction, lightVector))*(-dot(si.hitNormal,normalize(lightVector)));
	}

    //Area Light
    for (auto light = currentWorld->areaLightList.begin();light != currentWorld->areaLightList.end();light++)
    {
        RColor Li; RColor tmpLo;

        sampler->shuffleIndex(numAreaLightSample);
        for (int i = 0; i < numAreaLightSample; i++)
        {
            vector3D lightVector;   // From light sample point to hit point
            point3D samplePoint;
            ColorFloat pdf;
            if (!(*light)->CalcSample(r->shadeInfo.hitPoint, (*sampler)[i], samplePoint, Li,pdf))
                    continue;
            lightVector = r->shadeInfo.hitPoint - samplePoint;
            normal3D nLightVector = normalize(lightVector);
            Ray shadowRay(samplePoint,nLightVector,r);
            shadowRay.shadeInfo.firstHitT = glm::length(lightVector);
            if (!shadowRay.hasHit())
            {
                float cosin = -dot(si.hitNormal,nLightVector);
                if (cosin<0)
                    continue;
                float bf = bsdf->BRDF(si, r->direction, nLightVector);
                tmpLo += Li*(kd * bf * cosin / pdf);
                assert(tmpLo.r >=0);
            }
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
            Ray *refRay = new Ray(si.hitPoint,sampleOut,r);
            if (refRay->trace())
            {
                refRay->shadeInfo.firstHitEntity->material->shade(refRay);
                ColorFloat cosin = dot(sampleOut, si.hitNormal);
                tmpC += refRay->shadeInfo.Lo * (ka * f * cosin/ pdf);
                assert(tmpC.r >= 0);
            }

            delete refRay;
        }

        si.Lo += (tmpC / static_cast<float>(numGlobalSample));
    }
    RColor tColor = color;

    if (texture!=NULL)
    {
        point3D texturePoint;
        if (r->shadeInfo.firstHitEntity->map2texture(r->shadeInfo.hitPoint,texturePoint))
            tColor = (*texture)(texturePoint);
    }

    assert(si.Lo.r >= 0);
    si.Lo = si.Lo * tColor;
}
