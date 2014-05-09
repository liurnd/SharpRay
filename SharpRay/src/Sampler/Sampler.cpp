#include "Sampler.h"
#include "Core/BaseDS.h"


void Sampler::mapToDisk()
{
    type = disk;
	for (int i = 0; i < numSample; i++)
	{
		normal3D& n = sampleList[i];
		float x = n.x * 2 - 1;
		float y = n.y * 2 - 1;
		float r, phi;

		if (x>y&&x>-y) { r = x; phi = pi / 4 * y / x;}
		else if (x<y&&x>-y){ r = y; phi = pi / 4 *(2-y / x); }
		else if (x<y&&x<-y){ r = -x; phi = pi / 4 * (4+ y / x); }
		else{ r = -y; phi = pi / 4 * (6 - y / x); }

		n.x = r*cos(phi);
		n.y = r*sin(phi);
	}
}

void Sampler::mapToHemiSphere(float e)
{
    type = hemisphere;
	for (int i = 0; i < numSample; i++)
	{
		normal3D& n = sampleList[i];
		float cos_phi = cos(2 * pi*n.x);
		float sin_phi = sin(2 * pi*n.x);
		float cos_theta = pow(1.0f - n.y, 1.f / (e + 1.f));
		float sin_theta = sqrt(1.f - cos_theta*cos_theta);
		n.x = sin_theta*cos_phi;
		n.y = sin_theta*sin_phi;
		n.z = cos_theta;
	}
}
