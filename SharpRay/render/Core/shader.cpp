#include <Core/film.h>
#include <Entity/entity.h>
#include <Core/color.h>
#include <Core/shader.h>
#include <Core/ray.h>
#include <Core/world.h>
#include <algorithm>
#include <omp.h>

void Shader::exposure(RayList& rayQueue, int numThread)
{
    Ray** rayArray = rayQueue.getRayArray();
    int n = rayQueue.rayList.size();
    Sampler** samplerList = new Sampler*[numThread];
    for (int i = 0 ;i < numThread; i++)
        samplerList[i] = new NRook(10240);
    omp_set_num_threads(numThread);

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < n; i++)
    {
        auto ray = rayArray[i];
        ray->sampler = samplerList[omp_get_thread_num()];
        ray->sampler->shuffle();

        if (ray->trace())
        {
            ray->shadeInfo.firstHitEntity->material->shade(ray);
            ray->parent.orgPixel->color+=ray->shadeInfo.Lo;
        }
        delete ray;
    }
	
	for (int i = 0; i < numThread; i++)
		delete samplerList[i];
	delete[] samplerList;
}



Shader::Shader()
{
}


Shader::~Shader()
{
}
