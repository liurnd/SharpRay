#include "mirror.h"
#include <Core/BaseDS.h>
#include <Core/ray.h>
#include <Entity/entity.h>
Mirror::Mirror()
{
}

void Mirror::shade(Ray *r)
{
    ShadeInfo& si = r->shadeInfo;
	si.firstHitPoint = r->origin + r->direction*si.firstHitT;
	si.hitNormal = si.firstHitEntity->normalAt(si.firstHitPoint);
    si.Lo = RColor(0);
    if (r->rayLevel>traceLevelLimit)
        return;
    normal3D refD = r->direction + si.hitNormal* (-dot(si.hitNormal,r->direction)*2);
    Ray refRay(r->shadeInfo.firstHitPoint,refD,r);
    if (refRay.trace())
    {
        refRay.shadeInfo.firstHitEntity->material->shade(&refRay);
        si.Lo = kd * refRay.shadeInfo.Lo;
    }
}
