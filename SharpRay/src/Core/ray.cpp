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

bool Ray::trace()
{
	shadeInfo.firstHitT = INFINITY;
    shadeInfo.firstHitEntity= NULL;
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

    if (shadeInfo.firstHitEntity == NULL)
        return false;

    vector3D t = direction * shadeInfo.firstHitT;
    shadeInfo.firstHitPoint = origin + t;
    return true;
}
