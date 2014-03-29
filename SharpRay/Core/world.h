#ifndef _WORLD_H_
#define _WORLD_H_
#include "ray.h"
#include <list>
#include "Entity/entity.h"
#include "Light/Light.h"
struct Ray;
class Entity;

class World
{
public:
	std::list<Entity*> entityList;
	std::list<Light*> lightList;
	static World* currentWorld;
	World();
	~World();
};
#endif