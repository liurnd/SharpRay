#ifndef AREALIGHT_H
#define AREALIGHT_H
#include <Core/BaseDS.h>
#include <Light/Light.h>
class AreaLight
{
public:


    /**
     * @brief CalcSample
     * @param squareSample [in] a sample in square, 0 < x,y < 1
     * @param samplePoint  [out] samplePoint on the surface of the area light
     * @param Li           [out] output radiance of the sample point
     * @return             PDF of this sample
     */

    /**
     * @brief CalcSample
     * @param targetSample [in] the target point
     * @param squareSample [in] a sample in square, 0 < x,y < 1
     * @param samplePoint  [out] samplePoint on the surface of the area light
     * @param Li           [out] output radiance of the sample point
     * @param pdf          [out] PDF of this sample
     * @return             Whether this sample point is face to the target point
     */
    virtual bool CalcSample(const point3D& targetSample, const normal3D& squareSample, point3D& samplePoint, RColor& Li,float& pdf) = 0;
};


#include <Light/balllight.h>
#endif // AREALIGHT_H
