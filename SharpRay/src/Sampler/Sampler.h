#ifndef _SAMPLER_H_
#define _SAMPLER_H_

class Sampler
{
public:
	virtual void initSampler(int num) = 0;

	struct Sample
	{
		float x, y;
	};
	Sample* sampleList;
	int numSample;
	Sampler();
	~Sampler();
};


#endif // !_SAMPLER_H_
