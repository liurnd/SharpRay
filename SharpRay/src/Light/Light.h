#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <Core/BaseDS.h>
#include <Core/Color.h>
struct ShadeInfo;
class Shader;
class Entity;
struct Ray;
class Light
{
public:
	/**
	 * @brief Calculate the radience to a giving point
	 * @details This function calculate the radience this light can give to a particular point
	 * 	The implementation of this function should check whether the hit point is shadowed by 
	 * 	other entity (if nessary), and return the output radience to the hit point.
	 * 
	 * @param r A traced ray to point out the hit point
	 * @param colorOut [out] the output radience from the light to the giving hit point
	 * @param lightVector [out] Vector from  this light to hit point
	 * @return Whether the light can cast a ray can reach the hit point
	 */
	virtual bool Lo(Ray* r, RColor& colorOut, vector3D& lightVector) const = 0;
	Light();
	~Light();
};

#include <Light/spotLight.h>
#endif
