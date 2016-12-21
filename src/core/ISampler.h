//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_ISAMPLER_H
#define JOHNNYRENDERER2_ISAMPLER_H


#include <utils/UnitUtils.h>
#include <memory>


/**
 * interface for generating 2d samples for stuff like anti-aliasing and textures
 */
 class Sample;
class ISampler
{
protected:
    const IVec2 xRange, yRange;
    const int numSamples;
public:
    //todo possibly take into account shutter range
    ISampler(IVec2 xRange, IVec2 yRange, int numSamples)
    :xRange(xRange),yRange(yRange),numSamples(numSamples)
    {

    }

    /**
     * generates samples in the given sample. uses std::rand to generate sampled values
     * @param sample the sample object to store the generated values in. sample values should be in the range [0,1]
     * @return the number of samples added to the passed-in sample. 0 implies that the sample is fully genderated (for
     * paralellization purposes).
     */
    virtual int generateSamples(Sample& sample) = 0;

    /*todo overload @genrateSamples to allow for custom RNGs to be used (for testibility and for possibly
     * better implementations than STD */
};


#endif //JOHNNYRENDERER2_ISAMPLER_H
