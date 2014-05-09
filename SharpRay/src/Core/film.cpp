#include "film.h"

#include <cstdio>
typedef unsigned char byte;

struct HDRHeader{
	int width, height;
};
struct HDRPixel{
	int x, y;
    ColorFloat r, g, b;
	HDRPixel(int xx,int yy,const Pixel& p) :x(xx),y(yy),r(p.color.r), g(p.color.g), b(p.color.b){}
};

void Film::dumpToHDRFile(const char* fName)
{
	HDRHeader hdr;
	hdr.width = filmWidth; hdr.height = filmHeight;
	FILE* fout = fopen(fName, "wb");
	fwrite(&hdr, sizeof(hdr), 1, fout);
	for (int i = 0; i < pixelCnt; i++)
	{
		int row = i / filmWidth;
		int col = i % filmWidth;
		HDRPixel tmpPixel(col,row,pixelList[i]);
		fwrite(&tmpPixel, sizeof(tmpPixel), 1, fout);
	}
	fclose(fout);
}

Film::Film(int w, int h, float ps) :filmWidth(w), filmHeight(h), pixelSize(ps), pixelCnt(w*h)
{
	pixelList = new Pixel[w*h];
	float minX = -filmWidth / 2.0f * pixelSize, x, y = filmHeight / 2.0f *pixelSize;
	unsigned int index = 0;
	for (int i = 0; i < h; i++)
	{
		y -= pixelSize;
		x = minX;
		for (int j = 0; j < w; j++)
		{
			x += pixelSize;
			pixelList[index].pixelIndex = index;
			pixelList[index].color = RColor(0); 
			pixelList[index].coord.x = x;
			pixelList[index].coord.y = y;
			index++;
		}
	}
}

Film::~Film()
{
	delete [] pixelList;
}
