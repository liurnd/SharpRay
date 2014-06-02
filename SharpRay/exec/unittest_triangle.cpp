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
vector3D vecList[] = {point3D(0,1,0),point3D(1,0,1), point3D(-1,0,1), point3D(0,-1,0)};
void setupMesh(World* currentWorld)
{
    spotLight* p = new spotLight();
    p->position = point3D(0.f,5.f,5.f);
    p->ls = 0.2f;
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
    mesh->vertices = vecList;
    mesh->numVertices = 4;

    MeshTriangle* tr = new MeshTriangle();
    tr->mesh = mesh;
    tr->vertexIdx[0] = 0;
    tr->vertexIdx[1] = 2;
    tr->vertexIdx[2] = 1;
    tr->material = matt1;
    currentWorld->entityList.push_back(tr);

    tr = new MeshTriangle();
    tr->mesh = mesh;
    tr->vertexIdx[0] = 1;
    tr->vertexIdx[1] = 2;
    tr->vertexIdx[2] = 3;
    tr->material = matt1;
    currentWorld->entityList.push_back(tr);
}



int main(int argc, char* argv[])
{
    srand(time(NULL));
    Film film(360, 240, 3.6e-2f);
    World* currentWorld = new World();
    currentWorld->globalConfig = new Config(argc, argv);

    printf("Setup world entities\n");
    setupMesh(currentWorld);

    pinhole c(vector3D(0,0,1),normalize(vector3D(8.f,-4.f,-2.5f)),point3D(-8.f,4.f,2.5f),&film,3.5e-2f);

    c.shoot(currentWorld);
    film.dumpToHDRFile("a.hdr");
    return 0;
}
