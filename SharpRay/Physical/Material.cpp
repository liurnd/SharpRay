#include <Physical/Material.h>
#include <Core/world.h>
void Material::shade(Ray* r)
{
	ShadeInfo &si = r->shadeInfo;
	if (!isfinite(si.firstHitT))
		return;

	si.firstHitPoint = r->origin + r->direction*si.firstHitT;
	si.hitNormal = si.firstHitEntity->normalAt(si.firstHitPoint);

	si.Lo = RColor(0);
	//Direct light
	for (auto i = World::currentWorld->lightList.begin(); i != World::currentWorld->lightList.end(); i++)
	{
		RColor Li; vector3D lightAngle;

		if ((*i)->Lo(r, Li, lightAngle))	
		{
			//TODO:Non-linear BSDF support
			si.Lo += si.firstHitEntity->material->bsdf->BRDF(si, r->direction, lightAngle)*Li;
		}
	}
	//Mirror light

	//Lambertian
}