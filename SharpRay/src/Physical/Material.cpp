#include <Physical/Material.h>
#include <Core/world.h>
#include <Sampler/Sampler.h>
#include <Physical/BSDF.h>

RayLevelType Material::numSample = 8;
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
		{
			//TODO:Non-linear BSDF support
            si.Lo += Li*(kd * bsdf->BRDF(si, r->direction, lightVector))*(-dot(si.hitNormal,normalize(lightVector)));
		}
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
