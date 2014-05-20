#include "Sampler.h"
#include "Core/BaseDS.h"


normal3D Sampler::mapToDisk(const normal3D &n)
{
		float x = n.x * 2 - 1;
		float y = n.y * 2 - 1;
		float r, phi;

		if (x>y&&x>-y) { r = x; phi = pi / 4 * y / x;}
		else if (x<y&&x>-y){ r = y; phi = pi / 4 *(2-y / x); }
		else if (x<y&&x<-y){ r = -x; phi = pi / 4 * (4+ y / x); }
		else{ r = -y; phi = pi / 4 * (6 - y / x); }

        return normal3D(r*cos(phi),r*sin(phi), 0);
}

normal3D Sampler::mapToHemiSphere(const normal3D &n, float e)
{
    float cos_phi = cos(2 * pi*n.x);
    float sin_phi = sin(2 * pi*n.x);
    float cos_theta = pow(1.0f - n.y, 1.f / (e + 1.f));
    float sin_theta = sqrt(1.f - cos_theta*cos_theta);
    return normal3D(sin_theta*cos_phi, sin_theta*sin_phi, cos_theta);
}
