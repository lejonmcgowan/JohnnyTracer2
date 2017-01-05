//
// Created by lejonmcgowan on 9/5/16.
//

#ifndef JOHNNYRENDERER2_SAMPLE_H
#define JOHNNYRENDERER2_SAMPLE_H


#include <core/base/ISampler.h>
#include <Integrators/ISurfaceIntegrator.h>
#include <Integrators/IVolumeIntegrator.h>
#include "CameraSample.h"
#include <vector>

class Scene;
class Sample : public CameraSample
{
public:
    Sample(std::shared_ptr<ISampler> sampler, std::shared_ptr<ISurfaceIntegrator> surInt,
           std::shared_ptr<IVolumeIntegrator> volInt,
           std::shared_ptr<Scene> scene)
    {

    }

    unsigned long add1D(uint32_t num)
    {
        buffer1D.push_back(num);
        return buffer1D.size() - 1;
    }

    unsigned long add2D(uint32_t num)
    {
        buffer2D.push_back(num);
        return buffer2D.size() - 1;
    }

    Sample *duplicate(int count) const
    {

    }
private:
    std::vector<uint> buffer1D, buffer2D;
    void AllocateSampleMemory()
    {

    }

};

#endif //JOHNNYRENDERER2_SAMPLE_H
