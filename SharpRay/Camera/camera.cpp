#include "camera.h"


camera::camera(const vector3D& u, const vector3D& d, const point3D& pos, Film* f) :direction(normalize(d)), position(pos), lFilm(f)
{
	axis_x = normalize(cross(u,d));
	axis_y = cross(axis_x,direction);
	shader = new Shader();
}

camera::~camera()
{
}
