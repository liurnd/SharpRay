#ifndef _FILM_H_
#define _FILM_H_
#include <Core/BaseDS.h>
#include <Core/Color.h>
struct pixelCoord2
{
    CoordFloat x, y;
};

struct Pixel
{
	int pixelIndex;
	pixelCoord2 coord;
	RColor color;
};

class Film
{
public:
	int filmWidth, filmHeight;
	int pixelCnt;

    CoordFloat pixelSize;
	Pixel* pixelList;
	inline Pixel* operator()(int i, int j){ return pixelList + i + filmHeight*j; }

	void dumpToHDRFile(const char*);
    Film(int w, int h, float filmSize);
	~Film();
};
#endif
