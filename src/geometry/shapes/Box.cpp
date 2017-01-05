//
// Created by lejonmcgowan on 11/24/16.
//

#include <core/base/IShape.h>
#include "Box.h"

Box::Box(Vec3 min, Vec3 max, Transform transform): IShape(transform),
                                                   min(min),
                                                   max(max)
{

}
BBox Box::getObjectBounds()
{
    return BBox();
}
Number Box::surfaceArea() const
{
    return 0;
}
bool Box::intersect(const Ray& ray, IShape::HitPacket& results)
{
    return false;
}
