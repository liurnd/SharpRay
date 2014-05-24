#include "camera.h"
#include <Core/ray.h>

void pinhole::shoot(World *world)
{
    Sampler* sampler = new NRook(10240);
    sampler->shuffle();
    for (int i = 0; i < lFilm->pixelCnt; i++)
    {
        sampler->shuffleIndex(numAASample);
        Pixel* nPixel = &(lFilm->pixelList[i]);
        for (int j = 0; j < numAASample;j++)
        {
            point3D pixelPos = mapFilm2World(nPixel->coord.x+((*sampler)[j].x-0.5f)*lFilm->pixelSize, nPixel->coord.y+((*sampler)[j].y-0.5f)*lFilm->pixelSize);
            Ray *ray = new Ray(pixelPos, normalize(pinholePos-pixelPos), lFilm, nPixel);
            ray->currentWorld = world;
            shader->rayQueue.addRay(ray);
        }
    }

    printf("Done generating ray samples\n");

    shader->exposure(4);

    for (int i = 0;i < lFilm->pixelCnt;i++)
    {
        Pixel* nPixel = &(lFilm->pixelList[i]);
        nPixel->color /= numAASample;
    }
}
