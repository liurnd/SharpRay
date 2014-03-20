#include "spotLight.h"
#include <Core/shader.h>
#include <Core/ray.h>

bool spotLight::Li(Shader* shader, ShadeInfo* si, RColor& colorOut, float& cosin) const {
	vector3D lightDirection = si->firstHitPoint - position;
	cosin = dot(lightDirection, -si->hitNormal);
	if (cosin < 0)
		return false;
	ShadeInfo ssi;
	ssi.firstHitT = glm::length(lightDirection);
	Ray r(position, lightDirection);
	r.shadeInfo = &ssi;
	
	if (shader->castShadowRay(&r, si->world))
		return false;
	colorOut = ls*color;
	cosin /= ssi.firstHitT;
	return true;
}

spotLight::spotLight()
{
}


spotLight::~spotLight()
{
}
