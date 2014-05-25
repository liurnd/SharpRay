#include "config.h"
#include <Core/getopt.h>
#include <cstdio>
static const struct option longOpts[]=
{
{"aa-sample", optional_argument, NULL, 'A'},
{"al-sample", optional_argument, NULL, 'a'},
{"pt-sample", optional_argument, NULL, 'p'},
{"trace-depth", optional_argument, NULL, 't'},
{"help", optional_argument, NULL, 'h'}
};

static const char* optString = "A:a:p:t:h?";

void displayUsage()
{
    fprintf(stderr, "Usage: \n\
-A, --aa-sample\t\tThe number of Anti-alias samples\n\
-a, --al-sample\t\tThe number of area light samples\n\
-p, --pt-sample\t\tThe number of samples would path tracer cast\n\
-t, --trace-depth\t\tPath tracer depth\n\
            ");
}

Config::Config(int argc, char *argv[])
{
    char c;int longIndex;
    numAntialiasSample = 4;
    numAreaLightSample = 24;
    numPathTraceSample = 2;
    traceLevelLimit = 3;
    while((c = getopt_long(argc, argv,optString,longOpts,&longIndex))!=-1)
    {
        switch (c){
        case 'A':
            numAntialiasSample = atoi(optarg);
            break;
        case 'a':
            numAreaLightSample = atoi(optarg);
            break;
        case 'p':
            numPathTraceSample = atoi(optarg);
        case 't':
            traceLevelLimit = atoi(optarg);
        case 'h':
        case '?':
            displayUsage();
            exit(-1);
        }
    }
    printf("SharpRay is ready to run:\nnAAS:%d, nALS:%d, nPTS:%d, td:%d\n",
           numAntialiasSample,
           numAreaLightSample,
           numPathTraceSample,
           traceLevelLimit);
}
