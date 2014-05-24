#ifndef _F_MATH_H_
#define _F_MATH_H_
#include <glm/glm.hpp>
#include <Core/BaseDS.h>
#include <math.h>
typedef glm::vec3 vector3D;
typedef glm::vec3 point3D;
typedef glm::vec3 normal3D;

#define PI 3.1415f
#define floatMin 0.0000001f

inline CoordFloat dot(const vector3D &x, const vector3D &y){return glm::dot(x,y);}
inline vector3D cross(const vector3D &x, const vector3D &y){return glm::cross(x,y);}
inline normal3D normalize(const vector3D &x){return glm::normalize(x);}

struct CoordSystem
{
    normal3D u, v, w;
    CoordSystem(const normal3D& ww, const normal3D& vv):w(ww)
    {
        normal3D cv = vv;
        if (dot(ww,vv)< 0.01f)
            cv = (vv.x > 0.1f)?normal3D(0,1,0):normal3D(1,0,0);
        u = normalize(cross(cv,w));
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
