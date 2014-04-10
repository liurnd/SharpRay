#include <Sampler/Sampler.h>
#include <cstdlib>
#include <utility>
NRook::NRook(int num) :Sampler(num)
{
	for (int i = 0; i < num; i++)
	{
		sampleList[i].x = 1.f*(i) / numSample;
		sampleList[i].y = 1.f*(i) / numSample;
	}
}

void NRook::shuffle()
{
	for (int i = numSample-1; i > 1; i--)
	{
		int targetX = randomGen.getRandomI(0, i - 1);
		std::swap(sampleList[i].x, sampleList[targetX].x);
		//int targetY = randomGen.getRandomI(0, i - 1);
		//std::swap(sampleList[i].y, sampleList[targetX].y);
	}
}