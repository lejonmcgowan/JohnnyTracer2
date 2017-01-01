//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_IFILTER_H
#define JOHNNYRENDERER2_IFILTER_H


#include "utils/UnitUtils.h"
class IFilter
{
protected:
    Vec2 radius,invRadius;
public:
    IFilter(const Vec2 radius);
    virtual Number evaluate(const Point2D point) = 0;
};


#endif //JOHNNYRENDERER2_IFILTER_H
