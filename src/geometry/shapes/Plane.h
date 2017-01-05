//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_PLANE_H
#define JOHNNYRENDERER2_PLANE_H


#include <core/base/IShape.h>

class Plane
{
private:
    Vec3 nor;
    double d;
public:
    Plane(Vec3 normal, double d);
};


#endif //JOHNNYRENDERER2_PLANE_H
