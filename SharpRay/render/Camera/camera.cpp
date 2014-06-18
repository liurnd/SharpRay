#include "camera.h"


camera::camera(const vector3D& u, const normal3D& d, const point3D& pos, Film* f, RayLevelType numAntialiasSample) :direction(d), position(pos), lFilm(f)
{
    numAASample = numAntialiasSample;
	axis_x = normalize(cross(u,d));
	axis_y = cross(axis_x,direction);
}

void camera::exposureFilm()
{
	for (int i = 0; i < lFilm->pixelCnt; i++)
	{
		Pixel* nPixel = &(lFilm->pixelList[i]);
		nPixel->color /= numAASample;
	}
}

camera::~camera()
{
}
