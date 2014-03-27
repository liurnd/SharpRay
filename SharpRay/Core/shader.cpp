#include <Core/film.h>
#include <Core/world.h>
#include <Entity/entity.h>
#include <Core/Color.h>
#include <Core/shader.h>

void Shader::shade(const Ray* r, const World* world)
{
	ShadeInfo *si = r->shadeInfo;
	if (!isfinite(si->firstHitT))
		return;

	si->firstHitPoint = r->origin + r->direction*si->firstHitT;
	si->hitNormal = si->firstHitEntity->normalAt(si->firstHitPoint);
	for (auto i = world->lightList.begin(); i != world->lightList.end(); i++)
	{
		RColor Li; float cosLn;
		if ((*i)->Li(this, si, Li, cosLn))
		{
			si->Lo += si->firstHitEntity->material->Lo(si, cosLn, Li*cosLn);
		}
	}
}

void Shader::exposure(const World* world)
{
	ShadeInfo si;
	si.world = world;
	while (!rayQueue.rayList.empty())
	{
		auto ray = rayQueue.getRay();
		ray->shadeInfo = &si;
		si.Lo= RColor(0);
		castRay(ray, world);
		shade(ray, world);
		if (ray->rayLevel == 0)
			ray->parent.orgPixel->color = si.Lo;

	}
}

bool Shader::castShadowRay(Ray* r, const World* w) const
{
	ShadeInfo *si = r->shadeInfo;
	for (auto i = w->entityList.begin(); i != w->entityList.end(); i++)
	{
		float t = (*i)->firstHit(r);
		if (!isfinite(t))
			continue;
		if (t < si->firstHitT - (*i)->kEpsilon)
		{
			si->firstHitT = t;
			si->firstHitEntity = *i;
			si->firstHitPoint = r->origin + r->direction*si->firstHitT;
			return true;
		}
	}
	return false;
}

void Shader::castRay(Ray* r, const World* w)
{
	ShadeInfo *si = r->shadeInfo;
	si->firstHitT = INFINITY;
	for (auto i = w->entityList.begin(); i != w->entityList.end(); i++)
	{
		float t = (*i)->firstHit(r);
		if (!isfinite(t))
			continue;
		if (t < si->firstHitT)
		{
			if (t < (*i)->kEpsilon)
				continue;
			si->firstHitT = t;
			si->firstHitEntity = *i;
		}
	}
}

Shader::Shader()
{
}


Shader::~Shader()
{
}