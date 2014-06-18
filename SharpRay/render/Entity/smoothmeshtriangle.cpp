#include "smoothmeshtriangle.h"
#include <Util/mesh.h>
#include <Entity/meshtriangle.h>
SmoothMeshTriangle::SmoothMeshTriangle()
{
}

normal3D SmoothMeshTriangle::normalAt(const point3D &pos, const uint8_t deferData[])
{
	const triangleParam* param = reinterpret_cast<const triangleParam*>(deferData);
	if (deferData != nullptr)
		return triangle->normal[0] * (1 - param->beta - param->gamma)  + triangle->normal[1] * param->beta + triangle->normal[2] * param->gamma;
	return normal3D(1, 0, 0);
}
