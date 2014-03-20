#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <Core/fmath.h>
#include <Core/Color.h>
class ShadeInfo;
class Shader;
class Entity;
class Ray;
class Light
{
public:
	virtual bool Li(Shader* shader, ShadeInfo* si, RColor& colorOut,float& cosin) const = 0;
	Light();
	~Light();
};

#include <Light/spotLight.h>
#endif