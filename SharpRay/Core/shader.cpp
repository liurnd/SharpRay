#include <Core/film.h>
#include <Core/world.h>
#include <Entity/entity.h>
#include <Core/Color.h>
#include <Core/shader.h>

void Shader::shade(Ray* r, const World* world)
{
	ShadeInfo &si = r->shadeInfo;
	if (!isfinite(si.firstHitT))
		return;

	si.firstHitPoint = r->origin + r->direction*si.firstHitT;
	si.hitNormal = si.firstHitEntity->normalAt(si.firstHitPoint);
	
	for (auto i = world->lightList.begin(); i != world->lightList.end(); i++)
	{
		RColor Li; float cosLn;
		if ((*i)->Li(r, Li, cosLn))
		{
			si.Lo += si.firstHitEntity->material->Lo(&(r->shadeInfo), cosLn, Li*cosLn);
		}
	}
}

void Shader::exposure(const World* world)
{
	while (!rayQueue.rayList.empty())
	{
		auto ray = rayQueue.getRay();
		ray->trace();
		shade(ray, world);
		ray->parent.orgPixel->color = ray->shadeInfo.Lo;
	}
}



Shader::Shader()
{
}


Shader::~Shader()
{
}