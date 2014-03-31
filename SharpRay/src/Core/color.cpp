#include "film.h"
#include <cmath>
#include <Core/Color.h>
#define max(X,Y) (X)>(Y)?(X):(Y)

void colorMix(RGBAColor& origin, const RGBAColor& newColor, float transferFactor)
{
	origin.r += floor(newColor.r * 255 / newColor.a * transferFactor);
	origin.b += floor(newColor.b * 255 / newColor.a * transferFactor);
	origin.g += floor(newColor.g * 255 / newColor.a * transferFactor);
	origin.a = origin.a > newColor.a ? origin.a : newColor.a;
}