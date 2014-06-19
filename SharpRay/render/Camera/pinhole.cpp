#include "pinhole.h"
#include <Core/ray.h>

void pinhole::generateRays(World* world, RayList& rayList)
{
    Sampler* sampler = new NRook(10240);
    sampler->shuffle();
    for (int i = 0; i < lFilm->pixelCnt; i++)
    {
        sampler->shuffleIndex(numAASample);
        Pixel* nPixel = &(lFilm->pixelList[i]);
        for (int j = 0; j < numAASample;j++)
        {
			CoordFloat dx = numAASample == 1 ? 0 : ((*sampler)[j].x - 0.5f)*lFilm->pixelSize;
			CoordFloat dy = numAASample == 1 ? 0 : ((*sampler)[j].y - 0.5f)*lFilm->pixelSize;
            point3D pixelPos = mapFilm2World(nPixel->coord.x+dx, nPixel->coord.y+dy);
            Ray *ray = new Ray(pixelPos, normalize(pinholePos-pixelPos), lFilm, nPixel);
            ray->currentWorld = world;
			rayList.addRay(ray);
        }
    }
	delete sampler;
}
