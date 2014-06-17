#include "meshtriangle.h"
#include <Util/mesh.h>
#include <Core/ray.h>

normal3D MeshTriangle::normalAt(const point3D& pos, const uint8_t deferData[])
{
    point3D& v0 = triangle->vertex[0];
    point3D& v1 =  triangle->vertex[1];
    point3D& v2 =  triangle->vertex[2];

    return normalize(cross(v0-v1, v0-v2));
}

bool MeshTriangle::firstHit(const Ray* ray, CoordFloat& t, uint8_t deferData[])
{
    point3D& v0 = triangle->vertex[0];
    point3D& v1 =  triangle->vertex[1];
    point3D& v2 =  triangle->vertex[2];

	vector3D e1 = v1 - v0;
	vector3D e2 = v2 - v0;
	vector3D P, Q, T;
	CoordFloat det, inv_det, u, v;
	P = cross(ray->direction, e2);
	det = dot(e1, P);
	if (det > -0.01 && det < 0.01) return false;
	inv_det = 1.f / det;
	
	T = ray->origin - v0;
	u = dot(T, P) * inv_det;
	if (u < 0.f || u > 1.f) return false;

	Q = cross(T, e1);
	v = dot(ray->direction, Q) * inv_det;
	if (v < 0.f || u + v > 1.f) return 0;
	t = dot(e2, Q) * inv_det;

	if (t < 0)
		return false;

    if (deferData!=nullptr){
        triangleParam* param =reinterpret_cast<triangleParam*>(deferData);
        param->beta = u;
        param->gamma = v;
    }
    return true;
}
