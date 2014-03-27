#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <Core/fmath.h>
#include <Core/Color.h>
struct ShadeInfo;
class Shader;
class Entity;
struct Ray;
class Light
{
public:
	virtual bool Li(Ray* r, RColor& colorOut, float& cosin) const = 0;
	Light();
	~Light();
};

#include <Light/spotLight.h>
#endif