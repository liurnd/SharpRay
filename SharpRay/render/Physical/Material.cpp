#include <Physical/Material.h>
#include <Core/world.h>
#include <Sampler/Sampler.h>
#include <Texture/texture.h>
#include <Physical/BSDF/bsdf.h>
#include <Util/config.h>

RColor Material::calcGlobalIllu(Ray* r)
{
	ShadeInfo &si = r->shadeInfo;
	Sampler* sampler = r->sampler;
	World* currentWorld = r->currentWorld;
	Config* config = currentWorld->globalConfig;

	RColor tmpLo;

	sampler->shuffleIndex(config->numPathTraceSample + 1);
	if ((*sampler)[config->numPathTraceSample].x < ka)		//Stop recursive tracing in probability of ka
		if (r->rayLevel < config->traceLevelLimit && ka > 0){
			RColor tmpC(0);
			for (int i = 0; i < config->numPathTraceSample; i++)
			{
				normal3D sampleOut;
				ColorFloat pdf;
				ColorFloat f = bsdf->sample_BRDF((*sampler)[i], si, r->direction, sampleOut, pdf);
				Ray *refRay = new Ray(si.hitPoint, sampleOut, r);
				if (refRay->trace())
				{
					refRay->shadeInfo.firstHitEntity->material->shade(refRay);
					ColorFloat cosin = dot(sampleOut, si.hitNormal);
					tmpC += refRay->shadeInfo.Lo * (f * cosin / pdf);
				}
				delete refRay;
			}

			tmpLo += tmpC / static_cast<float>(config->numPathTraceSample);
		}

	return tmpLo;
}

Material::Material()
{
    texture = nullptr;
}


RColor Material::calcDirectLight(Ray* r)
{
	ShadeInfo &si = r->shadeInfo;
	World* currentWorld = r->currentWorld;
	RColor tmpLo;

	for (auto i = currentWorld->lightList.begin(); i != currentWorld->lightList.end(); i++)
	{
		RColor Li; vector3D lightVector;
		if ((*i)->Lo(r, Li, lightVector))
			tmpLo += Li*(kd * bsdf->BRDF(si, r->direction, lightVector))*(-dot(si.hitNormal, normalize(lightVector)));
	}

	return tmpLo;
}

RColor Material::calcAreaLight(Ray* r)
{
	ShadeInfo &si = r->shadeInfo;
	Sampler* sampler = r->sampler;
	World* currentWorld = r->currentWorld;
	Config* config = currentWorld->globalConfig;

	RColor tmpLo;
	for (auto light = currentWorld->areaLightList.begin(); light != currentWorld->areaLightList.end(); light++)
	{
		RColor Li; RColor thisLo;

		sampler->shuffleIndex(config->numAreaLightSample);
		for (int i = 0; i < config->numAreaLightSample; i++)
		{
			vector3D lightVector;   // From light sample point to hit point
			point3D samplePoint;
			ColorFloat pdf;
			if (!(*light)->CalcSample(r->shadeInfo.hitPoint, (*sampler)[i], samplePoint, Li, pdf))
				continue;
			lightVector = r->shadeInfo.hitPoint - samplePoint;
			normal3D nLightVector = normalize(lightVector);
			Ray shadowRay(samplePoint, nLightVector, r);
			shadowRay.shadeInfo.firstHitT = glm::length(lightVector);
			if (!shadowRay.hasHit())
			{
				float cosin = -dot(si.hitNormal, nLightVector);
				if (cosin<0)
					continue;
				float bf = bsdf->BRDF(si, r->direction, nLightVector);
				thisLo += Li*(kd * bf * cosin / pdf);
			}
		}
		tmpLo += (thisLo / static_cast<float>(config->numAreaLightSample));
	}

	return tmpLo;
}

void Material::shade(Ray* r)
{
    ShadeInfo &si = r->shadeInfo;
	si.Lo = RColor(0);

    si.hitPoint = r->origin + r->direction*si.firstHitT;
    si.hitNormal = si.firstHitEntity->normalAt(si.hitPoint,si.deferData);
	if (dot(si.hitNormal, r->direction) > 0)
		return;

	
	//Direct light
	si.Lo += calcDirectLight(r);

    //Area Light
	si.Lo += calcAreaLight(r);

    //Indirect light
	si.Lo += calcGlobalIllu(r);

    RColor tColor = color;

    if (texture!=nullptr)
    {
        point3D texturePoint;
        if (si.firstHitEntity->map2texture(r->shadeInfo.hitPoint,texturePoint,si.deferData))
            tColor = (*texture)(texturePoint);
    }

    si.Lo = si.Lo * tColor;
}
