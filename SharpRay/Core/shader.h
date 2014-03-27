#ifndef _SHADER_H_
#define _SHADER_H_
#include <deque>
class World;
class Entity;
struct Ray;

class Shader
{
	class RayQueue
	{
	public:
		std::deque<Ray*> rayList;
		void addRay(Ray* r){rayList.push_back(r);}
		Ray* getRay(){ auto tmp = rayList.front(); rayList.pop_front();  return tmp; }
	};

public:
	RayQueue rayQueue;
	
	void exposure(const World* w);
	void shade(Ray*, const World* world);
	Shader();
	~Shader();
};

#endif
