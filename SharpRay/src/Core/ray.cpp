#include "ray.h"
#include <Core/world.h>

bool Ray::hasHit() const
{
	for (auto i = World::currentWorld->entityList.begin(); i != World::currentWorld->entityList.end(); i++)
	{
		float t = (*i)->firstHit(this);
		if (!std::isfinite(t))
			continue;
		if (t < shadeInfo.firstHitT- (*i)->kEpsilon)
			return true;
	}
	return false;
}

void Ray::trace()
{
	shadeInfo.firstHitT = INFINITY;
	for (auto i = World::currentWorld->entityList.begin(); i != World::currentWorld->entityList.end(); i++)
	{
		float t = (*i)->firstHit(this);
		if (!std::isfinite(t))
			continue;
		if (t < shadeInfo.firstHitT)
		{
			if (t < (*i)->kEpsilon)
				continue;
			shadeInfo.firstHitT = t;
			shadeInfo.firstHitEntity = *i;
		}
	}

	shadeInfo.firstHitPoint = origin + direction*shadeInfo.firstHitT;
}
