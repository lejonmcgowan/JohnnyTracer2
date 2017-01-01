//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_RENDERER_H
#define JOHNNYRENDERER2_RENDERER_H

#include <memory>

#include <geometry/Ray.h>

#include "utils/UnitUtils.h"


class Scene;
class Sample;
class IRenderer
{
public:
    virtual void render(const std::shared_ptr<Scene> scene) = 0;

    /**
     * calculate the incident radiance along the ray
     */
    virtual Color calcIncidentRadiance(const std::shared_ptr<Scene> scene, const Ray& ray, const
    std::shared_ptr<Sample> sample) const = 0;

    /**
     * calculate the amount of light that passes into scene (for volumetric scattering)
     */
    virtual Color transmit(const std::shared_ptr<Scene> scene, const Ray& ray, const
    std::shared_ptr<Sample> sample) const = 0;
};
#endif //JOHNNYRENDERER2_RENDERER_H
