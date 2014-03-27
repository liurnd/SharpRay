#pragma once
#include "Material.h"
class PerfectSpecular :
	public Material
{
public:
	virtual RColor Lo(ShadeInfo* si, float cosLn, RColor Li);
	PerfectSpecular();
	~PerfectSpecular();
};

