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
    std::shared_ptr<HitData> queryIntersect(const Ray ray);
    bool checkIntersect(const Ray ray);

};
#endif //JOHNNYRENDERER2_SCENE_H
