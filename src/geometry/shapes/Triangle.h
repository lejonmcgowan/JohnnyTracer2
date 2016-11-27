//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_TRIANGLE_H
#define JOHNNYRENDERER2_TRIANGLE_H


#include <core/IShape.h>

class Triangle: public IShape
{
private:
    Point abc;
public:
    Triangle(Vec3 points, Transform transform = Transform());
};


#endif //JOHNNYRENDERER2_TRIANGLE_H
