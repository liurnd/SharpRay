#ifndef _PINHOLE_H_
#define _PINHOLE_H_
#include <Camera/camera.h>
class pinhole:public camera
{
public:
	point3D pinholePos;
	pinhole(vector3D up, vector3D d, const point3D& pos, Film* f, float focalLength) :camera(up, d, pos, f){
        pinholePos = position + direction*focalLength;
	}
	void generateRays(World*, RayList&) override;

	~pinhole(){}
};

#endif