#include <glm/glm.hpp>
#include <Core/world.h>
#include <Entity/entity.h>
#include <Camera/camera.h>
#include <Physical/Material.h>
#include <Light/Light.h>
#include <Physical/PerfectSpecular.h>
#include <Sampler/Sampler.h>
int main()
{
	Film film(640, 480, 0.01f);
	World::currentWorld = new World();

	Material matt;
    matt.sampler = new NRook(1024);
    matt.sampler->mapToHemiSphere(100);
	matt.kd = 0.6f;
	matt.color = RColor(1, 1, 1);
    matt.ka = 0.1f;
	matt.bsdf = new PerfectSpecular();

	Entity* s = new Sphere(point3D(0.f, 1.f, 0.f), 0.1f);
	s->material = &matt;
	World::currentWorld->entityList.push_back(s);

	s = new Sphere(point3D(0, 0, 0), 0.5f);
	s->material = &matt;
	World::currentWorld->entityList.push_back(s);
	
	s = new Plane(vector3D(0, 1, 0), point3D(0, -2, 0));
	s->material = &matt;
	World::currentWorld->entityList.push_back(s);
	
	spotLight sp;
	sp.ls = .5f;
	sp.position = vector3D(0, -1, 0);
	sp.color = RColor(0.f, 0.f, 1.f);
	World::currentWorld->lightList.push_back(&sp);
	spotLight sp2;
	sp2.ls = 2.f;
	sp2.position = vector3D(2.f, 2.f, 2.f);
	sp2.color = RColor(1.f, 0.f, 0.f);
	World::currentWorld->lightList.push_back(&sp2);
	spotLight sp3;
	sp3.ls = 2.f;
	sp3.position = vector3D(-2.f, 2.f,2.f);
	sp3.color = RColor(0.f, 1.f, 0.f);
	World::currentWorld->lightList.push_back(&sp3);

	pinhole c(vector3D(0,1,0),vector3D(0,-1.f,-4.f),point3D(0,1,4),&film,2.0f);

	
	c.shoot();
	film.dumpToHDRFile("a.hdr");
	return 0;
}
