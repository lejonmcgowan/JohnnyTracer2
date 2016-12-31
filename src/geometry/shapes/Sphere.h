//
// Created by lejonmcgowan on 11/23/16.
//

#ifndef JOHNNYRENDERER2_SPHERE_H
#define JOHNNYRENDERER2_SPHERE_H


#include <core/IShape.h>

class Sphere: public IShape
{
private:
    Number radius;
public:
    Sphere(Number radius, Transform transform = Transform());
    BBox getObjectBounds() override;
    Number surfaceArea() const override;
    bool intersect(const Ray& ray, HitPacket& results) override;

};


#endif //JOHNNYRENDERER2_SPHERE_H
