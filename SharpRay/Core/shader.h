#ifndef _SHADER_H_
#define _SHADER_H_
#include <deque>
class World;
class Entity;
class Ray;

class Shader
{
	class RayQueue
	{
	public:
		std::deque<Ray*> rayList;
		void addRay(Ray* r){rayList.push_back(r);}
		Ray* getRay(){ auto tmp = rayList.front(); rayList.pop_front();  return tmp; }
	};

	void castRay(Ray*, const World*);
public:
	RayQueue rayQueue;
	bool castShadowRay(Ray*, const World*) const;
	void exposure(const World* w);
	void shade(const Ray*, const World* world);
	Shader();
	~Shader();
};

struct ShadeInfo
{
	const World* world;
	float transferFactor;
	float firstHitT;
	point3D firstHitPoint;
	vector3D hitNormal;
	Entity* firstHitEntity;
	RColor Lo;
};

#endif
