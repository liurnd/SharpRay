#include "spotLight.h"
#include <Core/shader.h>
vector3D spotLight::getDirection(ShadeInfo* si){
	return normalize(position - si->firstHitPoint);
}
bool spotLight::isInShadow(ShadeInfo*) const{
	return false;
}
RColor spotLight::Li(ShadeInfo*, const vector3D& lightDirection) const {
	return (ls*color);
}

spotLight::spotLight()
{
}


spotLight::~spotLight()
{
}
