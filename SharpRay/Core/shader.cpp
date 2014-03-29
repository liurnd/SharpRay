#include <Core/film.h>
#include <Entity/entity.h>
#include <Core/Color.h>
#include <Core/shader.h>
#include <Core/ray.h>
#include <Core/world.h>

void Shader::shade(Ray* r)
{
	ShadeInfo &si = r->shadeInfo;
	if (!isfinite(si.firstHitT))
		return;

	si.firstHitPoint = r->origin + r->direction*si.firstHitT;
	si.hitNormal = si.firstHitEntity->normalAt(si.firstHitPoint);
	
	for (auto i = World::currentWorld->lightList.begin(); i != World::currentWorld->lightList.end(); i++)
	{
		RColor Li; float cosLn;
		if ((*i)->Li(r, Li, cosLn))
		{
			si.Lo += si.firstHitEntity->material->Lo(&(r->shadeInfo), cosLn, Li*cosLn);
		}
	}
}

void Shader::exposure()
{
	while (!rayQueue.rayList.empty())
	{
		auto ray = rayQueue.getRay();
		ray->trace();
		shade(ray);
		ray->parent.orgPixel->color = ray->shadeInfo.Lo;
	}
}



Shader::Shader()
{
}


Shader::~Shader()
{
}