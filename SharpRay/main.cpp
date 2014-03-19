#include <glm.hpp>
#include <Core/world.h>
#include <Entity/entity.h>
#include <Camera/camera.h>
#include <Physical/Material.h>
#include <Light/Light.h>
int main()
{
	Film film(640, 480, 0.01f);
	World t;

	Material matt;
	matt.kd = 20.0f;

	auto s = new Sphere(point3D(0, 0, 0), 1.0f);
	s->material = &matt;
	t.entityList.push_back(s);
	
	spotLight sp;
	sp.ls = 1;
	sp.position = vector3D(0, 1, 1);
	sp.color = RColor(0.f, 0.f, 1.f);
	t.lightList.push_back(&sp);
	spotLight sp2;
	sp2.ls = 1;
	sp2.position = vector3D(0, -1, 3);
	sp2.color = RColor(1.f, 0.f, 0.f);
	t.lightList.push_back(&sp2);

	pinhole c(vector3D(0,1,0),vector3D(0,0,-4),point3D(0,0,4),&film,2.0f);

	
	c.shoot(&t);
	film.dumpToFile("a.png");
	return 0;
}