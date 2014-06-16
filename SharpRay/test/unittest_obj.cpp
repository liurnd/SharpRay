#include <glm/glm.hpp>
#include <Core/world.h>
#include <Entity/entity.h>
#include <Camera/camera.h>
#include <Physical/Material.h>
#include <Light/Light.h>
#include <Physical/BSDF/bsdf.h>
#include <Light/arealight.h>
#include <Sampler/Sampler.h>
#include <Texture/texture.h>
#include <Util/config.h>
#include <ctime>
#include <Util/mesh.h>
#include <configmgr.h>
#include <meshReader.h>
#include <texturereader.h>

void setupMesh(World* currentWorld)
{
    spotLight* p = new spotLight();
    p->position = point3D(13.061f,7.522f,6.974f);
    p->ls = 1.f;
    p->color = RColor(1.f,1.f,1.f);
    currentWorld->lightList.push_back(p);

    p = new spotLight();
    p->position = point3D(-11.805f,6.732f,12.819f);
    p->ls = 0.2f;
    p->color = RColor(1.f,1.f,1.f);
    currentWorld->lightList.push_back(p);

    p = new spotLight();
    p->position = point3D(-8.896f,5.121f,-17.811f);
    p->ls = 0.3f;
    p->color = RColor(1.f,1.f,1.f);
    currentWorld->lightList.push_back(p);

    Material* matt1 = new Material();
    matt1->kd = 0.6f;
    matt1->color = RColor(1, 1, 1);
    auto b = new GlossySpecular();
    b->exp = 2;
    matt1->bsdf = b;
    matt1->ka = 0.6f;

    Mesh* mesh = new Mesh();
    mesh->material = matt1;

    readObjFile("odd.obj",mesh);
    mesh->addToWorld(currentWorld);
}



int main(int argc, char* argv[])
{
    srand(time(NULL));
    Film film(360, 240, 3.6e-2f);
    World* currentWorld = new World();

    currentWorld->globalConfig = new Config();
    setConfig(argc,argv,currentWorld->globalConfig);

    printf("Setup world entities\n");
    setupMesh(currentWorld);
    point3D viewPoint(30.436,27.220,29.432);
    point3D targetPoint(0,0,0);
    pinhole c(vector3D(0,1,0),normalize(targetPoint - viewPoint),viewPoint,&film,3.5e-2f);

    c.shoot(currentWorld);
    film.dumpToHDRFile("a.hdr");
    return 0;
}
