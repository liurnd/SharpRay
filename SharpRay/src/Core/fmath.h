#ifndef _F_MATH_H_
#define _F_MATH_H_
#include <glm/glm.hpp>
#include <Core/BaseDS.h>
#include <math.h>
typedef glm::vec3 vector3D;
typedef glm::vec3 point3D;
typedef glm::vec3 normal3D;

#define pi 3.1415f
#define dot glm::dot
#define cross glm::cross
#define normalize glm::normalize
#define floatMin 0.0000001f
struct CoordSystem
{
    normal3D u, v, w;
    CoordSystem(const normal3D& ww):w(ww)
    {
        normal3D tx(1,0,0);
        if (w.y < floatMin && w.z < floatMin)
            tx = normal3D(0,1,0);
        u = normalize(cross(tx,w));
        v = cross(w,u);
    }

    vector3D operator () (const vector3D & vc)
    {
        return u*vc.x+v*vc.y+w*vc.z;
    }

    vector3D operator () (const CoordFloat x, const CoordFloat y, const CoordFloat z)
    {
        return u*x+v*y+w*z;
    }
};

#endif
