#include "smoothmeshtriangle.h"
#include <Util/mesh.h>
#include <Entity/meshtriangle.h>
smoothMeshTriangle::smoothMeshTriangle()
{
}

normal3D smoothMeshTriangle::normalAt(const point3D &pos, const uint8_t deferData[])
{
	const triangleParam* param = reinterpret_cast<const triangleParam*>(deferData);
	if (deferData != nullptr)
		return triangle->normal[0] * param->beta + triangle->normal[1] * param->gamma + triangle->normal[2] * (1 - param->beta - param->gamma);
	return normal3D(1, 0, 0);
}
