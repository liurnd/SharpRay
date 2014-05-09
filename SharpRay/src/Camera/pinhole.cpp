#include "camera.h"
#include <Core/ray.h>

void pinhole::shoot()
{
	for (int i = 0; i < lFilm->pixelCnt; i++)
	{
		Pixel* nPixel = &(lFilm->pixelList[i]);
        point3D pixelPos = mapFilm2World(-nPixel->coord.x, -nPixel->coord.y);
        shader->rayQueue.addRay(new Ray(pixelPos, pinholePos-pixelPos, lFilm, nPixel));
	}
	shader->exposure();
}
