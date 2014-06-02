#ifndef MIRROR_H
#define MIRROR_H
#include <Physical/Material.h>
class Mirror : public Material
{
public:
    Mirror();
    void shade(Ray* r);
};

#endif // MIRROR_H
