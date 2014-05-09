#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <cstdlib>
#include <stdint.h>
struct RandomGen{
	float getRandomF(){
		return static_cast <float>(getRandomI()) / static_cast <float>(RAND_MAX);
	}
	float getRandomF(float a, float b) { return (b - a)*getRandomF() + a; }
    virtual uint32_t getRandomI(){ return rand(); }
	uint32_t getRandomI(int a, int b){ return a + getRandomI() % (b - a); }
};

struct mtRandom:RandomGen{
	uint32_t getRandomI()
	{
		uint32_t t;
		t = x ^ (x << 11);
    	x = y; y = z; z = w;
    	return w = w ^ (w >> 19) ^ t ^ (t >> 8);
	}
	mtRandom()
	{
		x = rand();
		y = rand();
		z = rand();
		w = rand();
	}
private:
	uint32_t x, y, z, w;
};

#include <Core/BaseDS.h>

enum samplerType{
    hemisphere,
    square,
    disk
} ;

class Sampler
{
protected:
    RandomGen* randomGen;
public:
	virtual void shuffle() = 0;
    virtual void shuffleIndex(int num){
        if (indexList==NULL)
            indexList = new int[num];
        for (int i = 0; i < num ;i++)
            indexList[i] = randomGen->getRandomI(0,numSample);
    }

    samplerType type;
	void mapToDisk();
	void mapToHemiSphere(float e);
    Sampler(int num) :numSample(num), type(square){indexList = NULL; sampleList = new normal3D[num]; randomGen = new mtRandom();}

    normal3D* sampleList;
    int* indexList;
	int numSample;
	Sampler();
	Sampler::~Sampler()
	{
		delete [] sampleList;
		delete randomGen;
	}
};


#include "nRook.h"
#endif // !_SAMPLER_H_
