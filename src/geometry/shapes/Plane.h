//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_PLANE_H
#define JOHNNYRENDERER2_PLANE_H


#include <core/IShape.h>

class Plane: public IShape
{
private:
    Point p;
    Vec3 nor;
public:
    Plane(Point point, Vec3 normal, Transform transform = Transform());
};


#endif //JOHNNYRENDERER2_PLANE_H
