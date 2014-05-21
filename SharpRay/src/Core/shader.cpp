#include <Core/film.h>
#include <Entity/entity.h>
#include <Core/Color.h>
#include <Core/shader.h>
#include <Core/ray.h>
#include <Core/world.h>

void Shader::exposure()
{
    Ray** rayArray = rayQueue.getRayArray();
    int n = rayQueue.rayList.size();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        auto ray = rayArray[i];
        if (ray->trace())
        {
            ray->shadeInfo.firstHitEntity->material->shade(ray);
            ray->parent.orgPixel->color = ray->shadeInfo.Lo;
        }
    }
}



Shader::Shader()
{
}


Shader::~Shader()
{
}
