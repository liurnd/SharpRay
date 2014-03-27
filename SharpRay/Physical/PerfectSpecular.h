#pragma once
#include "Material.h"
class PerfectSpecular :
	public Material
{
public:
	RColor Lo(ShadeInfo* si, float cosLn, RColor Li){ return RColor(0); };
	PerfectSpecular();
	~PerfectSpecular();
};

