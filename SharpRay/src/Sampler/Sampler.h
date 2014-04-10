#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <cstdlib>

struct RandomGen{
	virtual float getRandomF(){
		return static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
	}
	virtual float getRandomF(float a, float b) { return (b - a)*getRandomF() + a; }
	virtual int getRandomI(){ return rand(); };
	virtual int getRandomI(int a, int b){ return a + getRandomI() % (b - a); }
};

#include <Core/fmath.h>
class Sampler
{
public:
	virtual void shuffle() = 0;
	virtual void shuffleIndex(){}
	void mapToDisk();
	void mapToHemiSphere(float e);
	Sampler(int num) :numSample(num){ sampleList = new normal3D[num]; }

	normal3D* sampleList;
	RandomGen randomGen;
	int numSample;
	Sampler();
	~Sampler();
};


#include "nRook.h"
#endif // !_SAMPLER_H_
