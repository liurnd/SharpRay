#ifndef _SHADER_H_
#define _SHADER_H_
#include <deque>
class World;
class Entity;
struct Ray;
class RayList
{
	Ray** rayArray;
public:
	RayList(){
		rayArray = nullptr;
	}

	std::deque<Ray*> rayList;
	void addRay(Ray* r){ rayList.push_back(r); }
	Ray* getRay(){ auto tmp = rayList.front(); rayList.pop_front();  return tmp; }
	Ray** getRayArray(){
		if (rayArray == nullptr)
		{
			rayArray = new Ray*[rayList.size()];
			int iv = 0;
			for (auto i = rayList.begin(); i != rayList.end(); i++)
			{
				rayArray[iv] = *i;
				iv++;
			}
		}
		return rayArray;
	}
	~RayList()
	{
		delete[] rayArray;
	}
};

class Shader
{
public:	
	/**
	 * @brief exposure the film
	 * @details Cast all the ray in rayQueue.
	 *  When tracing complete, set the color of corresponding pixel of the ray.
	 */
	void exposure(RayList& rayQueue, int numThread = 4);

	Shader();
	~Shader();
};

#endif
