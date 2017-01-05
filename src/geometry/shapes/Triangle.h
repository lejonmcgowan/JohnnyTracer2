//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_TRIANGLE_H
#define JOHNNYRENDERER2_TRIANGLE_H


#include <core/base/IShape.h>

class Triangle: public IShape
{
private:
public:
    BBox getObjectBounds() override;
    Number surfaceArea() const override;
    bool intersect(const Ray& ray, HitPacket& results) override;
private:
    Point a,b,c;
public:
    Triangle(Point a,Point b, Point c, Transform transform = Transform());
};


#endif //JOHNNYRENDERER2_TRIANGLE_H
