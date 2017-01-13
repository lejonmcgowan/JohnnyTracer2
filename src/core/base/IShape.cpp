//
// Created by lejonmcgowan on 9/4/16.
//

#include <iostream>
#include "IShape.h"

BBox IShape::getWorldBounds()
{
    return  getObjectBounds() * worldtransform;
}

bool IShape::intersectQuick(const Ray &ray, bool alphaTexture)
{
    Vec3 mockHit;
    SurfaceInteraction mockSect(mockHit,mockHit,mockHit,SurfaceInteraction::Partials(),SurfaceInteraction::Partials(),nullptr);
    HitPacket packet(mockSect);

    return intersect(ray,packet);
}

bool IShape::intersect(const Ray &ray, IShape::HitPacket &results)
{
    std::cout << "UNIMPLEMENTED INTERSECT" << std::endl;
    return false;
}
