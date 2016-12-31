//
// Created by lejonmcgowan on 11/23/16.
//

#include "Sphere.h"

Sphere::Sphere(Number radius, Transform transform): IShape(transform),
                                                    radius(radius)
{

}
BBox Sphere::getObjectBounds()
{
    return BBox();
}
Number Sphere::surfaceArea() const
{
    return 0;
}
bool Sphere::intersect(const Ray& ray, IShape::HitPacket& results)
{
    return false;
}
