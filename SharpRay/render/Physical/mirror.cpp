#include "mirror.h"
#include <Core/BaseDS.h>
#include <Core/ray.h>
#include <Entity/entity.h>
#include <Core/world.h>
#include <Util/config.h>
Mirror::Mirror()
{
}

void Mirror::shade(Ray *r)
{
    World* currentWorld = r->currentWorld;
    ShadeInfo& si = r->shadeInfo;
    si.hitPoint = r->origin + r->direction*si.firstHitT;
    si.hitNormal = si.firstHitEntity->normalAt(si.hitPoint);
    si.Lo = RColor(0);
    if (r->rayLevel>currentWorld->globalConfig->traceLevelLimit)
        return;
    normal3D refD = r->direction + si.hitNormal* (-dot(si.hitNormal,r->direction)*2);

    for (auto i = currentWorld->areaLightList.begin(); i != currentWorld->areaLightList.end();i++)
    {
        RColor Li;
        AreaLight* light = *i;
        Ray lightRay(si.hitPoint,refD,r);

        if (light->CalcRad(&lightRay,Li))
            if(!lightRay.hasHit())
            {
                si.Lo+=Li;
            }
    }

    Ray refRay(r->shadeInfo.hitPoint,refD,r);
    if (refRay.trace())
    {
        refRay.shadeInfo.firstHitEntity->material->shade(&refRay);
        si.Lo += kd * refRay.shadeInfo.Lo;
    }
}
