#ifndef _FILM_H_
#define _FILM_H_
#include <Core/Color.h>
struct pixelCoord2
{
	float x, y;
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

	float pixelSize;
	Pixel* pixelList;
	inline Pixel* operator()(int i, int j){ return pixelList + i + filmHeight*j; }

#ifdef PNG_OUTPUT
	void dumpToPNGFile(const char*);
#endif

	void dumpToHDRFile(const char*);
	Film(int w, int h, float ps);
	~Film();
};
#endif
