#ifndef _COLOR_H_
#define _COLOR_H_
#include <glm/glm.hpp>
struct RGBAColor
{
	unsigned char r, g, b, a;
};

typedef glm::vec3 RColor;

RGBAColor& projectToRGB(const RColor&, float ISO);
#endif
