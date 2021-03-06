//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_BOX_H
#define JOHNNYRENDERER2_BOX_H


#include <core/utils/UnitUtils.h>

class Box: public IShape
{
private:
    Vec3 min,max;
public:
    BBox getObjectBounds() override;
    Number surfaceArea() const override;
    bool intersect(const Ray& ray, HitPacket& results) override;
    Box(Vec3 min,Vec3 max, Transform transform = Transform());
};


#endif //JOHNNYRENDERER2_BOX_H
