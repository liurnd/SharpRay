#include "spotLight.h"
#include <Core/shader.h>
#include <Core/ray.h>

bool spotLight::Li(Ray* r, RColor& colorOut, float& cosin) const {
	vector3D lightDirection = r->shadeInfo.firstHitPoint -position;
	cosin = dot(lightDirection, -r->shadeInfo.hitNormal);
	if (cosin < 0)
		return false;
	Ray shadowRay(position, lightDirection,r->world);
	shadowRay.shadeInfo.firstHitT = glm::length(lightDirection);
	if (shadowRay.hasHit())
		return false;
	colorOut = ls*color / shadowRay.shadeInfo.firstHitT;
	cosin /= shadowRay.shadeInfo.firstHitT;
	return true;
}

spotLight::spotLight()
{
}


spotLight::~spotLight()
{
}
