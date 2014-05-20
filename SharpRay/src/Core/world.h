#ifndef _WORLD_H_
#define _WORLD_H_
#include "ray.h"
#include <list>
#include "Entity/entity.h"
#include "Light/Light.h"
#include <Light/arealight.h>
struct Ray;
class Entity;

class World
{
public:
	std::list<Entity*> entityList;
	std::list<Light*> lightList;
    std::list<AreaLight*> areaLightList;
	static World* currentWorld;
	World();
	~World();
};
#endif
