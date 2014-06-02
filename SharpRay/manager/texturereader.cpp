#include "texturereader.h"
#include <Texture/texture.h>
#include "jpgd.h"
bool readTexture(const char* fName, Texture* texture)
{
    int d;
    texture->pixelList = (RGBPixel*) jpgd::decompress_jpeg_image_from_file(fName,&(texture->width),&(texture->height),&d, 3);
    return (d == 3);
}
