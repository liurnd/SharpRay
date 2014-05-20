#include "spotLight.h"
#include <Core/shader.h>
#include <Core/ray.h>

bool spotLight::Lo(Ray* r, RColor& colorOut, vector3D& lightVector)  {
	lightVector = r->shadeInfo.firstHitPoint - position;
	float cosin = dot(lightVector, -r->shadeInfo.hitNormal);
	if (cosin < 0)
		return false;
	Ray shadowRay(position, normalize(lightVector));
	shadowRay.shadeInfo.firstHitT = glm::length(lightVector);
	if (shadowRay.hasHit())
		return false;
    colorOut = ls*color / shadowRay.shadeInfo.firstHitT/shadowRay.shadeInfo.firstHitT;
	return true;
}

spotLight::spotLight()
{
}

spotLight::~spotLight()
{
}
