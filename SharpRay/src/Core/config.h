#ifndef CONFIG_H
#define CONFIG_H
#include <Core/BaseDS.h>

struct Config
{
public:
    RayLevelType numAntialiasSample;
    RayLevelType numAreaLightSample;
    RayLevelType numPathTraceSample;
    RayLevelType traceLevelLimit;
    Config(int argc, char* argv[]);
};

#endif // CONFIG_H
