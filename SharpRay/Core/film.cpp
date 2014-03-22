#include "film.h"
#include <png.hpp>
#include <cstdio>
typedef unsigned char byte;

void Film::dumpToPNGFile(const char* fName)
{
	png::image<png::rgb_pixel> fout(filmWidth,filmHeight);
	for (int i = 0; i < pixelCnt; i++)
	{
		int I = i / filmWidth;
		int J = i % filmWidth;
		fout.set_pixel(J, I, png::rgb_pixel((byte)(pixelList[i].color.r*100.f),
			(byte)(pixelList[i].color.g * 100.f),
			(byte)(pixelList[i].color.b * 100.f)));
	}
	fout.write(fName);
}


struct HDRHeader{
	int width, height;
};
struct HDRPixel{
	int x, y;
	float r, g, b;
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
			pixelList[index].color = { 0.f, 0.f, 0.f };
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
