//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_BOX_H
#define JOHNNYRENDERER2_BOX_H


#include <utils/UnitUtils.h>
#include <Transform.h>

class Box: public IShape
{
private:
    Vec3 min,max;
public:
    Box(Vec3 min,Vec3 max, Transform transform = Transform());
};


#endif //JOHNNYRENDERER2_BOX_H
