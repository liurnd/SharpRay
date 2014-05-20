#include <Core/film.h>
#include <Entity/entity.h>
#include <Core/Color.h>
#include <Core/shader.h>
#include <Core/ray.h>
#include <Core/world.h>

void Shader::exposure()
{

    int i= 0;
	while (!rayQueue.rayList.empty())
	{
        auto ray = rayQueue.getRay();

        if (ray->trace())
        {
            ray->shadeInfo.firstHitEntity->material->shade(ray);
            ray->parent.orgPixel->color = ray->shadeInfo.Lo;
        }
        if (i%100 == 0)
            printf("Shading: %.2f%%\n", static_cast<float>(i) * 100 / ray->currentFilm->pixelCnt);
        i++;
	}
}



Shader::Shader()
{
}


Shader::~Shader()
{
}
