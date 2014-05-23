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
    void shuffleIndex(int num);
    void shuffleIndex(){
        shuffleIndex(numSample);
    }

    samplerType type;
    static normal3D mapToDisk(const normal3D&);
    static normal3D mapToHemiSphere(const normal3D&, float e);
    Sampler(int num);

    normal3D* sampleList;
    int* indexList;
	int numSample;
    float hemisphereExp;
	Sampler();

    normal3D operator [](int index);

    virtual ~Sampler();
};


#include "nRook.h"
#endif // !_SAMPLER_H_
