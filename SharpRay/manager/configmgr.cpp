#include "configmgr.h"
#include <getopt/getopt.h>
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



void setConfig(int argc, char* argv[], Config* config)
{
    char c;int longIndex;
    config->numAntialiasSample = 4;
    config->numAreaLightSample = 24;
    config->numPathTraceSample = 2;
    config->traceLevelLimit = 0;
    while((c = getopt_long(argc, argv,optString,longOpts,&longIndex))!=-1)
    {
        switch (c){
        case 'A':
            config->numAntialiasSample = atoi(optarg);
            break;
        case 'a':
            config->numAreaLightSample = atoi(optarg);
            break;
        case 'p':
            config->numPathTraceSample = atoi(optarg);
        case 't':
            config->traceLevelLimit = atoi(optarg);
        case 'h':
        case '?':
            displayUsage();
            exit(-1);
        }
    }
    printf("SharpRay is ready to run:\nnAAS:%d, nALS:%d, nPTS:%d, td:%d\n",
           config->numAntialiasSample,
           config->numAreaLightSample,
           config->numPathTraceSample,
           config->traceLevelLimit);
}
