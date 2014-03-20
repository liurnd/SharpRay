#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_
#include <Core/Color.h>
#include <Light/Light.h>

class spotLight:public Light
{
public:
	float ls;
	RColor color;
	vector3D position;
	spotLight();
	bool Li(Shader* shader, ShadeInfo* si, RColor& colorOut, float& cosin) const;
	~spotLight();
};
#endif