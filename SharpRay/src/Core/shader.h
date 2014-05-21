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
        Ray** rayArray;
	public:
        RayQueue(){
            rayArray = NULL;
        }

		std::deque<Ray*> rayList;
		void addRay(Ray* r){rayList.push_back(r);}
		Ray* getRay(){ auto tmp = rayList.front(); rayList.pop_front();  return tmp; }
        Ray** getRayArray(){
            if (rayArray==NULL)
            {
                rayArray = new Ray*[rayList.size()];
                int iv= 0;
                for (auto i = rayList.begin(); i != rayList.end();i++)
                {
                    rayArray[iv] = *i;
                    iv++;
                }
            }
            return rayArray;
        }
        ~RayQueue()
        {
            delete [] rayArray;
        }
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
