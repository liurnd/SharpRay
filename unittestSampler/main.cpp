#include <Sampler/Sampler.h>
#include <cstdio>
#include <ctime>
int main()
{
	srand(time(NULL));
	int num = 511*127;
	Sampler* s = new NRook(num);
	s->shuffle();
	//s->mapToHemiSphere(1);
	FILE* fout = fopen("c.samples", "wb");
	/*for (int i = 0 ;i < num; i++)
	{
		fprintf(fout, "%f %f\n", (s->sampleList[i].x+1.f)/2, (s->sampleList[i].y+1.f)/2);
	}*/
	for (int i = 0 ;i < num; i++)
	{
		fprintf(fout, "%f %f\n", s->sampleList[i].x, s->sampleList[i].y);
	}
	fclose(fout);
}