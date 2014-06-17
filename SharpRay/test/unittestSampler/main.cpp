#include <Sampler/Sampler.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <utility>
#include <cstring>

void testSampler(FILE* fout, int num, bool dump = false)
{
	NRook* s = new NRook(num);
	s->shuffle();
	//s->mapToHemiSphere(1);
	FILE* foutXY = fopen("c.samples", "w");
//	memset(nMap,0, sizeof(nMap));
	for (int i = 0 ;i < num; i++)
	{
//		int x = fSize* s->sampleList[i].x/num;
//		int y = fSize* s->sampleList[i].y/num;
//		nMap[x][y]++;
		fprintf(foutXY, "%f %f\n",s->sampleList[i].x,s->sampleList[i].y);
	}
	fclose(foutXY);

//	float avg = static_cast<float> (num) / (fSize*fSize);
//	float divg = 0;
//	for (int i = 0; i < fSize; i++)
//		for (int j = 0; j < fSize; j++)
//		{
//			divg+=(nMap[i][j] - avg)*(nMap[i][j] - avg);
//		}
//	fprintf(fout, "%d,%f\n", num, divg/(fSize*fSize));
	delete s;
}

int main()
{
	srand(time(NULL));
	FILE* fout = fopen("c.csv", "w");
	//int num = 10000;
	/*for(int i = 10000;i<=1000000; i+= 10000)
	{
		if (i == 1000000)
			testSampler(fout, i,true);
		else
			testSampler(fout,i,false);
	}*/
	testSampler(fout,40000, true);
	fclose(fout);
}