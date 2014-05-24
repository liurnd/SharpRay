#ifndef TEXTURE_H
#define TEXTURE_H
#include <Core/Color.h>
#include <Core/BaseDS.h>

#pragma pack(1)
struct RGBPixel{
    unsigned char r,g,b;
};

class Texture
{
    int width, height;
    RGBPixel* pixelList;
public:
    Texture(){}
    Texture(const char* fName);
    RColor operator ()(const normal3D& po);
};

#endif // TEXTURE_H
