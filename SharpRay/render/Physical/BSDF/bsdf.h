#ifndef _BSDF_H_
#define _BSDF_H_
#include <Core/BaseDS.h>
struct ShadeInfo;
class Sampler;
class BSDF
{
public:
    /**
     * @brief sample_BRDF Map a square sample to BSDF hemisphere sample, return hemishpere sample ,BRDF and pdf
     * @param sampleIn  [in] a square sample with equiprobability in [0,1) * [0,1]
     * @param si        [in] shadeInfo at hitpoint
     * @param wo        [in] out vector
     * @param sampleOut [out] the direction of sample ray
     * @param pdf       [out] the probability of this direction
     * @return          BRDF value
     */
    virtual ColorFloat sample_BRDF(const normal3D& sampleIn,  const ShadeInfo& si, const vector3D& wo, normal3D& sampleOut, float& pdf) = 0;
    virtual ColorFloat BRDF(const ShadeInfo& si, const vector3D& wo, const vector3D& wi) = 0;
    virtual ColorFloat BTDF(const ShadeInfo& si, const vector3D& wo, const vector3D& wi){ return 0; }
};

#include "GlossySpecular.h"
#include "lambertian.h"
#include "PerfectSpecular.h"
#endif
