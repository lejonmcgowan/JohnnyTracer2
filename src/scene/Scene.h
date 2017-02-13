//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_SCENE_H
#define JOHNNYRENDERER2_SCENE_H
#include <core/IPrimitive.h>
#include <core/base/ILight.h>
#include <core/BBox.h>
/**
 * the actual data structure used by the Ray tracer to generate an image.
 */
class Scene
{
public:
    // Scene Public Methods
    Scene(std::shared_ptr<IPrimitive> aggregate, const std::vector<std::shared_ptr<ILight>> &lights);
    const BBox &WorldBound() const { return worldBound; }
    bool intersect(Ray &ray, SurfaceInteraction *isect) const
    {
        return aggregate->intersect(ray,isect);
    }
    bool intersectQuick(Ray ray) const
    {
        return aggregate->intersectQuick(ray);
    }

    // Scene Public Data
    std::vector<std::shared_ptr<ILight>> lights;
    // Store infinite light sources separately for cases where we only want
    // to loop over them.
    std::vector<std::shared_ptr<ILight>> infiniteLights;

private:
    // Scene Private Data
    std::shared_ptr<IPrimitive> aggregate;
    BBox worldBound;
};

#endif //JOHNNYRENDERER2_SCENE_H
