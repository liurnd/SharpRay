#include <Core/film.h>
#include <Entity/entity.h>
#include <Core/Color.h>
#include <Core/shader.h>
#include <Core/ray.h>
#include <Core/world.h>

void Shader::exposure()
{
	while (!rayQueue.rayList.empty())
	{
		auto ray = rayQueue.getRay();
		ray->trace();
		ray->shadeInfo.firstHitEntity->material->shade(ray);
		ray->parent.orgPixel->color = ray->shadeInfo.Lo;
	}
}



Shader::Shader()
{
}


Shader::~Shader()
{
}
