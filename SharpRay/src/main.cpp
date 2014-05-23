#include <glm/glm.hpp>
#include <Core/world.h>
#include <Entity/entity.h>
#include <Camera/camera.h>
#include <Physical/Material.h>
#include <Light/Light.h>
#include <Physical/BSDF/bsdf.h>
#include <Light/arealight.h>
#include <Sampler/Sampler.h>
#include <ctime>

void setupWorld(World* currentWorld)
{
    Material* mi = new Mirror();
    mi->kd=1.0f;

    Material* matt1 = new Material();
    matt1->kd = 0.6f;
    matt1->color = RColor(1, 1, 1);
    auto b = new GlossySpecular();
    b->exp = 2;
    matt1->bsdf = b;
    matt1->ka = 0.6f;

    Material* matt2 = new Material();
    matt2->kd = 0.6f;
    matt2->color = RColor(1, 1, 1);
    b = new GlossySpecular();
    b->exp = 4;
    matt2->bsdf = b;
    matt2->ka = 0.6f;

    Material* matt3 = new Material();
    matt3->kd = 0.6f;
    matt3->color = RColor(1, 0, 0);
    b = new GlossySpecular();
    b->exp = 100;
    matt3->bsdf = b;
    matt3->ka = 0.6f;

    Material* matt4 = new Material();
    matt4->kd = 0.2f;
    matt4->color = RColor(1, 1, 1);
    matt4->bsdf = new Lambertian();
    matt4->ka = 0.6f;

    Entity* s = new Sphere(point3D(3, 0, 0),1.f);
    s->material = matt1;
    currentWorld->entityList.push_back(s);

    s = new Sphere(point3D(1, 0, 0),1.f);
    s->material = mi;
    currentWorld->entityList.push_back(s);

    s = new Sphere(point3D(-1, 0, 0),1.f);
    s->material = matt2;
    currentWorld->entityList.push_back(s);

    s = new Sphere(point3D(-3, 0, 0),1.f);
    s->material = matt3;
    currentWorld->entityList.push_back(s);

    s = new Plane(vector3D(0, 0, 1), point3D(0, 0, -1));
    s->material = matt4;
    currentWorld->entityList.push_back(s);


    BallLight* bl = new BallLight(point3D(0.f,5.f,5.f),3.f);
    bl->color = RColor(1.f,1.f,1.f);
    bl->ls = 0.2f;
    currentWorld->areaLightList.push_back(bl);
}

int main()
{
    srand(time(NULL));
    Film film(360, 240, 3.6e-2f);
    World* currentWorld = new World();

    printf("Setup world entities\n");
    setupWorld(currentWorld);

    pinhole c(vector3D(0,0,1),normalize(vector3D(8.f,-4.f,-2.5f)),point3D(-8.f,4.f,2.5f),&film,3.5e-2f);

	c.shoot();
	film.dumpToHDRFile("a.hdr");
	return 0;
}
