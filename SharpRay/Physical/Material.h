#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include <Core/Color.h>
struct Ray;
struct ShadeInfo;
class Material
{
public:
	float ka, kd;
	RColor cd;
	/**
	 * @brief Function to calculate output radience based on incoming radience
	 * 
	 * @param si ShadeInfo pointer to point out hit point on the material surface
	 * @param cosLn cosin of incoming radience 
	 * @param Li Incoming radience value
	 * @return Output radience
	 */
	virtual RColor Lo(ShadeInfo* si, float cosLn, RColor Li)
	{
		return kd*Li / (4.0f * 3.14f);
	}
};
#endif