//
// Created by lejonmcgowan on 9/4/16.
//

#include <iostream>
#include "IShape.h"

BBox IShape::getWorldBounds()
{
    return  getObjectBounds() * worldtransform;
}

bool IShape::intersectQuick(const Ray &ray)
{
    std::cout << "UNIMPLEMENTED INTERSECT QUICK" << std::endl;
    return false;
}

bool IShape::intersect(const Ray &ray, IShape::HitPacket &results)
{
    std::cout << "UNIMPLEMENTED INTERSECT" << std::endl;
    return false;
}
