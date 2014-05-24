#include "texture.h"
#include <Texture/jpgd.h>
RColor Texture::operator ()(const normal3D& po)
{
    RColor tmp;
    int x,y;
    if (po.x >= 1.f)
        x = width-1;
    else
        x = static_cast<int>(po.x * width);

    if (po.y >=1.f)
        y = height-1;
    else
        y = static_cast<int>(po.y * height);
    assert(x>=0); assert(y>=0);
    RGBPixel* pixel= pixelList + y*width + x;
    tmp.r = static_cast<float>(pixel->r)/255;
    tmp.g = static_cast<float>(pixel->g)/255;
    tmp.b = static_cast<float>(pixel->b)/255;
    return tmp;
}
Texture::Texture(const char* fName)
{
    int d;
    pixelList = (RGBPixel*) jpgd::decompress_jpeg_image_from_file(fName,&width,&height,&d, 3);
    assert(d == 3);
}
