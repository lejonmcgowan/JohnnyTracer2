//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_SCENE_H
#define JOHNNYRENDERER2_SCENE_H
#include "geometry/Iprimitive.h"
#include "core/ILight.h"
#include "core/IVolumeRegion.h"
class Scene
{
private:
    std::shared_ptr<IPrimitive> aggregate;
    std::vector<std::shared_ptr<ILight>> lights;
    std::shared_ptr<IVolumeRegion> volumeRegion;
    BBox bounds;
public:
    Scene()
    {
        bounds = aggregate->getBounds();
    }
    /**
     * shoot a ray into the scene and determine the nearest object in the scene that it intersects with, if any
     * @param ray the ray to shoot into the scene
     * @return a pointer containing data based on the scene contiditions and nearest intersection
     */
    std::shared_ptr<HitData> queryIntersect(const Ray ray);
    /**
     * a less computationally expensive shot into the scene that determines if the ray collides with any object
     * @param ray the ray to shoot into the scene
     * @return a bool representing whether or not an object was hit.
     */
    bool checkIntersect(const Ray ray);

};
#endif //JOHNNYRENDERER2_SCENE_H
