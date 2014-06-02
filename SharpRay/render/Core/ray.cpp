#include "ray.h"
#include <Core/world.h>
#include <Core/BaseDS.h>

bool Ray::hasHit() const
{
    for (auto i = currentWorld->entityList.begin(); i != currentWorld->entityList.end(); i++)
	{
        CoordFloat t;
        if (!(*i)->firstHit(this,t))
			continue;
		if (t < shadeInfo.firstHitT- (*i)->kEpsilon)
			return true;
	}
	return false;
}

bool Ray::trace()
{
    shadeInfo.firstHitEntity= NULL;
    for (auto i = currentWorld->entityList.begin(); i != currentWorld->entityList.end(); i++)
    {
        CoordFloat t;
        if (!(*i)->firstHit(this,t))
            continue;
        if (shadeInfo.firstHitEntity==NULL || t < shadeInfo.firstHitT)
		{
			if (t < (*i)->kEpsilon)
				continue;
			shadeInfo.firstHitT = t;
            shadeInfo.firstHitEntity = *i;
		}
	}

    if (shadeInfo.firstHitEntity == NULL)
        return false;

    return true;
}
