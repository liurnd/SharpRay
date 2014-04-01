#pragma once
#include <Core/film.h>
#include <Core/world.h>
#include <Core/shader.h>

class camera
{
protected:
	vector3D axis_x, axis_y;
	normal3D direction;
	point3D position;
	inline point3D mapFilm2World(float x, float y){ return position+axis_x*x + axis_y*y; }

	Shader* shader;
	Film* lFilm;
public:
	camera(const vector3D& u, const vector3D& d, const point3D& pos, Film* f);

	virtual void shoot() = 0;
	virtual ~camera();
};

class pinhole:camera
{
public:
	point3D pinholePos;
	pinhole(vector3D up, vector3D d, const point3D& pos, Film* f, float focalLength) :camera(up, d, pos, f){
		pinholePos = direction*focalLength;
	}
	void shoot();
	~pinhole(){}
};

class lenCamera:camera
{
public:
	float focalLength;
	float apertureDiameter;
	lenCamera();
	void shoot();
	~lenCamera(){}
};
