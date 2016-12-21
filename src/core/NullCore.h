//
// Created by lejonmcgowan on 9/6/16.
//

#ifndef JOHNNYRENDERER2_NULLCORE_H
#define JOHNNYRENDERER2_NULLCORE_H

#include "IRenderer.h"
#include "ISampler.h"

class NullRenderer : public IRenderer
{
public:
    /**
     * don't render squat
     * @param scene the scene to not render
     */
    virtual void render(const std::shared_ptr<Scene> scene) override
    {

    }

    /**
     * returns a black color.
     * @param scene scene to not render
     * @param ray ray to not cast
     * @param sample sample to not sample
     * @return a black color
     */
    virtual Color calcIncidentRadiance(const std::shared_ptr<Scene> scene, const Ray &ray, const
    std::shared_ptr<Sample> sample) const override
    {
        return Color();
    }

    /**
     * returns a black color.
     * @param scene scene to not render
     * @param ray ray to not cast
     * @param sample sample to not sample
     * @return a black color
     */
    virtual Color transmit(const std::shared_ptr<Scene> scene, const Ray &ray, const
    std::shared_ptr<Sample> sample) const override
    {
        return Color();
    }
};

class NullSampler : public ISampler
{
public:
    NullSampler(const IVec2 &xRange, const IVec2 &yRange, int numSamples) : ISampler(xRange, yRange, numSamples)
    {}

};

#endif //JOHNNYRENDERER2_NULLCORE_H
