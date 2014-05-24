#include <Entity/sphere.h>
#include <Core/ray.h>
#include <Core/BaseDS.h>

Sphere::~Sphere()
{
}

normal3D Sphere::normalAt(const point3D& pos)
{
    return normalize(pos - position);
}

bool Sphere::firstHit(const Ray* r, CoordFloat& t)
{
    point3D nPos = position - r->origin;
    float b = -2*dot(r->direction, nPos);
    float a = dot(r->direction, r->direction);
    float c = dot(nPos, nPos)-radius*radius;
    float b2ac = b*b - 4 * a*c;
    if (b2ac < 0.0f)
        return false;
    t = (-b - sqrt(b2ac)) / (2 * a);
    if (t > 0.0f)
        return true;
    t = (-b + sqrt(b2ac)) / (2 * a);
    if (t > 0.0f)
        return true;
    return false;
}

bool Sphere::map2texture(const point3D &point, point3D &texturePoint)
{
    normal3D centre2point = (point - position) / radius;
    if (centre2point.z > 0.9999999f||centre2point.z < -0.999999f)
    {
        texturePoint.x = 0;
        texturePoint.y = 0;
    }
    else{
        texturePoint.x = (atan2(centre2point.y,centre2point.x)+PI)/(2*PI);
        texturePoint.y = acos(centre2point.z)/(PI);
    }
    return true;
}
