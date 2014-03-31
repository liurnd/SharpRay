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
	
	/**
	 * @brief exposure the film
	 * @details Cast all the ray in rayQueue.
	 *  When tracing complete, set the color of corresponding pixel of the ray.
	 */
	void exposure();

	Shader();
	~Shader();
};

#endif
