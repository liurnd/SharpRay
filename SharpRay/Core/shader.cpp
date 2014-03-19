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
		if ((*i)->isInShadow(si))
			continue;
		vector3D lightDirection = (*i)->getDirection(si);
		float cosLN = dot(lightDirection, si->hitNormal);
		if (cosLN< 0)
			continue;
		si->Lo += si->firstHitEntity->material->Lo(si, lightDirection, (*i)->Li(si, lightDirection)*cosLN);
	}

	si->Lo += RColor(0.5);
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
		shade(ray,world);
		if (ray->isMajor)
			ray->parent.orgPixel->color = si.Lo;
	}
}

bool Shader::castShadowRay(Ray* r, const World* w)
{
	ShadeInfo *si = r->shadeInfo;
	for (auto i = w->entityList.begin(); i != w->entityList.end(); i++)
	{
		float t = (*i)->firstHit(r);
		if (!isfinite(t))
			continue;
		if (t < si->firstHitT)
		{
			if (t < (*i)->kEpsilon)
				continue;
			r->shadeInfo->firstHitT = t;
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