#include <glm/glm.hpp>
#include <Core/world.h>
#include <Entity/entity.h>
#include <Camera/camera.h>
#include <Physical/Material.h>
#include <Light/Light.h>
#include <Physical/BSDF/BSDF.h>
#include <Light/arealight.h>
#include <Sampler/Sampler.h>
int main()
{
    Film film(640, 480, 0.001f);
	World::currentWorld = new World();

    Mirror mi;
    mi.kd=1.0f;
    Material matt;
    matt.sampler = new NRook(10240);
    matt.sampler->shuffle();
    matt.kd = 0.6f;
    matt.color = RColor(1, 1, 1);
    matt.bsdf = new GlossySpecular();
    matt.ka = 0.1f;

    Material mattRed;
    mattRed.sampler = new NRook(10240);
    mattRed.sampler->shuffle();
    mattRed.kd = 0.6f;
    mattRed.color = RColor(1, 0, 0);
    mattRed.bsdf = new GlossySpecular();
    mattRed.ka = 0.1f;

    Material mattBlue;
    mattBlue.sampler = new NRook(10240);
    mattBlue.sampler->shuffle();
    mattBlue.kd = 0.6f;
    mattBlue.color = RColor(0, 0, 1);
    mattBlue.bsdf = new GlossySpecular();
    mattBlue.ka = 0.1f;


    //Entity* s = new Sphere(point3D(0.f, 1.f, 0.f), 0.3f);
    //s->material = &matt;
    //World::currentWorld->entityList.push_back(s);

    Entity* s = new Sphere(point3D(0, 0, 0), 0.5f);
    s->material = &matt;
	World::currentWorld->entityList.push_back(s);

    s = new Plane(vector3D(0, 0, 1), point3D(0, 0, -2));
    s->material = &matt;
    World::currentWorld->entityList.push_back(s);

    s = new Plane(vector3D(0, 0, -1), point3D(0, 0, 2));
    s->material = &matt;
    World::currentWorld->entityList.push_back(s);

    s = new Plane(vector3D(0, 1, 0), point3D(0, -2, 0));
    s->material = &mi;
    World::currentWorld->entityList.push_back(s);

    s = new Plane(vector3D(-1, 0, 0), point3D(2, 0, 0));
    s->material = &mattRed;
    World::currentWorld->entityList.push_back(s);


    s = new Plane(vector3D(1, 0, 0), point3D(-2, 0, 0));
    s->material = &mattBlue;
    World::currentWorld->entityList.push_back(s);

/*
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
*/
    BallLight bl(point3D(0.f,0.f,1.f),0.2f);
    bl.color = RColor(1.f,1.f,1.f);
    bl.ls = 2.f;
    World::currentWorld->areaLightList.push_back(&bl);


    pinhole c(vector3D(0,0,1),normalize(vector3D(0,-4.f,-1.f)),point3D(0,4,1),&film,0.4f);

	c.shoot();
	film.dumpToHDRFile("a.hdr");
	return 0;
}
