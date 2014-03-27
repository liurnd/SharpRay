#include "camera.h"
#include <Core/ray.h>

void pinhole::shoot(World* world)
{
	for (int i = 0; i < lFilm->pixelCnt; i++)
	{
		Pixel* nPixel = &(lFilm->pixelList[i]);
		shader->rayQueue.addRay(new Ray(mapFilm2World(-nPixel->coord.x, -nPixel->coord.y), pinholePos, lFilm, nPixel,world));
	}
	shader->exposure(world);
}
