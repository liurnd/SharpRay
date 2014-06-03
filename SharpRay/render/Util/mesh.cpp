#include "mesh.h"
#include <Core/world.h>
#include <Physical/Material.h>
void Mesh::addToWorld(World* world)
{
    for (int i = 0; i < numTriangle;i++)
    {
        auto tmp = new MeshTriangle();
        tmp->material = material;
        tmp->triangle = triMesh+i;
        world->entityList.push_back(tmp);
    }
}
